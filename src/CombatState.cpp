#include "AssetsPaths.h"
#include "CombatState.h"

void CombatState::addCombatString(const Character& c, AssetsManager& am) {
	sf::Text characterInfo{};
	characterInfo.setColor(sf::Color::Black);
	characterInfo.setFont(*am.getFont(ALEX.c));
	characterInfo.setString(std::string(" HP:") + std::to_string(c.currentStats.hp) + "/" + std::to_string(c.maxStats.hp));
	lifeCounters.emplace(c.name, characterInfo);
}

CombatState::CombatState(sf::RenderWindow* window, AssetsManager& am,             //
    std::vector<MapBackground*> textureSheets, std::vector<Design*> levelDesigns, //
    Party p, Enemies e)
    : State(window), map(am, textureSheets, levelDesigns) {
	party = p;
	enemies = e;
	std::cout << "New Combat\n";
	for(const auto& c : p) {
		addCombatString(c, am);
	}
	for(const auto& c : e) {
		addCombatString(c, am);
	}
}

CombatState::~CombatState() {}

void CombatState::update(const float& dt) {
	updateKeybinds(dt);
}

void CombatState::render(sf::RenderTarget* target) {
	map.render(*target);
}

// bool CombatState::shouldQuit() {
//	return enemies.empty() || party.empty();
//}

void CombatState::updateKeybinds(const float& dt) {
	shouldQuit();
}

void CombatState::quitStateActions() {
	// emptying enemies list here is purely for debug
	enemies = {};
	std::cout << "Ending current game state" << std::endl;
}

void CombatState::handleKeys(const sf::Keyboard::Key key, [[maybe_unused]] sf::View* view) {
	switch(key) {
		// up, down, right, left should be used to move around the actions menu
	case sf::Keyboard::Up: // Up arrow
		/* buttons[activeButton].setInactive();
		if(activeButton == 0) {
			activeButton = MAX_BUTTONS - 1;
		} else {
			activeButton--;
		}
		buttons[activeButton].setActive();*/
		break;
	case sf::Keyboard::Down: // Down arrow
		/* buttons[activeButton].setInactive();
		if(activeButton == MAX_BUTTONS - 1) {
			activeButton = 0;
		} else {
			activeButton++;
		}
		buttons[activeButton].setActive();
		break;*/
	case sf::Keyboard::Enter:
		// select action - if possible
		break;
	default: break;
	}
}

StateAction CombatState::shouldAct() {
	// depending on selected action this should triger attack animation, use item animation, etc.
	return StateAction::NONE;
}