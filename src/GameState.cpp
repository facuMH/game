#include <iostream>
#include <string>

#include <SFML/Window.hpp>

#include "Animation.h"
#include "AssetsPaths.h"
#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, AssetsManager& gameAM, std::vector<MapBackground*> textureSheets, std::vector<Design*> levelDesigns)
    : State(window), map(gameAM, textureSheets, levelDesigns) {
	am = &gameAM;
	Texture* play_text = am->getTexture(IDLE.c);
	Animation player_animation(play_text, sf::IntRect(65, 55, 45, 50), Interval(162, 0), Position(50, 50));
	player = Character("Adventurer", Stats(15, 20, 50, 30), player_animation);
}

GameState::~GameState() = default;

void GameState::update(const float& dt) {
	this->updateKeybinds(dt);
	if(clock.getElapsedTime().asSeconds() > .05f) {
		playerIdle();
		clock.restart();
	}
}

void GameState::render(sf::RenderTarget* target) {
	map.render(*target);
	target->draw(player.animation.sprite);
}

void GameState::updateKeybinds(const float& dt) {
	shouldQuit();
}

StateAction GameState::handleKeys(sf::Keyboard::Key key, sf::View* view) {
	StateAction result = StateAction::NONE;
	switch(key) {
	case sf::Keyboard::Q: result = StateAction::EXIT_GAME; break;
	case sf::Keyboard::Right: // Right arrow
	case sf::Keyboard::Left:  // Left arrow
	case sf::Keyboard::Up:    // Up arrow
	case sf::Keyboard::Down:  // Down arrow
		player.animation.set_texture();
		player.move(key, view);
		break;
	case sf::Keyboard::C:
		result = StateAction::START_COMBAT;
		break;
	default: playerIdle(); break;
	}
	return result;
}

void GameState::playerIdle() {
	player.animation.set_texture();
	player.animation.next();
}

StateAction GameState::shouldAct() {
	return StateAction::NONE;
}

void GameState::quitStateActions() {
	std::cout << "Ending current game state" << std::endl;
}

void GameState::drawPlayer(sf::RenderWindow* window) {
	window->draw(player.animation.sprite);
}

bool GameState::shouldQuit() {
	return isQuit();
}