#include <iostream>

#include "AssetsPaths.h"
#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, AssetsManager& am) : State(window), map(am) {
	//this->initKeybinds();
}

// void GameState::initKeybinds() {
//	std::ifstream ifs(KEYBIND);
//
//	if(ifs.is_open()) {
//		std::string key = "";
//		std::string key2 = "";
//
//		while(ifs >> key >> key2) {
//			this->keybinds[key] = this->supportedKeys->at(key2);
//		}
//	}
//	ifs.close();
//
//	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
//	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("A");
//	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("D");
//	this->keybinds["MOVE_UP"] = this->supportedKeys->at("W");
//	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("S");
//}


GameState::~GameState() = default;

void GameState::update(const float& dt) {
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

void GameState::quitStateActions() {
	std::cout << "Ending current game state" << std::endl;
}
