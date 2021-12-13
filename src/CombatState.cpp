#include "AssetsPaths.h"
#include "Button.h"
#include "CombatState.h"
#include "definitions.h"

void CombatState::addCombatString(const Character& c, AssetsManager& am, const int i) {
	sf::Text characterInfo{};

	characterInfo.setOutlineColor(sf::Color::Black);
	characterInfo.setFillColor(sf::Color::Black);
	characterInfo.setFont(*am.getFont(ALEX.c));
	characterInfo.setString(c.name.c_str() +
	    std::string(" HP:") + std::to_string(c.currentStats.hp) + "/" + std::to_string(c.maxStats.hp));
	lifeCounters.emplace(c.name, Button(initialText.x + i * textIntervalHeigh, initialText.y, 200, 50, characterInfo));
}

CombatState::CombatState(sf::RenderWindow* window, AssetsManager& am, std::vector<MapBackground*> textureSheets,
    JSONFilePath path, const Party& p, const Enemies& e, KeyList* gameSupportedKeys)
    : State(window), map(am, textureSheets, path) {
	view = window->getDefaultView();
	keybinds = gameSupportedKeys;
	view = window->getDefaultView();
	party = p;
	enemies = e;
	std::cout << "New Combat\n";
	for(int i = 0; i < p.size(); i++) {
		auto pPos = COMBAT_FIRST_PLAYER_POSITION;
		addCombatString(p[i], am, i);
		party[i].animation.set_position(pPos);
		pPos.y += i * 50;
		party[i].animation.sprite.setScale({3.f, 3.f});
	}
	for(int i = 0; i < e.size(); i++) {
		auto ePos = COMBAT_FIRST_ENEMY_POSITION;
		enemies[i].animation.set_position(ePos);
		ePos.y += i * 50;
	}

	MusicPath* musicPath = am.getMusic(COMBAT_MUSIC.c);
	music.openFromFile(*musicPath);
	music.play();
}

CombatState::~CombatState() = default;

void CombatState::update(const float& dt) {
	updateKeybinds(dt);
}

void CombatState::render(sf::RenderWindow* window) {
	window->setView(view);
	map.render(*window);
	drawPlayer(window);
	for(auto character : lifeCounters) {
		character.second.render(window);
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
			/* buttons[activeButton].setInactive();
			if(activeButton == 0) {
			    activeButton = MAX_BUTTONS - 1;
			} else {
			    activeButton--;
			}
			buttons[activeButton].setActive();*/
			break;
		case KeyAction::DOWN:
			/* buttons[activeButton].setInactive();
			if(activeButton == MAX_BUTTONS - 1) {
			    activeButton = 0;
			} else {
			    activeButton++;
			}
			buttons[activeButton].setActive();
			break;*/
		case KeyAction::SELECT:
			// select action - if possible
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
