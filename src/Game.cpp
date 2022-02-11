#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "AssetsPaths.h"
#include "Game.h"
#include "House.h"
#include "HouseManager.h"
#include "asset_data.h"
#include "states/CombatState.h"
#include "states/GameOverState.h"
#include "states/InventoryState.h"
#include "states/PauseGameState.h"
#include "states/SettingsState.h"

// Private functions
void Game::initVariables() {
	window = nullptr;

	Texture* play_text = assetsManager.getTexture(NINJA_WALK.c);
	Animation player_animation(play_text, sf::IntRect(0, 0, TILESIZE, TILESIZE), Position(50, 50));
	player = Player("Adventurer", Stats(15, 20, 50, 30, 31, 1), player_animation, 5.0f);
}

void Game::closeWindow() {
	std::ifstream ifs(WINDOW.c);

	// set default values
	std::string title = "RPG";
	unsigned int framerate_limit = 120;
	bool vertical_sync_enabled = false;

	// read default configs with file contents
	if(ifs.is_open()) {
		std::getline(ifs, title);
		ifs >> videoMode.width >> videoMode.height;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
	}
	ifs.close();

	std::ofstream ofs(WINDOW.c);
	// get the size of the window
	sf::Vector2u currentSize = window->getSize();
	unsigned int width = currentSize.x;
	unsigned int height = currentSize.y;
	// write new configs
	if(ofs.is_open()) {
		std::string res = std::to_string(width) + " " + std::to_string(height);
		ofs << title << std::endl;
		ofs << res << std::endl;
		ofs << framerate_limit << std::endl;
		ofs << vertical_sync_enabled << std::endl;
	}
	ofs.close();
	window->close();
}

std::string PosToString(Position_i pos) {
	return "(" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ")";
}

