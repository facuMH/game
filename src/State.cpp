#include "State.h"

State::State(sf::RenderWindow* window) {
	this->window = window;
}

State::~State() = default;

bool State::shouldQuit() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
    isQuitting = true;
  }
  return isQuitting;
}

void State::checkIfQuitting() {
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { this->isQuitting = true; }
}

const bool& State::isQuit() const {
	return this->isQuitting;
}