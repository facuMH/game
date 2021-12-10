#include <iostream>
#include <string>

#include <SFML/Window.hpp>

#include "Animation.h"
#include "AssetsPaths.h"
#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, AssetsManager& gameAM, std::vector<MapBackground*> textureSheets,
    JSONFilePath& path, KeyList* gameSupportedKeys)
    : State(window), map(gameAM, textureSheets, path) {
	am = &gameAM;
	keybinds = gameSupportedKeys;
	Texture* play_text = am->getTexture(IDLE.c);
	Animation player_animation(play_text, sf::IntRect(65, 55, 45, 50), Interval(162, 0), Position(50, 50));
	player = Character("Adventurer", Stats(15, 20, 50, 30), player_animation);
	soundBuffer = am->getSoundBuffer(GASP.c);
	sound.setBuffer(soundBuffer);
	previousKey = sf::Keyboard::Unknown;

	MusicPath* musicPath = gameAM.getMusic(VILLAGE_MUSIC.c);
	music.openFromFile(*musicPath);
	music.play();
}

GameState::~GameState() = default;

void GameState::update(const float& dt) {
	updateKeybinds(dt);
	if(clock.getElapsedTime().asSeconds() > .05f) {
		playerIdle();
		clock.restart();
	}
}

void GameState::render(sf::RenderTarget* target) {
	map.render(*target);
	target->draw(player.animation.sprite);
}

void GameState::updateKeybinds(const float& dt) {}

StateAction GameState::handleKeys(sf::Keyboard::Key key, sf::View* view) {
	StateAction result = StateAction::NONE;
	auto action = std::find_if(keybinds->begin(), keybinds->end(),
	    [key](const std::pair<KeyAction, sf::Keyboard::Key>& v) { return key == v.second; });
	if(action != keybinds->end()) {
		switch(action->first) {
		case KeyAction::BACK: result = StateAction::EXIT_GAME; break;
		case KeyAction::UP:
		case KeyAction::DOWN:
		case KeyAction::RIGHT:
		case KeyAction::LEFT:
			player.animation.set_texture(am->getTexture(RUN.c));
			player.move(action->first, view);
			if(previousKey != key) {
				// play gasping sound each time the player changes direction
				sound.play();
			}
			previousKey = key;
		default: playerIdle(); break;
		}
	}
	if(key == sf::Keyboard::C) result = StateAction::START_COMBAT;
	if(key == sf::Keyboard::Q) result = StateAction::EXIT_GAME;
	return result;
}

void GameState::playerIdle() {
	player.animation.set_texture(am->getTexture(IDLE.c));
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
void GameState::stopMusic() {
	music.stop();
}
void GameState::resumeMusic() {
	music.play();
}
