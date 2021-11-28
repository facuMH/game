
#include <SFML/Window.hpp>

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
		std::string key;
		std::string key2;

		while(ifs >> key >> key2) {
			keybinds[key] = supportedKeys->at(key2);
		}
	}
	ifs.close();
}

void MainMenuState::initButtons() {
	buttons.push_back(Button(300, 150, 150, 50, &font, "New Game", GREY, LIGHTGREY, BLACK));
	activeButton = 0;
	buttons[activeButton].setActive();
	buttons.push_back(Button(300, 200, 150, 50, &font, "Settings", GREY, LIGHTGREY, BLACK));
	buttons.push_back(Button(300, 250, 150, 50, &font, "QUIT", GREY, LIGHTGREY, BLACK));
}

MainMenuState::~MainMenuState() {}

void MainMenuState::endState() {
	std::cout << "Ending Maun Menu!"
	          << "\n";
}

void MainMenuState::updateInput(const float& dt) {
	checkIfQuitting();
}

void MainMenuState::updateButtons() {
	/*Updates all the buttons in the state and handels their functionality*/
	for(auto it : buttons) {
		it.update(mousePosView);
	}
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
		it.render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target) {
	target->draw(background);
	renderButtons(target);
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

void MainMenuState::handleKeys(sf::Keyboard::Key key) {
	switch(key) {
	case sf::Keyboard::Up: // Up arrow
		buttons[activeButton].setInactive();
		if(activeButton == 0) {
			activeButton = MAX_BUTTONS - 1;
		} else {
			activeButton--;
		}
		buttons[activeButton].setActive();
		break;
	case sf::Keyboard::Down : // Down arrow
		buttons[activeButton].setInactive();
		if(activeButton == MAX_BUTTONS-1) {
			activeButton = 0;
		} else {
			activeButton++;
		}
		buttons[activeButton].setActive();
		break;
	default: break;
	}
}

StateAction MainMenuState::shouldAct() {
	if(activeButton == 0) {
		return StateAction::START_GAME;
	} else if(activeButton == 2) {
		return StateAction::EXIT_GAME;
	} else {
		return StateAction::NONE;
	}
}