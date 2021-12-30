#include <algorithm>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "AssetsPaths.h"
#include "PauseGameState.h"

#include "definitions.h"

PauseGameState::PauseGameState(sf::RenderWindow* window, AssetsManager& am, KeyList* gameSupportedKeys)
    : State(window) {
	view = window->getDefaultView();
	initBackground(window);
	initFonts(am);
	initText(window);
	// Settings should keep on playing music from Menu

	supportedKeys = gameSupportedKeys;	

}

PauseGameState::~PauseGameState() = default;

void PauseGameState::initBackground(sf::RenderWindow* window) {
	sf::Vector2u currentSize = window->getSize();
	background.setSize(sf::Vector2f(currentSize));
	background.setPosition(0,0);
	background.setFillColor(sf::Color(0,0,0,150));

}

void PauseGameState::initFonts(AssetsManager& am) {
	font = *am.getFont(DOSIS.c);
}

void PauseGameState::initText(sf::RenderWindow* window) {
	text.setFont(font);
	text.setString(sf::String("PAUSED"));
	text.setCharacterSize(14);
	text.setStyle(sf::Text::Bold);
	sf::Vector2u currentSize = window->getSize();
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(currentSize.x / 2.0f, currentSize.y / 2.0f);
}

void PauseGameState::endState() {
	std::cout << "Ending Settings Menu!\n";
}

void PauseGameState::updateInput(const float& dt) {}

void PauseGameState::update(const float& dt) {
	updateInput(dt);
}

void PauseGameState::render(sf::RenderWindow* window) {
	window->setView(view);
	window->draw(background);
	window->draw(text);
}

StateAction PauseGameState::handleKeys(sf::Keyboard::Key key) {
	StateAction result = StateAction::NONE;
	auto action = std::find_if(supportedKeys->begin(), supportedKeys->end(),
	    [key](const std::pair<KeyAction, sf::Keyboard::Key>& v) { return key == v.second; });
	if(action != supportedKeys->end()) {
		switch(action->first) {
		case KeyAction::PAUSE: result = StateAction::RESUME_GAME; std::cout << "File:" << __FILE__ << ", Line:" << __LINE__ << std::endl; break;
		default: break;
		}
	}

	return result;
}

void PauseGameState::updateKeybinds(const float& dt) {}

void PauseGameState::quitStateActions() {
	std::cout << "Ending current game state" << std::endl;
}

bool PauseGameState::shouldQuit() {
	return isQuit();
}

void PauseGameState::drawPlayer(sf::RenderWindow* window) {}

StateAction PauseGameState::shouldAct() {
	return StateAction::NONE;
}

void PauseGameState::stopMusic() { }

void PauseGameState::resumeMusic() { }
