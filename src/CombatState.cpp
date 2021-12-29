#include <map>

#include "AssetsPaths.h"
#include "Button.h"
#include "CombatState.h"
#include "Player.h"
#include "definitions.h"

void CombatState::addCombatString(const Player& player, AssetsManager& am, const int i) {
	sf::Text characterInfo{};

	characterInfo.setOutlineColor(sf::Color::Black);
	characterInfo.setFillColor(sf::Color::Black);
	characterInfo.setFont(font);
	characterInfo.setString(player.name + std::string(" HP:") + std::to_string(player.currentStats.hp) + "/"
	                        + std::to_string(player.maxStats.hp));
	lifeCounters.emplace(
	    player.name, Button(initialText.x + i * textIntervalHeight, initialText.y, 200, 50, characterInfo));
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
    JSONFilePath& path, const Party& p, const Enemies& e, KeyList* gameSupportedKeys)
    : State(window), map(am, textureSheets, path) {
	auto size = sf::Vector2f{720.0, 480.0};
	view = window->getDefaultView();
	view.setSize(size);
	view.setCenter({size.x / 2.f, size.y / 2.f});

	initialText.y = window->getSize().y / 2;

	keybinds = gameSupportedKeys;
	std::map<int, Entity*> turnMap;
	party = p;
	enemies = e;
	std::cout << "New Combat\n";
	for(int i = 0; i < party.size(); i++) {
		auto pPos = COMBAT_FIRST_PLAYER_POSITION;
		addCombatString(party[i], am, i);
		party[i].animation.set_position(pPos);
		pPos.y += i * 50;
		party[i].animation.sprite.setScale({3.f, 3.f});
		turnMap.insert({party[i].currentStats.dex, (Entity*)(&party[i])});
	}
	for(int i = 0; i < enemies.size(); i++) {
		auto ePos = COMBAT_FIRST_ENEMY_POSITION;
		enemies[i].animation.set_position(ePos);
		ePos.y += i * 50;
		turnMap.insert({enemies[i].currentStats.dex, (Entity*)(&enemies[i])});
	}
	for(auto c : turnMap) {
		turnList.push_back(c.second);
	}

	currentCharacterTurn = 0;
	MusicPath* musicPath = am.getMusic(COMBAT_MUSIC.c);
	music.openFromFile(*musicPath);
	music.setLoop(true);
	music.play();

	// hand poiting at first character
	auto cursorPosition = turnList[0]->animation.get_position();
	cursor = Animation(am.getTexture(HAND.c), {40, 30, 40, 65}, cursorPosition);
	cursor.sprite.setScale({0.7, 0.7});
	cursor.sprite.setRotation(90.f);
	curosrOrientation = -1;
	nextTurn = false;

	font = *am.getFont(ALEX.c);
	addActionMenu(window);
}

CombatState::~CombatState() = default;

void CombatState::update(const float& dt) {
	if(cursorClock.getElapsedTime().asSeconds() > 0.5f) {
		cursor.move({(curosrOrientation)*15.f, 0});
		curosrOrientation = curosrOrientation > 0 ? -1 : 1;
		cursorClock.restart();
	}
	if(nextTurn) {
		currentCharacterTurn = ((int)currentCharacterTurn + 1) % turnList.size();
		cursor.set_position(turnList[currentCharacterTurn]->animation.get_position());
		nextTurn = false;
	}
	updateKeybinds(dt);
}

void CombatState::render(sf::RenderWindow* window) {
	window->setView(view);
	map.render(*window);
	drawPlayer(window);
	for(auto character : lifeCounters) {
		character.second.render(window);
	}
	window->draw(cursor.sprite);
	for(auto b : actionButtons) {
		b.render(window);
	}
}

void CombatState::updateKeybinds(const float& dt) {}

bool CombatState::shouldQuit() {
	bool quit = isQuit();
	if(enemies.empty() || party.empty()) {
		quit = true;
	}
	return quit;
}

void CombatState::quitStateActions() {
	// emptying enemies list here is purely for debug
	enemies = {};
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
	// this is here just as a guide for future implementation
	/* case sf::Keyboard::Escape:
	   // open pause menu
	   break;
	case sf::Keyboard::Up: // Up arrow
	                      // switch action up
	   break;
	case sf::Keyboard::Down: // Down arrow
	                        // switch action down
	   break;
	case sf::Keyboard::Space:
	   // select combat action
	   break;*/
	if(key == sf::Keyboard::X) return StateAction::EXIT_COMBAT;
	return StateAction::NONE;
}

StateAction CombatState::shouldAct() {
	// depending on selected action this should trigger attack animation, use item animation, etc.
	if(actionButtonActive == 0) {
		nextTurn = true;
	}
	return StateAction::NONE;
}

void CombatState::drawPlayer(sf::RenderWindow* window) {
	for(const auto& e : enemies) {
		window->draw(e.animation.sprite);
	}
	for(const auto& p : party) {
		window->draw(p.animation.sprite);
	}
}
void CombatState::stopMusic() {
	music.stop();
}
void CombatState::resumeMusic() {
	music.play();
}
