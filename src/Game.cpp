#include <iostream>

#include "AssetsPaths.h"
#include "CombatState.h"
#include "Game.h"

// Private functions
void Game::initVariables() {
	window = nullptr;
}

void Game::initWindow() {
	videoMode.height = 720;
	videoMode.width = 1280;
	// load window configs from file
	std::ifstream ifs("../config/window.ini");

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

void Game::makeNewCombat(const int numberOfEnemies) {
	Texture* alien_texture = assetsManager.getTexture(ALIEN.c);
	Animation alien_animation(alien_texture, sf::IntRect(50, 25, 105, 145), Interval(210, 0), Position(100, 100));
	Character alien("Alien", Stats(15, 25, 50, 30), alien_animation);
	Enemies enemies{};
	for(int i = 0; i < numberOfEnemies; i++) {
		alien.animation.move({50, 0});
		enemies.push_back(alien);
	}
	auto mapTexture = {assetsManager.getMap(TILESHEET_FLOOR.c), assetsManager.getMap(TILESHEET_NATURE.c)};
	JSONFilePath* design = assetsManager.getMapDesign(COMBAT_LEVEL1.c);
	Party party{*dynamic_cast<GameState*>(states.top())->getPlayer()};
	turnOffMusic();
	states.push(new CombatState(window, assetsManager, mapTexture, *design, party, enemies, &keyBindings));
	in_combat = true;
}

// Functions

void Game::pollEvents() {
	// Event polling
	StateAction action;
	while(window->pollEvent(event)) {
		switch(event.type) {
		// Event that is called when the close button is clicked
		case sf::Event::Closed: window->close(); break;
		case sf::Event::KeyPressed:
			// Event that is called when the Escape button is pressed
			switch(event.key.code) {
			case sf::Keyboard::Escape: window->close(); break;
			case sf::Keyboard::Enter:
				action = states.top()->shouldAct();
				if(action == StateAction::EXIT_GAME) {
					window->close();
				}
				if(action == StateAction::START_GAME) {
					turnOffMusic();
					// Optional TODO: find bug in Tileson.
					// Comment: There's a bug in Tileson. Tile attributes, such as isBlocked are connected with the tile ID.
					// However, the tile ID differs of tiles in the 2nd, 3rd, ... tile sheet from the original ID, because it's
					// counted with an offset. My theory is that, internally, this ID is used to get the attributes, but returns
					// NULL for all sheets but the first one. Therefore, all collisions are noted in the first sheet, which
					// has to be passed twice now for the collisions to be loaded at all.
					states.push(new GameState(window, assetsManager,
					    {assetsManager.getMap(TILESHEET_FLOOR.c), assetsManager.getMap(TILESHEET_FLOOR.c),
					        assetsManager.getMap(TILESHEET_HOUSES.c), assetsManager.getMap(TILESHEET_NATURE.c)},
					    *assetsManager.getMapDesign(MAP_LEVEL1.c), &keyBindings));
				}
				break;
			default:
				action = states.top()->handleKeys(event.key.code);
				if(action == StateAction::START_COMBAT) {
					makeNewCombat(1);
				}
				if(action == StateAction::EXIT_GAME) {
					window->close();
				}
				if(action == StateAction::EXIT_COMBAT) {
					// calling quitStateActions here is only for debug reasons
					states.top()->quitStateActions();
					in_combat = false;
				}
				break;
			}
			break;
		case sf::Event::MouseMoved: break;
		default: break;
		}
	}
}

void Game::update() {
	pollEvents();

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
		window->close();
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