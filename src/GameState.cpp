#include <iostream>
#include <string>

#include <SFML/Window.hpp>

#include "AssetsPaths.h"
#include "DialogueBox.h"
#include "asset_data.h"
#include "states/GameState.h"

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

	soundBuffers.emplace("gasp", am->getSoundBuffer(GASP.c));
	soundBuffers.emplace("interaction bling", am->getSoundBuffer(INTERACTION_BLING.c));

	for(auto& sb : soundBuffers) {
		sf::Sound sound;
		sound.setBuffer(sb.second);
		sounds.emplace(sb.first, sound);
	}

	previousKey = sf::Keyboard::Unknown;

	view = sf::View(player.get_position(), {720.0, 480.0});
	MusicPath* musicPath = gameAM.getMusic(_musicPath);
	music.openFromFile(*musicPath);
	music.setLoop(true);
	music.play();
}

/// Constructor for house GameState: No villagers here, but monsters and item
GameState::GameState(sf::RenderWindow* window, AssetsManager& gameAM, std::vector<MapBackground*> textureSheets,
    JSONFilePath& path, KeyList* gameSupportedKeys, Player& _player, Enemies& _enemies, MusicPath& _musicPath,
    Object* _item, DoorNumber _doorNumber)
    : State(window), map(gameAM, textureSheets, path) {
	std::cout << "New house state" << std::endl;
	am = &gameAM;
	keybinds = gameSupportedKeys;
	player = _player;
	enemies = _enemies;
	isHouse = true;
	doorNumber = _doorNumber;
	inDialogue = false;
	item = _item;
	if(item != nullptr) item->animation.set_position({player.get_position().x + 2, player.get_position().y});

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

	if(!itemPicked && item != nullptr) window->draw(item->animation.sprite);
}

void GameState::updateKeybinds(const float& dt) {}

StateAction GameState::handleKeys(sf::Keyboard::Key key) {
	StateAction result = StateAction::NONE;
	Name interactWith;
	auto action = std::find_if(keybinds->begin(), keybinds->end(),
	    [key](const std::pair<KeyAction, sf::Keyboard::Key>& v) { return key == v.second; });
	if(action != keybinds->end()) {
		switch(action->first) {
		case KeyAction::PAUSE: result = StateAction::PAUSE_GAME; break;
		case KeyAction::BACK: result = StateAction::EXIT_GAME; break;
		case KeyAction::UP:
		case KeyAction::DOWN:
		case KeyAction::RIGHT:
		case KeyAction::LEFT:
			if(!inDialogue) { // Player cannot move while in dialogue
				player.move(action->first, &map);
				view.setCenter(player.animation.get_position());
				if(previousKey != key && !isHouse) {
					sounds.find("gasp")->second.play();
				}
				if(getCurrentDoorNumber(player.get_position()) != 0) {
					if(!isHouse) {
						result = StateAction::START_HOUSE;
					} else {
						result = StateAction::EXIT_HOUSE;
					}
				}
				previousKey = key;
			}
			break;
		case KeyAction::INTERACT:
			interactWith = getEntityInInteractionRange(player.animation.get_position());
			if(!isHouse) {
				if(!interactWith.empty()) {
					startDialogue(interactWith);
				}
			} else {
				if(interactWith == enemies[0].name)
					result = StateAction::START_COMBAT;
				else if(interactWith == item->getName()) {
					if(item->can_equip) player.equip(item);
					itemPicked = true;
					result = StateAction::PICK_ITEM;
				}
			}
		default: break;
		}
	}
	if(key == sf::Keyboard::Q) result = StateAction::EXIT_GAME;
	if(key == sf::Keyboard::I && !inDialogue) result = StateAction::OPEN_INVENTORY;
	// BEWARE: using this will directly move the item into the player inventory
	// and since items are unique, it will not show up at the house.
	if(key == sf::Keyboard::Y) result = StateAction::ADD_ITEM;
	return result;
}


StateAction GameState::shouldAct() {
	return StateAction::NONE;
}

void GameState::quitStateActions() {
	if(isHouse) {
		std::cout << "Ending house state" << std::endl;
	} else {
		std::cout << "Ending game state" << std::endl;
	}
}

void GameState::drawPlayer(sf::RenderWindow* window) {
	window->draw(player.animation.sprite);
	for(auto& v : villagers) {
		window->draw(v.animation.sprite);
		if(!inDialogue) {
			v.move(&v.animation, &map);
		}
	}
	for(auto& e : enemies) {
		window->draw(e.animation.sprite);
		e.move(&e.animation, &map);
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
	return player.animation.get_position();
}

void GameState::startDialogue(Name& characterName) {
	inDialogue = true;
	sounds.find("interaction bling")->second.play();
	std::string faceTextureName;
	for(auto& v : villagers) {
		if(v.name == characterName) {
			faceTextureName = v.faceTexturePath;
			break;
		}
	}
	dialogueBox = DialogueBox(characterName, faceTextureName, player.get_position());
}

Name GameState::getEntityInInteractionRange(Position position) {
	Name n;
	// if entity is a villager
	for(auto& v : villagers) {
		if(positionsInRange(position, v.animation.get_position(), 15.f)) {
			n = v.name;
		}
	}
	// if entity is an enemy
	for(auto& e : enemies) {
		if(positionsInRange(position, e.animation.get_position(), 15.f)) {
			n = e.name;
		}
	}
	// if entity is an item
	if(item != nullptr && positionsInRange(position, item->animation.get_position(), 15.f)) {
		n = item->getName();
	}
	return n;
}
void GameState::playErrorSound() {}