void Game::initWindow() {
	videoMode.height = 720;
	videoMode.width = 1280;
	// load window configs from file
	std::ifstream ifs(WINDOW.c);

	// set default values
	std::string title = "RPG";
	unsigned int framerate_limit = 120;
	bool vertical_sync_enabled = false;

	// replace default configs with file contents
	if(ifs.is_open()) {
		std::getline(ifs, title);
		ifs >> videoMode.width >> videoMode.height;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
	}
	ifs.close();

	// create window
	window = new sf::RenderWindow(videoMode, title, sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	window->setFramerateLimit(framerate_limit);
	window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initStates() {
	states.push(new MainMenuState(window, assetsManager, &keyBindings));
}

// Constructor
Game::Game() : itemManager(&assetsManager) {
	initKeys();
	initVariables();
	initWindow();
	initStates();
	mousePos = sf::Mouse::getPosition(*window);
	mousePosText.setFont(*assetsManager.getFont(ALEX.c));
	mousePosText.setOutlineColor(sf::Color::Black);
	mousePosText.setFillColor(sf::Color::Black);
	mousePosText.setString(PosToString(mousePos));
}

// Destructor
Game::~Game() {
	// Delete window
	delete window;

	// Clear states stack
	while(!states.empty()) {
		// remove data
		delete states.top();
		// remove pointer
		states.pop();
	}
}

// Accessors
bool Game::isRunning() const {
	return window->isOpen();
}

void Game::makeNewCombat(const Enemy* enemy) {
	auto mapTexture = {assetsManager.getMap(TILESHEET_FLOOR.c), assetsManager.getMap(TILESHEET_NATURE.c)};
	JSONFilePath* design = assetsManager.getMapDesign(COMBAT_LEVEL1.c);
	turnOffMusic();
	states.push(new CombatState(window, assetsManager, mapTexture, *design, player, *enemy, &keyBindings));
}

void Game::makeMainGameState(Position playerPosition = {50, 50}) {
	Villagers villagers;
	villagers.push_back(
	    createVillager("Egg Girl", EGG_GIRL_FACE.c, EGG_GIRL_WALK.c, Position(300, 50), MovementType::VERTICAL, 0.3f));
	villagers.push_back(
	    createVillager("Old Man", OLD_MAN_FACE.c, OLD_MAN_WALK.c, Position(50, 150), MovementType::HORIZONTAL, 0.2f));
	villagers.push_back(createVillager(
	    "Princess", PRINCESS_FACE.c, PRINCESS_WALK.c, Position(230, 150), MovementType::VERTICAL, 0.25f));

	player.animation.set_position(playerPosition);
	// Comment: There's a bug in Tileson. Tile attributes, such as isBlocked are connected with the tile
	// ID. However, the tile ID differs of tiles in the 2nd, 3rd, ... tile sheet from the original ID,
	// because it's counted with an offset. My theory is that, internally, this ID is used to get the
	// attributes, but returns NULL for all sheets but the first one. Therefore, all collisions are
	// noted in the first sheet, which has to be passed twice now for the collisions to be loaded at
	// all.
	auto* mainGame = new GameState(window, assetsManager,
	    {assetsManager.getMap(TILESHEET_FLOOR.c), assetsManager.getMap(TILESHEET_FLOOR.c),
	        assetsManager.getMap(TILESHEET_HOUSES.c), assetsManager.getMap(TILESHEET_NATURE.c)},
	    *assetsManager.getMapDesign(MAP_LEVEL1.c), &keyBindings, player, villagers,
	    *assetsManager.getMusic(VILLAGE_MUSIC.c));

	states.push(mainGame);
	housePositions = mainGame->listHousePositions();
}

Villager Game::createVillager(const Name& name, const std::string& faceTextureName, const std::string& textureName,
    const Position position, const MovementType movementDirection, const float stepsize) {
	Texture* tex = assetsManager.getTexture(textureName);
	Animation anim(tex, sf::IntRect(0, 0, TILESIZE, TILESIZE), position);
	Position endPosition;
	if(movementDirection == MovementType::HORIZONTAL) {
		endPosition = {position.x + 50, position.y};
	} else {
		endPosition = {position.x, position.y + 60};
	}
	return {anim, name, movementDirection, endPosition, stepsize, faceTextureName};
}

void Game::makeNewHouseState(DoorNumber doorNumber) {
	std::vector<MapBackground*> tileSheets = {assetsManager.getMap(TILESHEET_INTERIOR_FLOOR.c),
	    assetsManager.getMap(TILESHEET_INTERIOR_FLOOR.c), assetsManager.getMap(TILESHEET_FURNITURE.c)};
	House house = HouseManager::getHouse(doorNumber + 1);

	Enemies enemies;
	EnemyData enemyData = ENEMYDATA[doorNumber];
	Texture* texture = assetsManager.getTexture(enemyData.texturePath);
	Animation animation(texture, sf::IntRect(0, 0, TILESIZE, TILESIZE), enemyData.position);
	Enemy enemy(enemyData.name, Stats(15, 15, 15, 15, 15, 15), animation, MovementType::HORIZONTAL, {30, 30}, 2.0f,
	    enemyData.experience);
	enemies.push_back(enemy);

	Object* item = nullptr;
	Name itemName = HOUSEDATA.at(doorNumber).itemName;
	if(!itemManager.hasBeenPickedUp(itemName)) {
		item = itemManager.get(itemName, HOUSEDATA.at(doorNumber).itemPosition);
	}
	states.push(new GameState(window, assetsManager, tileSheets, house.houseDesignPath, &keyBindings, player, enemies,
	    *assetsManager.getMusic(HOUSE_MUSIC.c), item, doorNumber + 1));

}

void Game::makeNewHouseStateFromPlayerPosition(const Position playerPosition) {
	DoorNumber doorNumber = 0;
	for(auto& hp : housePositions) {
		auto doorPosition = hp.first;
		if(positionsInRange(playerPosition, doorPosition, 8.0f)) {
			doorNumber = hp.second - 1;
			break;
		}
	}
	makeNewHouseState(doorNumber);
}

void Game::openInventory() {
	states.push(new InventoryState(window, assetsManager, &keyBindings, &itemManager, &player, states.top()));
}

void Game::pollEvents() {
	// Gets StateAction that is triggered by the game itself, not the player
	StateAction action = states.top()->programAction();
	SaveObject savedGame{};
	Position lastPosition;
	// Checks for events triggered by the player
	while(window->pollEvent(event)) {
		switch(event.type) {
		// Event that is called when the close button is clicked
		case sf::Event::Closed: closeWindow(); break;
		case sf::Event::KeyPressed:
			// Event that is called when the Escape button is pressed
			switch(event.key.code) {
			case sf::Keyboard::Escape: closeWindow(); break;
			case sf::Keyboard::Enter: action = states.top()->shouldAct(); break;
			case sf::Keyboard::K:
				turnOffMusic();
				makeNewHouseStateFromPlayerPosition(housePositions.back().first);
				break;
			default: action = states.top()->handleKeys(event.key.code); break;
			}
			switch(action) {
			case StateAction::EXIT_GAME: closeWindow(); break;
			case StateAction::START_GAME:
				turnOffMusic();
				makeMainGameState();
				break;
			case StateAction::START_SETTING: states.push(new SettingsState(window, assetsManager, &keyBindings)); break;
			case StateAction::PAUSE_GAME: states.push(new PauseGameState(window, assetsManager, &keyBindings)); break;
			case StateAction::LOAD_GAME:
			    turnOffMusic();
				savedGame = SaveAndLoad::loadGame();
				makeMainGameState();
				makeNewHouseState(savedGame.houseNumber);
				player.animation.set_position({savedGame.positionX, savedGame.positionY});
				break;
			case StateAction::START_COMBAT: makeNewCombat(dynamic_cast<GameState*>(states.top())->getEnemy()); break;
			case StateAction::EXIT_COMBAT:
				// coming out here means you won the fight.
				player.addExperience(dynamic_cast<CombatState*>(states.top())->experienceFromEnemy());
				turnOffMusic();
				states.pop();
				states.top()->resumeMusic();
				// save progress
				SaveAndLoad::saveGame(SaveObject{
				    dynamic_cast<GameState*>(states.top())->doorNumber,
				    dynamic_cast<GameState*>(states.top())->getCurrentPlayerPosition().x,
				    dynamic_cast<GameState*>(states.top())->getCurrentPlayerPosition().y,
				    player.getLevel()});
				break;
			case StateAction::START_HOUSE:
				turnOffMusic();
				makeNewHouseStateFromPlayerPosition(dynamic_cast<GameState*>(states.top())->getCurrentPlayerPosition());
				break;
			case StateAction::PICK_ITEM:
			{
				Name itemName = dynamic_cast<GameState*>(states.top())->getItemName();
				itemManager.pickUp(itemName);
				auto item = itemManager.get(itemName);
				if(item->can_equip) {
					player.equip(item);
				}
			} break;
			case StateAction::OPEN_INVENTORY: openInventory(); break;
			case StateAction::ADD_ITEM: itemManager.add_item(); break;
			case StateAction::EXIT_HOUSE:
				turnOffMusic();
				states.pop();
				states.top()->resumeMusic();
				break;
			case StateAction::EXIT_SETTING:
			case StateAction::RESUME_GAME:
			case StateAction::CLOSE_INVENTORY: states.pop(); break;
			default: break;
			}
			break;
		case sf::Event::MouseMoved: break;
		default:
			if(action == StateAction::GAME_OVER) {
				turnOffMusic();
				states.push(new GameOverState(window, assetsManager, &keyBindings));
				break;
			}
			break;
		}
	}
}

void Game::update() {
	pollEvents();

	mousePos = sf::Mouse::getPosition(*window);
	mousePosText.setString(PosToString(mousePos));

	if(!states.empty()) {
		// update current game state
		states.top()->update(dt);
		// check if the state is about to be quit
		if(states.top()->shouldQuit()) {
			// quit actions
			states.top()->quitStateActions();
			delete states.top();
			states.pop();
			states.top()->resumeMusic();
		}
	} else { // End of application
		// Since the game depends on the window being open (see function
		// isRunning()), closing the window ends the game
		Game::endApplication();
		closeWindow();
	}
}

void Game::turnOffMusic() {
	states.top()->stopMusic();
}

void Game::render() {
	// Clear old frame
	window->clear();

	// Draw game
	if(!states.empty()) {
		// render current game state
		states.top()->render(window);
	}
	window->setView(states.top()->getView());
	if(!states.empty()) states.top()->drawPlayer(window);
	// Window is done drawing --> display result
	// window->draw(mousePosText);
	window->display();
}

void Game::updateDT() {
	dt = dtClock.restart().asSeconds();
}

void Game::endApplication() {
	std::cout << "Ending application" << std::endl;
}

void Game::initKeys() {
	keyActionString.emplace("UP", KeyAction::UP);
	keyActionString.emplace("DOWN", KeyAction::DOWN);
	keyActionString.emplace("RIGHT", KeyAction::RIGHT);
	keyActionString.emplace("LEFT", KeyAction::LEFT);
	keyActionString.emplace("SELECT", KeyAction::SELECT);
	keyActionString.emplace("BACK", KeyAction::BACK);
	keyActionString.emplace("INTERACT", KeyAction::INTERACT);
	keyActionString.emplace("PAUSE", KeyAction::PAUSE);

	std::ifstream ifs(KEYS.c);
	std::string key;
	size_t key_value = 0;

	if(ifs.is_open()) {
		while(ifs >> key >> key_value) {
			keyBindings.emplace(keyActionString.at(key), static_cast<sf::Keyboard::Key>(key_value));
		}
	}
	ifs.close();
}
