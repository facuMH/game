#include "State.h"

State::State(sf::RenderWindow *window) { this->window = window; }

State::~State() {}

void State::checkIfQuitting() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
    this->isQuitting = true;
  }
}

const bool &State::isQuit() const { return this->isQuitting; }
