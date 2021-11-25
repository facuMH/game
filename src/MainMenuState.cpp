#include "MainMenuState.h"
#include "AssetsPaths.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, AssetsManager& am, KeyList* gameSupportedKeys) : State(window) {
	supportedKeys = gameSupportedKeys;
	initBackground(window, am);
	initFonts(am);
	initKeybinds();
	initButtons();
}

void MainMenuState::initBackground(sf::RenderWindow* window, AssetsManager& am) {
	background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	backgroundTexture = *am.getTexture(BACKGROUND.c);
	background.setTexture(&backgroundTexture);
}

void MainMenuState::initFonts(AssetsManager& am) {
	font = *am.getFont(DOSIS.c);
}

void MainMenuState::initKeybinds() {
	std::ifstream ifs(MENUKEYBIND.c);

	if(ifs.is_open()) {
		std::string key = "";
		std::string key2 = "";

		while(ifs >> key >> key2) {
			keybinds[key] = supportedKeys->at(key2);
		}
	}
	ifs.close();
	/*
	keybinds["CLOSE"] = supportedKeys->at("Escape");
	keybinds["MOVE_LEFT"] = supportedKeys->at("A");
	keybinds["MOVE_RIGHT"] = supportedKeys->at("D");
	keybinds["MOVE_UP"] = supportedKeys->at("W");
	keybinds["MOVE_DOWN"] = supportedKeys->at("S");*/
}

void MainMenuState::initButtons() {
	buttons["GAME_STATE"] = new Button(300, 480, 150, 50, &font, "New Game", GREY, LIGHTGREY, BLACK);
	buttons["SETTINGS"] = new Button(300, 580, 150, 50, &font, "Settings", GREY, LIGHTGREY, BLACK);
	buttons["EXIT"] = new Button(300, 680, 150, 50, &font, "QUIT", GREY, LIGHTGREY, BLACK);
}

MainMenuState::~MainMenuState() {
	for(auto it = buttons.begin(); it != buttons.end(); ++it) {
		delete it->second;
	}
}

void MainMenuState::endState() {
	std::cout << "Ending Maun Menu!"
	          << "\n";
}

void MainMenuState::updateInput(const float& dt) {
	checkIfQuitting();
}

void MainMenuState::updateButtons() {
	/*Updates all the buttons in the state and handels their functionality*/
	for(auto& it : buttons) {
		it.second->update(mousePosView);
	}

	// New Game
	// if(buttons["GAME_STATE"]->isPressed()) { states->push(new GameState(window, supportedKeys, states)); }

	// Quit the game
	if(buttons["EXIT"]->isPressed()) { quit = true; }
}

void MainMenuState::updateMousePositions() {
	mousePosScreen = sf::Mouse::getPosition();
	mousePoseWindow = State::getMouse();
	mousePosView = getPos(mousePoseWindow);
}

void MainMenuState::update(const float& dt) {
	updateMousePositions();
	updateInput(dt);
	updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget* target) {
	for(auto& it : buttons) {
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target) {
	target->draw(background);
	renderButtons(target);

	// Remove Later!!!!!
	/*sf::Text mouseText;
	mouseText.setPosition(mousePosView.x, mousePosView.y -50);
	mouseText.setFont(font);
	mouseText.setCharacterSize(19);
	std::stringstream ss;
	ss << mousePosView.x << " " << mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);*/
}

void MainMenuState::checkIfQuitting() {
	State::checkIfQuitting();
}

void MainMenuState::updateKeybinds(const float& dt) {
	checkIfQuitting();
}

void MainMenuState::quitStateActions() {
	std::cout << "Ending current game state" << std::endl;
}
