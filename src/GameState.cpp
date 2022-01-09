#include <iostream>
#include <string>

#include <SFML/Window.hpp>

#include "Animation.h"
#include "AssetsPaths.h"
#include "DialogueBox.h"
#include "GameState.h"

/// Constructor for village GameState: There are several villagers, but no enemies, as they hide in the houses
GameState::GameState(sf::RenderWindow* window, AssetsManager& gameAM, std::vector<MapBackground*> textureSheets,
    JSONFilePath& path, KeyList* gameSupportedKeys, Player& _player, Villagers& _villagers, MusicPath& _musicPath)
    : State(window), map(gameAM, textureSheets, path) {
	am = &gameAM;
	keybinds = gameSupportedKeys;
	player = _player;
	villagers = _villagers;
	isHouse = false;
	inDialogue = false;
	soundBuffer = am->getSoundBuffer(GASP.c);
	gaspSound.setBuffer(soundBuffer);
	previousKey = sf::Keyboard::Unknown;
	// view = sf::View(player.get_position(), {float(window->getSize().x), float(window->getSize().y)});
	view = sf::View(player.get_position(), {720.0, 480.0});
	MusicPath* musicPath = gameAM.getMusic(_musicPath);
	music.openFromFile(*musicPath);
	music.setLoop(true);
	music.play();
	windowHeight = view.getCenter().y;
}

/// Constructor for house GameState: No villagers here, but monsters
GameState::GameState(sf::RenderWindow* window, AssetsManager& gameAM, std::vector<MapBackground*> textureSheets,
    JSONFilePath& path, KeyList* gameSupportedKeys, Player& _player, Enemies& _enemies, MusicPath& _musicPath)
    : State(window), map(gameAM, textureSheets, path) {
	am = &gameAM;
	keybinds = gameSupportedKeys;
	player = _player;
	enemies = _enemies;
	isHouse = true;
	inDialogue = false;
	soundBuffer = am->getSoundBuffer(GASP.c);
	gaspSound.setBuffer(soundBuffer);
	previousKey = sf::Keyboard::Unknown;
	// view = sf::View(player.get_position(), {float(window->getSize().x), float(window->getSize().y)});
	view = sf::View(player.get_position(), {720.0, 480.0});
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
	if(inDialogue) {
		dialogueBox.update(dt);
		if(dialogueBox.textDone()) {
			inDialogue = false;
		}
	}
}

void GameState::render(sf::RenderWindow* window) {
	window->setView(view);
	map.render(*window);
	if(inDialogue) {
		dialogueBox.render(window);
	}
}

void GameState::updateKeybinds(const float& dt) {}

StateAction GameState::handleKeys(sf::Keyboard::Key key) {
	StateAction result = StateAction::NONE;
	Name interactWith = "";
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
			view.setCenter(player.get_position());
			if(previousKey != key) {
				// play gasping gaspSound each time the player changes direction
				gaspSound.play();
			}
			if(getCurrentDoorNumber(player.get_position()) != 0) {
				if(!isHouse) {
					result = StateAction::START_HOUSE;
				} else {
					result = StateAction::EXIT_HOUSE;
				}
			}
			previousKey = key;
		default: break;
		}
	}
	if(key == sf::Keyboard::C) result = StateAction::START_COMBAT;
	if(key == sf::Keyboard::Q) result = StateAction::EXIT_GAME;
	if(key == sf::Keyboard::P) {
		interactWith = "Old Man";
		startDialogue(interactWith, windowHeight);
	}
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
		e.move(&map);
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

DoorNumber GameState::getCurrentDoorNumber(Position position) {
	return map.getTileDoorNumber(position);
}

std::vector<std::pair<Position, DoorNumber>> GameState::listHousePositions() {
	return map.getHousePositions();
}

Position GameState::getCurrentPlayerPosition() {
	return player.get_position();
}

void GameState::startDialogue(Name& characterName, float windowHeight) {
	inDialogue = true;
	dialogueBox = DialogueBox(characterName, windowHeight);
}
