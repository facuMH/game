#include <iostream>
#include <string>

#include "AssetsPaths.h"
#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, AssetsManager& am, std::vector<MapBackground*> textureSheets, std::vector<Design*> levelDesigns)
    : State(window), map(am, textureSheets, levelDesigns) {}

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
void CombatState::addCombatString(const Character& c, AssetsManager& am) {
	sf::Text characterInfo{};
	characterInfo.setColor(sf::Color::Black);
	characterInfo.setFont(*am.getFont(ALEX.c));
	characterInfo.setString(std::string(" HP:") + std::to_string(c.currentStats.hp) + "/" + std::to_string(c.maxStats.hp));
	lifeCounters.emplace(c.name, characterInfo);
}

CombatState::CombatState(sf::RenderWindow* window, AssetsManager& am,               //
	std::vector<MapBackground *> textureSheets, std::vector<Design *> levelDesigns, //
	Party p, Enemies e) : State(window), map(am, textureSheets, levelDesigns) {
	party = p;
	enemies = e;
	std::cout << "New Combat\n";
	for(const auto& c : p) {
		addCombatString(c, am);
	}
	for(const auto& c : e) {
		addCombatString(c, am);
	}
}

CombatState::~CombatState() {}

void CombatState::update(const float& dt) {
	updateKeybinds(dt);
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
	// emptying enemies list here is purely for debug
	enemies = {};
	std::cout << "Ending current game state" << std::endl;
}