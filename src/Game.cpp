#include <iostream>

#include "AssetsPaths.h"
#include "CombatState.h"
#include "Game.h"

// Private functions
void Game::initVariables() {
	window = nullptr;
	soundBuffer = assetsManager.getSoundBuffer(GASP.c);
	sound.setBuffer(soundBuffer);
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
	window = new sf::RenderWindow(videoMode, title, sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(framerate_limit);
	window->setVerticalSyncEnabled(vertical_sync_enabled);
	view = sf::View(sf::Vector2f(320.f, 240.f), sf::Vector2f(640.f, 480.f));
}

void Game::initStates() {
	states.push(new MainMenuState(window, assetsManager, {
	                                                         assetsManager.getMap(TILESHEET_FLOOR.c),
	                                                         assetsManager.getMap(TILESHEET_NATURE.c),
	                                                         assetsManager.getMap(TILESHEET_HOUSES.c)
	                                                     },
	    {assetsManager.getDesign(LAYER1.c), assetsManager.getDesign(LAYER2.c)}, &supportedKeys));
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
	auto mapTexture = {assetsManager.getMap(TILESHEET_FLOOR.c)};
	auto designs = {assetsManager.getDesign(COMBATLEVEL.c)};
	Party party{*dynamic_cast<GameState*>(states.top())->getPlayer()};
	states.push(new CombatState(window, assetsManager, mapTexture, designs, party, enemies));
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
			if(!in_combat) {
				// Event that is called when the Escape button is pressed
				switch(event.key.code) {
				case sf::Keyboard::Escape: window->close(); break;
				case sf::Keyboard::Enter:
					action = states.top()->shouldAct();
					if(action == StateAction::EXIT_GAME) {
						window->close();
					}
					if(action == StateAction::START_GAME) {
						states.push(new GameState(window, assetsManager, {assetsManager.getMap(TILESHEET_FLOOR.c), assetsManager.getMap(TILESHEET_NATURE.c)},
						    {assetsManager.getDesign(LAYER1.c), assetsManager.getDesign(LAYER2.c)}));
					}
					break;
				default:
					action = states.top()->handleKeys(event.key.code, &view);
					if(previousKey != event.key.code) {
						// play gasping sound each time the player changes direction
						sound.play();
					}
					previousKey = event.key.code;
					if(action == StateAction::START_COMBAT) {
						makeNewCombat(1);
					}
					if(action == StateAction::EXIT_GAME) {
						window->close();
					}
					break;
				}
			} else {
				switch(event.key.code) {
				case sf::Keyboard::Escape:
					// open pause menu
					break;
				case sf::Keyboard::Up: // Up arrow
				                       // switch action up
					break;
				case sf::Keyboard::Down: // Down arrow
				                         // switch action down
					break;
				case sf::Keyboard::Space:
					// select combat action
					break;
				case sf::Keyboard::A:
					// calling quitStateActions here is only for debug reasons
					states.top()->quitStateActions();
					in_combat = false;
				default: break;
				}
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
		}
	} else { // End of application
		// Since the game depends on the window being open (see function
		// isRunning()), closing the window ends the game
		Game::endApplication();
		window->close();
	}
}

void Game::render() {
	// Clear old frame
	window->clear();

	// Draw game
	if(!states.empty()) {
		// render current game state
		states.top()->render(window);
	}
	window->setView(view);
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
	std::ifstream ifs(KEYS.c);

	if(ifs.is_open()) {
		std::string key;
		int key_value = 0;

		while(ifs >> key >> key_value) {
			supportedKeys.emplace(key, key_value);
		}
	}
	ifs.close();
}
