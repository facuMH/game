#include <iostream>

#include "AssetsPaths.h"
#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, AssetsManager& am, const std::string& level) : State(window), map(am, level) {}

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
CombatState::CombatState(sf::RenderWindow* window, AssetsManager& am, Party p, Enemies e, const std::string& level) : State(window), map(am, level) {
	party = p;
	enemies = e;
	std::cout << "New Combat\n";
}

CombatState::~CombatState() {}

void CombatState::update(const float& dt) {
	updateKeybinds(dt);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) enemies = {};
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