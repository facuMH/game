#include <iostream>

#include <SFML/Window.hpp>

#include "Animation.h"
#include "AssetsPaths.h"
#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, AssetsManager& am) : State(window), map(am), am(&am) {
	Texture* play_text = am.getTexture(IDLE.c);
	Animation player_animation(play_text, sf::IntRect(65, 55, 45, 50), Interval(162, 0), Position(50, 50));
	player = Character("Adventurer", Stats(15, 20, 50, 30), player_animation);
}

GameState::~GameState() = default;

void GameState::update(const float& dt) {
	this->updateKeybinds(dt);
	if(clock.getElapsedTime().asSeconds() > .05f) {
		player_idle();
		clock.restart();
	}
}

void GameState::render(sf::RenderTarget* target) {
	map.render(*target);
	target->draw(player.animation.sprite);
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

void GameState::handleKeys(sf::Keyboard::Key key) {
	switch(key) {
	case sf::Keyboard::Right: // Right arrow
	case sf::Keyboard::Left:  // Left arrow
	case sf::Keyboard::Up:    // Up arrow
	case sf::Keyboard::Down:  // Down arrow
		player.animation.set_texture(*am->getTexture(RUN.c));
		player.move(key);
		break;
	default: player_idle(); break;
	}
}

void GameState::player_idle() {
	player.animation.set_texture(*am->getTexture(IDLE.c));
	player.animation.next();
}