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
	assetsManager = &gameAM;
	keybinds = gameSupportedKeys;
	player = _player;
	villagers = _villagers;
	isHouse = false;
	inDialogue = false;

	clearedForFinalBoss = false;
	setEntranceBlock(true);
	initSounds();

	previousKey = sf::Keyboard::Unknown;
	view = sf::View(player.get_position(), {720.0, 480.0});
	MusicPath* musicPath = gameAM.getMusic(_musicPath);
	music.openFromFile(*musicPath);
	music.setLoop(true);
	music.play();
}

/// Constructor for house GameState: No villagers here, but monsters and item
GameState::GameState(sf::RenderWindow* window, AssetsManager& _assetsManager, std::vector<MapBackground*> textureSheets,
    JSONFilePath& path, KeyList* gameSupportedKeys, Player& _player, Enemy& _enemy, MusicPath& _musicPath,
    Object* _item, DoorNumber _doorNumber)
    : State(window), map(_assetsManager, textureSheets, path) {
	assetsManager = &_assetsManager;
	keybinds = gameSupportedKeys;
	player = _player;
	enemy = _enemy;
	isHouse = true;
	doorNumber = _doorNumber;
	inDialogue = false;
	item = _item;
	if(item != nullptr) {
		item->animation.set_position({player.get_position().x + 2, player.get_position().y});
	} else {
		itemPicked = true;
	}

	view = sf::View(player.get_position(), {720.0, 480.0});
	MusicPath* musicPath = _assetsManager.getMusic(_musicPath);
	music.openFromFile(*musicPath);
	music.setLoop(true);
	music.play();
	initSounds();

	// The final boss holds a little monologue before the fight - as they always do.
	if(doorNumber == 7) {
		Name finalBoss = "Evil Grandpa";
		startDialogue(finalBoss);
	}
}

void GameState::initSounds() {
	soundBuffers.emplace("gasp", assetsManager->getSoundBuffer(GASP.c));
	soundBuffers.emplace("interaction bling", assetsManager->getSoundBuffer(INTERACTION_BLING.c));

	for(auto& sb : soundBuffers) {
		sf::Sound sound;
		sound.setBuffer(sb.second);
		sounds.emplace(sb.first, sound);
	}
}


GameState::~GameState() = default;

void GameState::update(const float& dt) {
	updateKeybinds(dt);
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
	if(!isHouse && !clearedForFinalBoss) {
		window->draw(entranceBlocker);
	}
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
				if(item != nullptr && interactWith == item->getName()) {
					if(item->can_equip) player.equip(item);
					itemPicked = true;
					result = StateAction::PICK_ITEM;
				} else if(!enemy.isEmpty() && interactWith == enemy.name) {
					result = StateAction::START_COMBAT;
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
	if(!enemy.isEmpty()) {
		window->draw(enemy.animation.sprite);
		enemy.move(&enemy.animation, &map);
	}
}

bool GameState::shouldQuit() {
	return isQuit();
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
	if(characterName == "Evil Grandpa") {
		faceTextureName = OLD_MAN_FACE.c;
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
	if(!enemy.isEmpty()) {
		if(positionsInRange(position, enemy.animation.get_position(), 15.f)) {
			n = enemy.name;
		}
	}
	// if entity is an item
	if(item != nullptr && positionsInRange(position, item->animation.get_position(), 15.f)) {
		n = item->getName();
	}
	return n;
}

void GameState::unblockEnemyTile() {
	if(!enemy.isEmpty()) {
		Enemy::setTileOccupation(&map, enemy.get_position(), false);
	}
}

int GameState::getExperienceFromEnemy() const {
	if(!enemy.isEmpty()) {
		return enemy.getExperience();
	} else {
		return 0;
	}
}
void GameState::setEntranceBlock(bool isBlocked) {
	std::vector<std::pair<Position, DoorNumber>> tmp = map.getHousePositions();
	Position finalHouseDoor;
	for(auto& pair : tmp) {
		if(pair.second == 7) {
			finalHouseDoor = pair.first;
		}
	}
	map.setTileOccupation(finalHouseDoor, isBlocked);

	if(isBlocked) {
		Texture* entranceBlockerTexture = assetsManager->getTexture(BLOCKER_IDLE.c);
		entranceBlocker.setTexture(*entranceBlockerTexture);
		entranceBlocker.setTextureRect(sf::IntRect(0, 0, 16, 16));
		entranceBlocker.setPosition(finalHouseDoor);
		Animation animation(entranceBlockerTexture, entranceBlocker.getTextureRect(), entranceBlocker.getPosition());
		Villager villager(
		    animation, "Skele Tony", MovementType::STILL, entranceBlocker.getPosition(), 0, BLOCKER_FACE.c);
		villagers.push_back(villager);
	} else {
		clearedForFinalBoss = true;
		villagers.pop_back();
	}
}
