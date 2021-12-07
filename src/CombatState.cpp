#include "CombatState.h"
#include "AssetsPaths.h"

void CombatState::addCombatString(const Character& c, AssetsManager& am) {
	sf::Text characterInfo{};
	characterInfo.setOutlineColor(sf::Color::Black);
	characterInfo.setFillColor(sf::Color::Black);
	characterInfo.setFont(*am.getFont(ALEX.c));
	characterInfo.setString(
	    std::string(" HP:") + std::to_string(c.currentStats.hp) + "/" + std::to_string(c.maxStats.hp));
	lifeCounters.emplace(c.name, characterInfo);
}

CombatState::CombatState(sf::RenderWindow* window, AssetsManager& am, std::vector<MapBackground*> textureSheets,
    JSONFilePath path, const Party& p, const Enemies& e, KeyList* gameSupportedKeys)
    : State(window), map(am, textureSheets, path) {
	keybinds = gameSupportedKeys;
	party = p;
	enemies = e;
	std::cout << "New Combat\n";
	for(const auto& c : p) {
		addCombatString(c, am);
	}
	for(const auto& c : e) {
		addCombatString(c, am);
	}

	MusicPath* musicPath = am.getMusic(COMBAT_MUSIC.c);
	music.openFromFile(*musicPath);
	music.play();
}

CombatState::~CombatState() = default;

void CombatState::update(const float& dt) {
	updateKeybinds(dt);
}

void CombatState::render(sf::RenderTarget* target) {
	map.render(*target);
}

void CombatState::updateKeybinds(const float& dt) {
}

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

StateAction CombatState::handleKeys(const sf::Keyboard::Key key, [[maybe_unused]] sf::View* view) {
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
	for(const auto& p : party) {
		window->draw(p.animation.sprite);
	}
	for(const auto& e : enemies) {
		window->draw(e.animation.sprite);
	}
}
void CombatState::stopMusic() {
	music.stop();
}
void CombatState::resumeMusic() {
	music.play();
}
