#include <algorithm>
#include <map>
#include <memory>

#include "AssetsPaths.h"
#include "Button.h"
#include "CombatState.h"
#include "Player.h"
#include "definitions.h"

void CombatState::addCombatString(const Player& player, AssetsManager& am) {
	sf::Text characterInfo{};

	characterInfo.setOutlineColor(sf::Color::Black);
	characterInfo.setFillColor(sf::Color::Black);
	characterInfo.setFont(font);
	characterInfo.setString(player.name + std::string(" HP:") + std::to_string(player.get_hp()) + "/"
	                        + std::to_string(player.maxStats.hp) + " MP:" + std::to_string(player.get_mana()) + "/"
	                        + std::to_string(player.maxStats.mana));
	lifeCounters.emplace(player.name, Button(initialText.x, initialText.y, 280, 40, characterInfo));
}

void CombatState::addActionMenu(const sf::RenderWindow* window) {
	auto center = Position{320, 300};
	center.y = center.y * 0.75f;
	unsigned int bWidth = 150;
	unsigned int bHeight = 40;
	actionButtons.push_back(
	    Button(center.x, center.y, bWidth, bHeight, &font, "Attack", DARKBLUE, LIGHTGREY, sf::Color::Black));
	center.y += bHeight;
	actionButtons.push_back(
	    Button(center.x, center.y, bWidth, bHeight, &font, "Special", DARKBLUE, LIGHTGREY, sf::Color::Black));
	center.y += bHeight;
	actionButtons.push_back(
	    Button(center.x, center.y, bWidth, bHeight, &font, "Item", DARKBLUE, LIGHTGREY, sf::Color::Black));
	center.y += bHeight;
	actionButtons.push_back(
	    Button(center.x, center.y, bWidth, bHeight, &font, "Skip", DARKBLUE, LIGHTGREY, sf::Color::Black));
	actionButtonActive = 0;
	actionButtons[actionButtonActive].setActive();
}

CombatState::CombatState(sf::RenderWindow* window, AssetsManager& am, std::vector<MapBackground*> textureSheets,
    JSONFilePath& path, const Player& p, const Enemy& e, KeyList* gameSupportedKeys)
    : State(window), map(am, textureSheets, path) {
	auto size = sf::Vector2f{720.0, 480.0};
	view = window->getDefaultView();
	view.setSize(size);
	view.setCenter({size.x / 2.f, size.y / 2.f});

	// initialText.y = 300; // window->getSize().y / 2;

	keybinds = gameSupportedKeys;
	std::map<int, Combatant*> turnMap;
	player = p;
	enemy = e;
	std::cout << "New Combat\n";

	auto pPos = COMBAT_FIRST_PLAYER_POSITION;
	addCombatString(player, am);
	player.animation.set_position(pPos);
	player.animation.sprite.setScale({3.f, 3.f});
	turnMap.insert({player.currentStats.dex, &player});


	auto ePos = COMBAT_FIRST_ENEMY_POSITION;
	enemy.animation.set_position(ePos);
	ePos.y += 50;
	turnMap.insert({enemy.currentStats.dex, &enemy});

	for(auto c : turnMap) {
		turnList.push_back(c.second);
	}

	currentCharacterTurn = 0;
	MusicPath* musicPath = am.getMusic(COMBAT_MUSIC.c);
	music.openFromFile(*musicPath);
	music.setLoop(true);
	music.play();

	// hand poiting at first character
	auto cursorPosition = turnList.at(0)->animation.get_position();
	cursor = Animation(am.getTexture(HAND.c), {40, 30, 40, 65}, cursorPosition);
	cursor.sprite.setScale({0.7, 0.7});
	cursor.sprite.setRotation(90.f);
	curosrOrientation = -1;
	nextTurn = false;

	font = *am.getFont(ALEX.c);
	addActionMenu(window);
	selectingEnemy = false;
	selectingItem = false;
	isSpecialAtk = false;
}

CombatState::~CombatState() = default;

