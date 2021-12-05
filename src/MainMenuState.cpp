#include <algorithm>

#include <SFML/Window.hpp>

#include "AssetsPaths.h"
#include "MainMenuState.h"

MainMenuState::MainMenuState(
    sf::RenderWindow* window, AssetsManager& am, std::vector<MapBackground*> textureSheets, KeyList* gameSupportedKeys)
    : State(window) {
	supportedKeys = gameSupportedKeys;
	initBackground(window, am, textureSheets);
	initFonts(am);
	initButtons();
	soundBuffer = am.getSoundBuffer(GASP.c);
	sound.setBuffer(soundBuffer);
}

void MainMenuState::initBackground(sf::RenderWindow* window, AssetsManager& am, std::vector<MapBackground*> textureSheets) {
	background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	backgroundTexture = *am.getTexture(BACKGROUND.c);
	background.setTexture(&backgroundTexture);
	// TODO: load background from textureSheets and Designs
}

void MainMenuState::initFonts(AssetsManager& am) {
	font = *am.getFont(DOSIS.c);
}

void MainMenuState::initButtons() {
	buttons.push_back(Button(300, 150, 150, 50, &font, "New Game", GREY, LIGHTGREY, BLACK));
	activeButton = 0;
	buttons[activeButton].setActive();
	buttons.push_back(Button(300, 200, 150, 50, &font, "Settings", GREY, LIGHTGREY, BLACK));
	buttons.push_back(Button(300, 250, 150, 50, &font, "QUIT", GREY, LIGHTGREY, BLACK));
}

MainMenuState::~MainMenuState() = default;

void MainMenuState::endState() {
	std::cout << "Ending Main Menu!"
	          << "\n";
}

void MainMenuState::updateInput(const float& dt) {}

void MainMenuState::updateButtons() {
	/*Updates all the buttons in the state and handles their functionality*/
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

void MainMenuState::updateKeybinds(const float& dt) {}

bool MainMenuState::shouldQuit() {
	return isQuit();
}

void MainMenuState::quitStateActions() {
	std::cout << "Ending current game state" << std::endl;
}

StateAction MainMenuState::handleKeys(sf::Keyboard::Key key, sf::View* view) {
	auto action = std::find_if(supportedKeys->begin(), supportedKeys->end(),
	    [key](const std::pair<KeyAction, sf::Keyboard::Key>& v) { return key == v.second; });
	if(action != supportedKeys->end()) {
		switch(action->first) {
		case KeyAction::UP: // Up arrow
			buttons[activeButton].setInactive();
			if(activeButton == 0) {
				activeButton = MAX_BUTTONS - 1;
			} else {
				activeButton--;
			}
			buttons[activeButton].setActive();
			break;
		case KeyAction::DOWN: // Down arrow
			buttons[activeButton].setInactive();
			if(activeButton == MAX_BUTTONS - 1) {
				activeButton = 0;
			} else {
				activeButton++;
			}
			buttons[activeButton].setActive();
			break;
		default: break;
		}
	}
	// play gasping sound each time change button.
	sound.play();
	return StateAction::NONE;
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