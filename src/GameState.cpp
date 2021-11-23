#include <iostream>

#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, AssetsManager& am) : State(window), map(am) {}

GameState::~GameState() = default;

void GameState::update(const float &dt)
{
    this->updateKeybinds(dt);
}

void GameState::render(sf::RenderTarget* target) {
	map.render(*target);
}

void GameState::checkIfQuitting() {
	State::checkIfQuitting();
}

void GameState::updateKeybinds(const float& dt) {
	this->checkIfQuitting();
}

void GameState::updateMap(const float &dt, sf::Vector2f playerPos)
{
    this->map.update(playerPos);
}

void GameState::quitStateActions() {
	std::cout << "Ending current game state" << std::endl;
}
