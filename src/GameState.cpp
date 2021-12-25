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

	Texture* play_text = am->getTexture(NINJA_WALK.c);
	Animation player_animation(play_text, sf::IntRect(0, 0, TILESIZE, TILESIZE), Position(50, 50));
	player = Player("Adventurer", Stats(15, 20, 50, 30), player_animation);

	Villager girl = createVillager(EGG_GIRL_WALK.c, "Egg Girl", Position(300, 50), MovementType::VERTICAL, 0.3f);
	villagers.push_back(girl);

	Villager old_man = createVillager(OLD_MAN_WALK.c, "Old Man", Position(50, 150), MovementType::HORIZONTAL, 0.4f);
	villagers.push_back(old_man);

	Villager princess = createVillager(PRINCESS_WALK.c, "Princess", Position(230, 150), MovementType::VERTICAL, 0.2f);
	villagers.push_back(princess);

	soundBuffer = am->getSoundBuffer(GASP.c);
	gaspSound.setBuffer(soundBuffer);
	previousKey = sf::Keyboard::Unknown;
	view = sf::View(player.get_position(), {720.0, 480.0});
	MusicPath* musicPath = gameAM.getMusic(VILLAGE_MUSIC.c);
	music.openFromFile(*musicPath);
	music.setLoop(true);
	music.play();
}

Villager GameState::createVillager(
    const std::string& textureName, Name name, Position position, MovementType movementDirection, float stepsize) {
	Texture* tex = am->getTexture(textureName);
	Animation anim(tex, sf::IntRect(0, 0, TILESIZE, TILESIZE), position);
	Position endPosition;
	if(movementDirection == MovementType::HORIZONTAL) {
		endPosition = {position.x + 50, position.y};
	} else {
		endPosition = {position.x, position.y + 60};
	}
	return {anim, name, movementDirection, endPosition, stepsize};
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
			player.move(action->first, &view, &map);
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