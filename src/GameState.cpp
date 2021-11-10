#include "GameState.h"
#include <iostream>
#include <vector>

GameState::GameState(sf::RenderWindow *window) : State(window) {}

GameState::~GameState() {}

void GameState::update(const float &dt) {
  this->updateKeybinds(dt);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    std::cout << "A pressed" << std::endl;
  }
}

void GameState::render(sf::RenderTarget *target) {}

bool GameState::shouldQuit() { return State::shouldQuit(); }

void GameState::updateKeybinds(const float &dt) { shouldQuit(); }

void GameState::quitStateActions() {
  std::cout << "Ending current game state" << std::endl;
}

CombatState::CombatState(sf::RenderWindow *window, Party p, Enemies e)
    : State(window) {
  party = p;
  enemies = e;
}

CombatState::~CombatState() {}

void CombatState::update(const float &dt) {
  this->updateKeybinds(dt);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    std::cout << "A pressed" << std::endl;
  }
}

void CombatState::render(sf::RenderTarget *target) {}

bool CombatState::shouldQuit() { return enemies.empty() || party.empty(); }

void CombatState::updateKeybinds(const float &dt) { shouldQuit(); }

void CombatState::quitStateActions() {
  std::cout << "Ending current game state" << std::endl;
}