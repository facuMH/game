#include <algorithm>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "AssetsPaths.h"
#include "Button.h"
#include "LoadGameState.h"

#include "definitions.h"

constexpr int MAX_RESOLUTION_COUNT = 6;

LoadGameState::LoadGameState(sf::RenderWindow* window, AssetsManager& am, KeyList* gameSupportedKeys)
    : State(window), activeButton(0) {
	view = window->getDefaultView();
	initBackground(window, am);
	initFonts(am);
	soundBuffer = am.getSoundBuffer(MENU_BLIP.c);
	blipSound.setBuffer(soundBuffer);

	supportedKeys = gameSupportedKeys;
	initButtons(window);
	save_game.saveCurrentGame();
}

LoadGameState::~LoadGameState() = default;

void LoadGameState::initBackground(sf::RenderWindow* window, AssetsManager& am) {
	background.setTexture(am.getTexture(SETTING_BACKGROUND.c));
	background.setSize(view.getSize());
}

void LoadGameState::initFonts(AssetsManager& am) {
	font = *am.getFont(DOSIS.c);
}

// creating buttons showing different resolution
void LoadGameState::initButtons(sf::RenderWindow* window) {

	// button size
	unsigned int bWidth = 150;
	unsigned int bHeight = 40;
	auto offsetX = 0.5 * bWidth;
	auto offsetY = 4 * bHeight;

	auto center = getWindowCenter(*window);
	center.x -= offsetX;
	center.y -= offsetY;
	auto bPos = center.y;

	buttons.push_back(Button(center.x, bPos, bWidth, bHeight, &font, "LOAD GAME 1", GREY, LIGHTGREY, sf::Color::Black));
	bPos += bHeight;
	buttons.push_back(Button(center.x, bPos, bWidth, bHeight, &font, "LOAD GAME 2", GREY, LIGHTGREY, sf::Color::Black));
	bPos += bHeight;
	buttons.push_back(Button(center.x, bPos, bWidth, bHeight, &font, "LOAD GAME 3", GREY, LIGHTGREY, sf::Color::Black));
	bPos += bHeight;
	buttons.push_back(Button(center.x, bPos, bWidth, bHeight, &font, "LOAD GAME 4", GREY, LIGHTGREY, sf::Color::Black));
	bPos += bHeight;
	buttons.push_back(Button(center.x, bPos, bWidth, bHeight, &font, "LOAD GAME 5", GREY, LIGHTGREY, sf::Color::Black));
	bPos += bHeight;
	buttons.push_back(Button(center.x, bPos, bWidth, bHeight, &font, "BACK", GREY, LIGHTGREY, sf::Color::Black));

	activeButton = 0;

	buttons[activeButton].setActive();
}

void LoadGameState::updateButtons() {
	for(auto it : buttons) {
		it.update(mousePosView);
	}
}

void LoadGameState::renderButtons(sf::RenderWindow* window) {
	for(auto& it : buttons) {
		it.render(window);
	}
}

void LoadGameState::updateMousePositions() {
	mousePoseWindow = State::getMouse();
	mousePosView = getPos(mousePoseWindow);
}

void LoadGameState::endState() {
	std::cout << "Ending Load Game Menu!\n";
}

void LoadGameState::updateInput(const float& dt) {}

void LoadGameState::update(const float& dt) {
	updateMousePositions();
	updateInput(dt);
	updateButtons();
}


void LoadGameState::render(sf::RenderWindow* window) {
	window->setView(view);
	window->draw(background);
	renderButtons(window);
}

StateAction LoadGameState::handleKeys(sf::Keyboard::Key key) {
	auto action = std::find_if(supportedKeys->begin(), supportedKeys->end(),
	    [key](const std::pair<KeyAction, sf::Keyboard::Key>& v) { return key == v.second; });
	if(action != supportedKeys->end()) {
		switch(action->first) {
		case KeyAction::UP: // Up arrow
			buttons[activeButton].setInactive();
			if(activeButton == 0) {
				activeButton = MAX_RESOLUTION_COUNT - 1;
			} else {
				activeButton--;
			}
			buttons[activeButton].setActive();

			break;
		case KeyAction::DOWN: // Down arrow
			buttons[activeButton].setInactive();
			if(activeButton == MAX_RESOLUTION_COUNT - 1) {
				activeButton = 0;
			} else {
				activeButton++;
			}
			buttons[activeButton].setActive();
			break;
		default: break;
		}
	}
	// play gasping gaspSound each time change button.
	blipSound.play();
	return StateAction::NONE;
}

void LoadGameState::updateKeybinds(const float& dt) {}

void LoadGameState::quitStateActions() {
	std::cout << "Ending load game state" << std::endl;
}

bool LoadGameState::shouldQuit() {
	return isQuit();
}

void LoadGameState::drawPlayer(sf::RenderWindow* window) {}

StateAction LoadGameState::shouldAct() {
	return StateAction::EXIT_SETTING;
}

void LoadGameState::stopMusic() {
	music.stop();
}

void LoadGameState::resumeMusic() {
	music.play();
}
