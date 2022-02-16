#include <algorithm>
#include <map>

#include "AssetsPaths.h"
#include "Button.h"
#include "Player.h"
#include "definitions.h"
#include "states/CombatState.h"

void CombatState::addCombatString(const Player& _p, AssetsManager& am) {
	sf::Text characterInfo{};

	characterInfo.setOutlineColor(sf::Color::Black);
	characterInfo.setFillColor(sf::Color::Black);
	characterInfo.setFont(font);
	characterInfo.setString(_p.name + std::string(" HP:") + std::to_string(_p.get_hp()) + "/"
	                        + std::to_string(_p.maxStats.hp) + " MP:" + std::to_string(_p.get_mana()) + "/"
	                        + std::to_string(_p.maxStats.mana));
	lifeCounters.emplace(_p.name, Button(initialText, {280, 40}, characterInfo));
}

void CombatState::addActionMenu() {
	auto center = Position{320, 300};
	center.y = center.y * 0.75f;
	const int bWidth = 150;
	const int bHeight = 40;
	const Position size{bWidth, bHeight};
	actionButtons.push_back(Button(center, size, &font, "Attack", DARKBLUE, sf::Color::Black));
	center.y += bHeight;
	actionButtons.push_back(Button(center, size, &font, "Special", DARKBLUE, sf::Color::Black));
	center.y += bHeight;
	actionButtons.push_back(Button(center, size, &font, "Item", DARKBLUE, sf::Color::Black));
	center.y += bHeight;
	actionButtons.push_back(Button(center, size, &font, "Skip", DARKBLUE, sf::Color::Black));
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
	std::map<int, Entity*> turnMap;
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
	enemy.animation.sprite.setScale({3.f, 3.f});
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

	soundBuffers.emplace("power_up", am.getSoundBuffer(POWER_UP.c));
	soundBuffers.emplace("punch1", am.getSoundBuffer(PUNCH1.c));
	soundBuffers.emplace("punch2", am.getSoundBuffer(PUNCH2.c));

	for(auto& sb : soundBuffers) {
		sf::Sound sound;
		sound.setBuffer(sb.second);
		sounds.emplace(sb.first, sound);
	}

	// hand pointing at first character
	Position cursorPosition;
	auto next = turnList.at(0);
	cursorPosition = next->animation.get_position();
	cursor = Animation(am.getTexture(HAND.c), {40, 30, 40, 65}, cursorPosition);
	cursor.sprite.setScale({0.7, 0.7});
	cursor.sprite.setRotation(90.f);
	cursorOrientation = -1;
	nextTurn = false;

	font = *am.getFont(ALEX.c);
	addActionMenu();
	selectingEnemy = false;
	selectingItem = false;
	isSpecialAtk = false;
}

CombatState::~CombatState() = default;

void CombatState::update(const float& dt) {
	if(dynamic_cast<Combatant*>(turnList[currentCharacterTurn])->isEnemy()) {
		sf ::sleep(sf::milliseconds(1000));
	}
	if(cursorClock.getElapsedTime().asSeconds() > 0.5f) {
		cursor.move({(cursorOrientation)*15.f, 0});
		cursorOrientation = cursorOrientation > 0 ? -1 : 1;
		cursorClock.restart();
	}
	if(nextTurn) {
		currentCharacterTurn = (int(currentCharacterTurn + 1)) % turnList.size();
		auto next = turnList[currentCharacterTurn];
		cursor.set_position(next->animation.get_position());
		nextTurn = false;
	}
	updateKeybinds(dt);
	auto e = dynamic_cast<Combatant*>(turnList[currentCharacterTurn]);
	if(e->isEnemy()) {
		auto next = turnList[currentCharacterTurn];
		cursor.set_position(next->animation.get_position());
		if(e->attack() > player.defend()) {
			player.apply_damage(e->atkDamage());
		}
		nextTurn = true;
	}

	lifeCounters.at(player.name)
	    .setText(player.name + std::string(" HP:") + std::to_string(player.get_hp()) + "/"
	             + std::to_string(player.maxStats.hp) + " MP:" + std::to_string(player.get_mana()) + "/"
	             + std::to_string(player.maxStats.mana));
}

void CombatState::render(sf::RenderWindow* window) {
	window->setView(view);
	map.render(*window);
	if(inLevelUpBox) {
		levelUpBox.get()->render(window);
	} else {
		drawPlayer(window);
		for(auto character : lifeCounters) {
			character.second.render(window);
		}
		window->draw(cursor.sprite);
		if(!dynamic_cast<Combatant*>(turnList.at(currentCharacterTurn))->isEnemy()) {
			for(auto b : actionButtons) {
				b.render(window);
			}
		}
	}
}

void CombatState::updateKeybinds(const float& dt) {}

bool CombatState::shouldQuit() {
	return isQuit();
}

void CombatState::quitStateActions() {
	std::cout << "Ending current game state" << std::endl;
}

StateAction CombatState::handleKeys(const sf::Keyboard::Key key) {
	auto action = std::find_if(keybinds->begin(), keybinds->end(),
	    [key](const std::pair<KeyAction, sf::Keyboard::Key>& v) { return key == v.second; });
	if(action != keybinds->end()) {
		if(!inLevelUpBox) {
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
		} else {
			if(key == sf::Keyboard::F) {
				inLevelUpBox = false;
				return StateAction::EXIT_COMBAT;
			}
		}
	}
	return StateAction::NONE;
}

StateAction CombatState::shouldAct() {
	// depending on selected action this should trigger attack animation, use item animation, etc.
	if(!selectingItem) {
		// combat action menu
		if(actionButtonActive == 0) {
			// normal attack with current weapon
			sounds.find("punch1")->second.play();
			if(player.attack() < enemy.defend()) {
				enemy.apply_damage(player.atkDamage());
			}
			nextTurn = true;
		} else if(actionButtonActive == 1) {
			sounds.find("punch2")->second.play();
			// special attack with current weapon
			if(player.currentStats.mana >= 5) {
				if(player.attack() < enemy.defend()) {
					enemy.apply_damage(player.atkDamage() * 4);
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

	if(enemy.get_hp() <= 0) {
		if(!inLevelUpBox && player.getExp() + enemy.getExperience() >= 99) {
			LevelUpMessage();
		} else {
			return StateAction::EXIT_COMBAT;
		}
	}

	return StateAction::NONE;
}

void CombatState::drawPlayer(sf::RenderWindow* window) {
	if(!inLevelUpBox) {
		window->draw(enemy.animation.sprite);
		window->draw(player.animation.sprite);
	}
}

StateAction CombatState::programAction() {
	StateAction ret = StateAction::NONE;
	if(player.get_hp() <= 0) {
		ret = StateAction::GAME_OVER;
	}
	return ret;
}

void CombatState::LevelUpMessage() {
	inLevelUpBox = true;
	music.setVolume(music.getVolume() / 2.0f);
	sf ::sleep(sf::milliseconds(1000));
	sounds.find("power_up")->second.play();
	sf ::sleep(sf::milliseconds(1000));
	music.setVolume(music.getVolume() * 2.0f);

	auto center = view.getCenter();
	sf::Text lvlUpTxt{};
	lvlUpTxt.setFont(font);
	const std::string lvlUpMsg =
	    "Congrats, you killed enough crazy\n monsters to LEVEL UP.\nNow you feel stronger ... or not";
	lvlUpTxt.setString(lvlUpMsg);
	const int width = 400.f;
	const int height = 100.f;
	center.x -= width / 2;
	center.y -= height / 2;
	levelUpBox = std::make_unique<Button>(Button(center, {400, 100}, lvlUpTxt));
}
