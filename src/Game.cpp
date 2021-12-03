#include <fstream>
#include <iostream>

#include "AssetsPaths.h"
#include "CombatState.h"
#include "Game.h"

// Private functions
void Game::initVariables() {
	window = nullptr;
}

void Game::initWindow() {
	this->videoMode.height = 720;
	this->videoMode.width = 1280;
	// load window configs from file
	std::ifstream ifs("../config/window.ini");

	// set default values
	std::string title = "RPG";
	unsigned int framerate_limit = 120;
	bool vertical_sync_enabled = false;

	// replace default configs with file contents
	if(ifs.is_open()) {
		std::getline(ifs, title);
		ifs >> this->videoMode.width >> this->videoMode.height;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
	}
	ifs.close();

	// create window
	this->window = new sf::RenderWindow(this->videoMode, title, sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
	view = sf::View(sf::Vector2f(320.f, 240.f), sf::Vector2f(640.f, 480.f));
}

void Game::initStates() {
	states.push(new MainMenuState(window, assetsManager, {assetsManager.getMap(TILESHEET_FLOOR.c), assetsManager.getMap(TILESHEET_NATURE.c)},
	    {assetsManager.getDesign(LAYER1.c), assetsManager.getDesign(LAYER2.c)}, &supportedkeys));
}

// Constructor
Game::Game() {
	initKeys();
	this->initVariables();
	this->initWindow();
	this->initStates();
}

// Destructor
Game::~Game() {
	// Delete window
	delete this->window;

	// Clear states stack
	while(!this->states.empty()) {
		// remove data
		delete this->states.top();
		// remove pointer
		this->states.pop();
	}
}

// Accessors
bool Game::isRunning() const {
	return this->window->isOpen();
}

void Game::makeNewCombat(const int numberOfEnemis) {
	Texture* alien_texture = assetsManager.getTexture(ALIEN.c);
	Animation alien_animation(alien_texture, sf::IntRect(50, 25, 105, 145), Interval(210, 0), Position(100, 100));
	Character alien("Alien", Stats(15, 25, 50, 30), alien_animation);
	Enemies enemies{};
	for(int i = 0; i < numberOfEnemis; i++) {
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
	while(this->window->pollEvent(this->event)) {
		switch(this->event.type) {
		// Event that is called when the close button is clicked
		case sf::Event::Closed: this->window->close(); break;
		case sf::Event::KeyPressed:
			if(!in_combat) {
				// Event that is called when the Escape button is pressed
				switch(this->event.key.code) {
				case sf::Keyboard::Escape: window->close(); break;
				case sf::Keyboard::Enter:
					action = states.top()->shouldAct();
					if(action == StateAction::EXIT_GAME) { this->window->close(); }
					if(action == StateAction::START_GAME) {
						states.push(new GameState(window, assetsManager, {assetsManager.getMap(TILESHEET_FLOOR.c), assetsManager.getMap(TILESHEET_NATURE.c)},
						    {assetsManager.getDesign(LAYER1.c), assetsManager.getDesign(LAYER2.c)}));
					}
					break;
				default:
					action = states.top()->handleKeys(event.key.code, &view);
					if(previousKey != this->event.key.code) {
						// play gasping sound each time the player changes direction
						sound.play();
					}
					previousKey = this->event.key.code;
					if(action == StateAction::START_COMBAT) { makeNewCombat(1);}
					if(action == StateAction::EXIT_GAME) { this->window->close(); }
					break;
				}
			} else {
				switch(this->event.key.code) {
				case sf::Keyboard::Escape:
					// open pause menu
					break;
				case sf::Keyboard::Up: // Up arrow
				                       // swich action up
					break;
				case sf::Keyboard::Down: // Down arrow
				                         // swich action down
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
	this->pollEvents();

	if(!this->states.empty()) {
		// update current game state
		this->states.top()->update(this->dt);
		// check if the state is about to be quit
		if(this->states.top()->shouldQuit()) {
			// quit actions
			this->states.top()->quitStateActions();
			delete this->states.top();
			this->states.pop();
		}
	} else { // End of application
		// Since the game depends on the window being open (see function
		// isRunning()), closing the window ends the game
		Game::endApplication();
		this->window->close();
	}
}

void Game::render() {
	// Clear old frame
	window->clear();

	// Draw game
	if(!this->states.empty()) {
		// render current game state
		this->states.top()->render(this->window);
	}
	window->setView(view);
	if(states.size() > 0) states.top()->drawPlayer(window);
	// Window is done drawing --> display result
	window->display();
}

void Game::updateDT() {
	this->dt = this->dtClock.restart().asSeconds();
	// std::cout << "Time delta: " << this->dt << std::endl;
}

void Game::endApplication() {
	std::cout << "Ending application" << std::endl;
}

void updateKeybinds(const float& dt) {}
void quitStateActions() {}

void Game::initKeys() {
	std::ifstream ifs(KEYS.c);

	if(ifs.is_open()) {
		std::string key;
		int key_value = 0;

		while(ifs >> key >> key_value) {
			supportedkeys.emplace(key, key_value);
		}
	}
	ifs.close();
}
