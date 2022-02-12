#include <algorithm>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "AssetsPaths.h"
#include "states/PauseGameState.h"

#include "definitions.h"

constexpr int MAX_RESOLUTION_COUNT = 2;

PauseGameState::PauseGameState(sf::RenderWindow* window, AssetsManager& am, KeyList* gameSupportedKeys)
    : State(window) {
	view = window->getDefaultView();
	initBackground(window, am);
	initFonts(am);
	initText(window);
	initButtons(window);
	supportedKeys = gameSupportedKeys;
}

PauseGameState::~PauseGameState() = default;

void PauseGameState::initBackground(sf::RenderWindow* window, AssetsManager& am) {
	background.setTexture(am.getTexture(SETTING_BACKGROUND.c));
	background.setSize(view.getSize());

	sf::Vector2u currentSize = window->getSize();
	container.setSize(sf::Vector2f(currentSize));
	container.setFillColor(TRANSPARENT_BLACK);
}

void PauseGameState::initFonts(AssetsManager& am) {
	font = *am.getFont(DOSIS.c);
}

void PauseGameState::initText(sf::RenderWindow* window) {
	text.setFont(font);
	text.setString(sf::String("GAME PAUSED"));
	text.setCharacterSize(20);
	text.setStyle(sf::Text::Bold);
	sf::Vector2u currentSize = window->getSize();
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(currentSize.x / 2.0f, currentSize.y / 4.0f);
}

void PauseGameState::initButtons(sf::RenderWindow* window) {
	// button size
	unsigned int bWidth = 150;
	unsigned int bHeight = 40;
	activeButton = 0;
	auto offsetX = 2 * bWidth;
	auto offsetY = 2 * bHeight;

	auto center = getWindowCenter(*window);
	center.x -= offsetX;
	center.y -= offsetY;
	auto bPos = center.x;

	buttons.push_back(Button(bPos, center.y, bWidth, bHeight, &font, "RESUME", GREY, LIGHTGREY, sf::Color::Black));
	bPos = bPos + 3 * bWidth;
	buttons.push_back(Button(bPos, center.y, bWidth, bHeight, &font, "QUIT", GREY, LIGHTGREY, sf::Color::Black));
	buttons[activeButton].setInactive();
}

void PauseGameState::updateButtons() {
	for(auto it : buttons) {
		it.update(mousePosView);
	}
}

void PauseGameState::renderButtons(sf::RenderWindow* window) {
	for(auto& it : buttons) {
		it.render(window);
	}
}

void PauseGameState::updateMousePositions() {
	mousePoseWindow = State::getMouse();
	mousePosView = getPos(mousePoseWindow);
}

void PauseGameState::endState() {
	std::cout << "Ending Pause Game State!\n";
}

void PauseGameState::updateInput(const float& dt) {}


void PauseGameState::update(const float& dt) {
	updateMousePositions();
	updateInput(dt);
	updateButtons();
}

void PauseGameState::render(sf::RenderWindow* window) {
	window->setView(view);
	window->draw(background);
	window->draw(container);
	window->draw(text);
	renderButtons(window);
}

StateAction PauseGameState::handleKeys(sf::Keyboard::Key key) {
	StateAction result = StateAction::NONE;
	auto action = std::find_if(supportedKeys->begin(), supportedKeys->end(),
	    [key](const std::pair<KeyAction, sf::Keyboard::Key>& v) { return key == v.second; });
	if(action != supportedKeys->end()) {
		switch(action->first) {
		case KeyAction::RIGHT: // Right arrow
			buttons[activeButton].setInactive();
			if(activeButton == 0) {
				activeButton = MAX_RESOLUTION_COUNT - 1;
			} else {
				activeButton--;
			}
			buttons[activeButton].setActive();

			break;
		case KeyAction::LEFT: // Left arrow
			buttons[activeButton].setInactive();
			if(activeButton == MAX_RESOLUTION_COUNT - 1) {
				activeButton = 0;
			} else {
				activeButton++;
			}
			buttons[activeButton].setActive();
			break;
		case KeyAction::PAUSE: result = StateAction::RESUME_GAME; break;
		default: break;
		}
	}
	return result;
}

void PauseGameState::updateKeybinds(const float& dt) {}

void PauseGameState::quitStateActions() {
	std::cout << "Ending pause game state" << std::endl;
}

bool PauseGameState::shouldQuit() {
	return isQuit();
}

void PauseGameState::drawPlayer(sf::RenderWindow* window) {}

StateAction PauseGameState::shouldAct() {
	if(activeButton == 0) {
		return StateAction::RESUME_GAME;
	} else if(activeButton == 1) {
		return StateAction::EXIT_GAME;
	} else {
		return StateAction::NONE;
	}
}

void PauseGameState::stopMusic() {}

void PauseGameState::resumeMusic() {}
void PauseGameState::playErrorSound() {}
