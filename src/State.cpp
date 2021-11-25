#include "State.h"

State::State(sf::RenderWindow* window) {
	this->window = window;
}

State::~State() = default;

void State::checkIfQuitting() {
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { this->isQuitting = true; }

	// else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
	//{
	// this->isQuitting = true;
	//}
}

const bool& State::isQuit() const {
	return this->isQuitting;
}