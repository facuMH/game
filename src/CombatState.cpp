#include "CombatState.h"
#include "AssetsPaths.h"

void CombatState::addCombatString(const Character& c, AssetsManager& am) {
	sf::Text characterInfo{};
	characterInfo.setOutlineColor(sf::Color::Black);
	characterInfo.setFillColor(sf::Color::Black);
	characterInfo.setFont(*am.getFont(ALEX.c));
	characterInfo.setString(std::string(" HP:") + std::to_string(c.currentStats.hp) + "/" + std::to_string(c.maxStats.hp));
	lifeCounters.emplace(c.name, characterInfo);
}

CombatState::CombatState(sf::RenderWindow* window, AssetsManager& am,             //
    std::vector<MapBackground*> textureSheets, JSONFilePath path, //
    const Party& p, const Enemies& e)
    : State(window), map(am, textureSheets, path) {
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

CombatState::~CombatState() = default;

void CombatState::update(const float& dt) {
	updateKeybinds(dt);
}

void CombatState::render(sf::RenderTarget* target) {
	map.render(*target);
}

void CombatState::updateKeybinds(const float& dt) {
	shouldQuit();
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