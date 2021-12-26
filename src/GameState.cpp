#include <iostream>
#include <string>

#include <SFML/Window.hpp>

#include "Animation.h"
#include "AssetsPaths.h"
#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, AssetsManager& gameAM, std::vector<MapBackground*> textureSheets,
    JSONFilePath& path, KeyList* gameSupportedKeys, Player& _player, Villagers& _villagers, Enemies& _enemies, MusicPath& _musicPath)
    : State(window), map(gameAM, textureSheets, path) {
	am = &gameAM;
	keybinds = gameSupportedKeys;
	player = _player;
	villagers = _villagers;
	enemies = _enemies;
	soundBuffer = am->getSoundBuffer(GASP.c);
	gaspSound.setBuffer(soundBuffer);
	previousKey = sf::Keyboard::Unknown;
	view = sf::View(player.get_position(), {float(window->getSize().x), float(window->getSize().y)});
	MusicPath* musicPath = gameAM.getMusic(_musicPath);
	music.openFromFile(*musicPath);
	music.setLoop(true);
	music.play();
}

GameState::~GameState() = default;

void GameState::update(const float& dt) {
	updateKeybinds(dt);
	if(clock.getElapsedTime().asSeconds() > .05f) {
		clock.restart();
	}
}

void GameState::render(sf::RenderWindow* window) {
	window->setView(view);
	map.render(*window);
}

void GameState::updateKeybinds(const float& dt) {}

StateAction GameState::handleKeys(sf::Keyboard::Key key) {
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
			player.animation.set_texture(am->getTexture(NINJA_WALK.c));
			player.move(action->first, &map);
			view.setCenter(player.animation.get_position());
			if(previousKey != key) {
				// play gasping gaspSound each time the player changes direction
				gaspSound.play();
			}
			previousKey = key;
		default: break;
		}
	}
	if(key == sf::Keyboard::C) result = StateAction::START_COMBAT;
	if(key == sf::Keyboard::Q) result = StateAction::EXIT_GAME;
	return result;
}

StateAction GameState::shouldAct() {
	return StateAction::NONE;
}

void GameState::quitStateActions() {
	std::cout << "Ending current game state" << std::endl;
}

void GameState::drawPlayer(sf::RenderWindow* window) {
	window->draw(player.animation.sprite);
	for(auto& v : villagers) {
		window->draw(v.animation.sprite);
		v.move(&map);
	}
	for(auto& e : enemies) {
		window->draw(e.animation.sprite);
		// e.move; once it's implemented
	}
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
