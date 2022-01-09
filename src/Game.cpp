#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "AssetsPaths.h"
#include "CombatState.h"
#include "Game.h"
#include "SettingsState.h"
#include "asset_data.h"

// Private functions
void Game::initVariables() {
	window = nullptr;

	Texture* play_text = assetsManager.getTexture(NINJA_WALK.c);
	Animation player_animation(play_text, sf::IntRect(0, 0, TILESIZE, TILESIZE), Position(50, 50));
	player = Player("Adventurer", Stats(15, 20, 50, 30, 15, 1), player_animation);
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
Game::Game() {
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

void Game::makeNewCombat() {
	Enemy alien = createAlien(assetsManager);
	auto mapTexture = {assetsManager.getMap(TILESHEET_FLOOR.c), assetsManager.getMap(TILESHEET_NATURE.c)};
	JSONFilePath* design = assetsManager.getMapDesign(COMBAT_LEVEL1.c);
	turnOffMusic();
	states.push(new CombatState(window, assetsManager, mapTexture, *design, player, alien, &keyBindings));
}

void Game::makeNewCombat(const Enemy* enemy) {
	auto mapTexture = {assetsManager.getMap(TILESHEET_FLOOR.c), assetsManager.getMap(TILESHEET_NATURE.c)};
	JSONFilePath* design = assetsManager.getMapDesign(COMBAT_LEVEL1.c);
	turnOffMusic();
	states.push(new CombatState(window, assetsManager, mapTexture, *design, player, *enemy, &keyBindings));
}

void Game::makeMainGameState() {
	Villagers villagers;
	villagers.push_back(createVillager(EGG_GIRL_WALK.c, "Egg Girl", Position(300, 50), MovementType::VERTICAL, 0.3f));
	villagers.push_back(createVillager(OLD_MAN_WALK.c, "Old Man", Position(50, 150), MovementType::HORIZONTAL, 0.4f));
	villagers.push_back(createVillager(PRINCESS_WALK.c, "Princess", Position(230, 150), MovementType::VERTICAL, 0.2f));

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

Villager Game::createVillager(const std::string& textureName, const Name name, const Position position,
    const MovementType movementDirection, const float stepsize) {
	Texture* tex = assetsManager.getTexture(textureName);
	Animation anim(tex, sf::IntRect(0, 0, TILESIZE, TILESIZE), position);
	Position endPosition;
	if(movementDirection == MovementType::HORIZONTAL) {
		endPosition = {position.x + 50, position.y};
	} else {
		endPosition = {position.x, position.y + 60};
	}
	return {anim, name, movementDirection, endPosition, stepsize};
}

void Game::makeNewHouseState(const Position playerPosition) {
	DoorNumber doorNumber = 0;
	for(auto& hp : housePositions) {
		auto doorPosition = hp.first;
		if(positionsInRange(playerPosition, doorPosition, 8.0f)) {
			doorNumber = hp.second;
			break;
		}
	}
	std::vector<MapBackground*> tileSheets = {assetsManager.getMap(TILESHEET_INTERIOR_FLOOR.c),
	    assetsManager.getMap(TILESHEET_INTERIOR_FLOOR.c), assetsManager.getMap(TILESHEET_FURNITURE.c)};
	House house = HouseManager::getHouse(doorNumber);
	Enemies enemies;

	EnemyData enemyData = ENEMYDATA[int(doorNumber - 1)];
	Texture* texture = assetsManager.getTexture(enemyData.texturePath);
	Animation animation(texture, sf::IntRect(0, 0, TILESIZE, TILESIZE), enemyData.position);
	Enemy enemy(enemyData.name, Stats(15, 15, 15, 15, 15, 15), animation, MovementType::HORIZONTAL, {30, 30}, 2.0f);
	enemies.push_back(enemy);

	states.push(new GameState(window, assetsManager, tileSheets, house.houseDesignPath, &keyBindings, player, enemies,
	    *assetsManager.getMusic(HOUSE_MUSIC.c)));
}

void Game::pollEvents() {
	// Event polling
	StateAction action = StateAction::NONE;
	while(window->pollEvent(event)) {
		switch(event.type) {
		// Event that is called when the close button is clicked
		case sf::Event::Closed: closeWindow(); break;
		case sf::Event::KeyPressed:
			// Event that is called when the Escape button is pressed
			switch(event.key.code) {
			case sf::Keyboard::Escape: closeWindow(); break;
			case sf::Keyboard::Enter: action = states.top()->shouldAct(); break;
			default: action = states.top()->handleKeys(event.key.code); break;
			}
			switch(action) {
			case StateAction::EXIT_GAME: closeWindow(); break;
			case StateAction::START_GAME:
				turnOffMusic();
				makeMainGameState();
				break;
			case StateAction::START_SETTING: states.push(new SettingsState(window, assetsManager, &keyBindings)); break;
			case StateAction::EXIT_SETTING: states.pop(); break;
			case StateAction::START_COMBAT:
				if(auto* house = dynamic_cast<GameState*>(states.top()); house->isHouse) {
					makeNewCombat(house->getEnemy());
				} else {
					makeNewCombat();
				}
				break;
			case StateAction::EXIT_COMBAT:
				// calling quitStateActions here is only for debug reasons
				states.top()->quitStateActions();
				break;
			case StateAction::START_HOUSE:
				turnOffMusic();
				makeNewHouseState(states.top()->getCurrentPlayerPosition());
				break;
			case StateAction::EXIT_HOUSE:
				turnOffMusic();
				states.pop();
				states.top()->resumeMusic();
				break;
			default: break;
			}
			break;
		case sf::Event::MouseMoved: break;
		default:
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