void CombatState::update(const float& dt) {
	if(cursorClock.getElapsedTime().asSeconds() > 0.5f) {
		cursor.move({(curosrOrientation)*15.f, 0});
		curosrOrientation = curosrOrientation > 0 ? -1 : 1;
		cursorClock.restart();
	}
	if(nextTurn) {
		currentCharacterTurn = (int(currentCharacterTurn + 1)) % turnList.size();
		cursor.set_position(turnList[currentCharacterTurn]->animation.get_position());
		nextTurn = false;
	}
	updateKeybinds(dt);
	auto e = dynamic_cast<Enemy*>(turnList[currentCharacterTurn]);
	if(turnList[currentCharacterTurn]->isEnemy()) {
		if(player.defend() > e->attack()) {
			player.apply_damage(e->atkDamage());
			nextTurn = true;
		}
	}

	lifeCounters.at(player.name)
	    .setText(player.name + std::string(" HP:") + std::to_string(player.get_hp()) + "/"
	             + std::to_string(player.maxStats.hp) + " MP:" + std::to_string(player.get_mana()) + "/"
	             + std::to_string(player.maxStats.mana));
}

void CombatState::render(sf::RenderWindow* window) {
	window->setView(view);
	map.render(*window);
	drawPlayer(window);
	for(auto character : lifeCounters) {
		character.second.render(window);
	}
	window->draw(cursor.sprite);
	if(!turnList.at(currentCharacterTurn)->isEnemy()) {
		for(auto b : actionButtons) {
			b.render(window);
		}
	}
}

void CombatState::updateKeybinds(const float& dt) {}

bool CombatState::shouldQuit() {
	bool quit = isQuit();
	if(enemy.get_hp() < 0 || player.get_hp() < 0) {
		quit = true;
	}
	return quit;
}

void CombatState::quitStateActions() {
	// emptying enemies list here is purely for debug
	enemy.apply_damage(enemy.get_hp());
	std::cout << "Ending current game state" << std::endl;
}

StateAction CombatState::handleKeys(const sf::Keyboard::Key key) {
	auto action = std::find_if(keybinds->begin(), keybinds->end(),
	    [key](const std::pair<KeyAction, sf::Keyboard::Key>& v) { return key == v.second; });
	if(action != keybinds->end()) {
		switch(action->first) {
		case KeyAction::UP:
			actionButtons[actionButtonActive].setInactive();
			if(actionButtonActive == 0) {
				actionButtonActive = actionButtons.size() - 1;
			} else {
				actionButtonActive--;
			}
			actionButtons[actionButtonActive].setActive();
			break;
		case KeyAction::DOWN:
			actionButtons[actionButtonActive].setInactive();
			if(actionButtonActive == actionButtons.size() - 1) {
				actionButtonActive = 0;
			} else {
				actionButtonActive++;
			}
			actionButtons[actionButtonActive].setActive();
			break;
		default: break;
		}
	}
	if(key == sf::Keyboard::X) return StateAction::EXIT_COMBAT;
	return StateAction::NONE;
}

StateAction CombatState::shouldAct() {
	// depending on selected action this should trigger attack animation, use item animation, etc.
	if(!selectingItem) {
		// combat action menu
		if(actionButtonActive == 0) {
			// normal attack with current weapon
			if(player.attack() < enemy.defend()) {
				enemy.apply_damage(player.atkDamage());
			}
			nextTurn = true;
		} else if(actionButtonActive == 1) {
			// special attack with current weapon
			if(player.currentStats.mana >= 5) {
				if(player.attack() < enemy.defend()) {
					enemy.apply_damage(player.atkDamage() * 2);
				}
				player.spend_mana(5);
				nextTurn = true;
			} else {
				actionButtons[actionButtonActive].setColor(sf::Color::Red);
			}
		} else if(actionButtonActive == 2) {
			// select an item to be used
			selectingItem = true;
		} else {
			// skip turn
			nextTurn = true;
		}
	} else {
		// TODO: openUsableItemInventory(turnList[currentCharacterTurn]);
		selectingItem = false;
		nextTurn = true;
	}
	return StateAction::NONE;
}

void CombatState::drawPlayer(sf::RenderWindow* window) {
	window->draw(enemy.animation.sprite);
	window->draw(player.animation.sprite);
}
void CombatState::stopMusic() {
	music.stop();
}
void CombatState::resumeMusic() {
	music.play();
}