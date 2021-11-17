#include "GameState.h"

#include <iostream>

GameState::GameState(sf::RenderWindow *window) : State(window) {}

GameState::~GameState() = default;

void GameState::update(const float &dt) {
  this->updateKeybinds(dt);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    std::cout << "A pressed" << std::endl;
  }
}

void GameState::render(sf::RenderTarget *target) {
    map.render(*target);
}

void GameState::checkIfQuitting() { State::checkIfQuitting(); }

void GameState::updateKeybinds(const float &dt) { this->checkIfQuitting(); }

void GameState::quitStateActions() {
  std::cout << "Ending current game state" << std::endl;
}
