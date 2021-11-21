#include <iostream>
#include <vector>

#include "GameState.h"

// --- GAME STATE
GameState::GameState(sf::RenderWindow* window) : State(window) {}

GameState::~GameState() {}

void GameState::render(sf::RenderTarget* target) {
	map.render(*target);
}
void GameState::update(const float& dt) {
	this->updateKeybinds(dt);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { std::cout << "A pressed" << std::endl; }
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

CombatState::CombatState(sf::RenderWindow* window, Party p, Enemies e) : State(window) {
	party = p;
	enemies = e;
}

// --- COMBAT STATE

CombatState::CombatState(sf::RenderWindow* window, Party p, Enemies e) : State(window) {
	party = p;
	enemies = e;
}

CombatState::~CombatState() {}

void CombatState::update(const float& dt) {
	this->updateKeybinds(dt);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { std::cout << "A pressed" << std::endl; }
}

void CombatState::render(sf::RenderTarget* target) {}

bool CombatState::shouldQuit() {
	return enemies.empty() || party.empty();
}

void CombatState::updateKeybinds(const float& dt) {
	shouldQuit();
}

void CombatState::quitStateActions() {
	std::cout << "Ending current game state" << std::endl;
}