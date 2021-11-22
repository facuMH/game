#include <iostream>

#include "AssetsPaths.h"
#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, AssetsManager& am) : State(window), map(am) {}

GameState::~GameState() = default;

void GameState::update(const float& dt) {
	this->updateKeybinds(dt);
}

void GameState::render(sf::RenderTarget* target) {
	map.render(*target);
}

bool GameState::shouldQuit() {
	return State::shouldQuit();
}

void GameState::updateKeybinds(const float& dt) {
	shouldQuit();
}

void GameState::quitStateActions() {
	std::cout << "Ending current game state" << std::endl;
}

// --- COMBAT STATE
CombatState::CombatState(sf::RenderWindow* window, AssetsManager& am, Party p, Enemies e) : State(window), map(am) {
	party = p;
	enemies = e;
	map.updateLevel(am, COMBATLEVEL.c);
}

CombatState::~CombatState() {}

void CombatState::update(const float& dt) {
	this->updateKeybinds(dt);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { std::cout << "A pressed" << std::endl; }
}

void CombatState::render(sf::RenderTarget* target) {
	map.render(*target);
}

bool CombatState::shouldQuit() {
	return enemies.empty() || party.empty();
}

void CombatState::updateKeybinds(const float& dt) {
	shouldQuit();
}

void CombatState::quitStateActions() {
	std::cout << "Ending current game state" << std::endl;
}