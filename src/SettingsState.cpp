#include "SettingsState.h"
#include "Gui.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <algorithm>

#include <SFML/Window.hpp>
#include <string>

#include "AssetsPaths.h"
#include "MainMenuState.h"

void SettingsState::initBackground(sf::RenderWindow* window, AssetsManager& am) {
	background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	backgroundTexture = *am.getTexture(SETTING_BACKGROUND.c);
	background.setTexture(&backgroundTexture);
}

void SettingsState::initFonts(AssetsManager& am) {
	font = *am.getFont(DOSIS.c);
}

// void SettingsState::initGui() {
// 	buttons.push_back(gui::Button(300, 250, 150, 50, &font, "QUIT", GREY, LIGHTGREY, BLACK));
// }

void SettingsState::initText() {
	this->optionsText.setFont(this->font);

	this->optionsText.setPosition(sf::Vector2f(100.f, 100.f));

	this->optionsText.setCharacterSize(30);

	this->optionsText.setFillColor(sf::Color::Black);

	this->optionsText.setString("Resolution \nFullscreen \nVsync \nAntialiasing \n");
}


SettingsState::SettingsState(sf::RenderWindow* window, AssetsManager& am, KeyList* supportedKeys) : State(window) {
	// supportedKeys = gameSupportedKeys;
	initBackground(window, am);
	initFonts(am);
	initGui();
	initText();

	soundBuffer = am.getSoundBuffer(GASP.c);
	sound.setBuffer(soundBuffer);

	MusicPath* path = am.getMusic(MENU_MUSIC.c);
	music.openFromFile(*path);
	music.play();
}

SettingsState::~SettingsState() {
	// void SettingsState::endState() {
	// std::cout << "Ending Main Menu!"
	//           << "\n";
	// }

	// auto it = this->buttons.begin();
	// for(it = this->buttons.begin(); it != this->buttons.end(); ++it)
	// {
	// 	delete it->second;
	// }

	auto it2 = this->dropdownList.begin();
	for(it2 = this->dropdownList.begin(); it2 != this->dropdownList.end(); ++it2) {
		delete it2->second;
	}
}


// Accessors


// Functions

void SettingsState::endState() {
	std::cout << "Ending Main Menu!"
	          << "\n";
}

void SettingsState::updateInput(const float& dt) {}

// void SettingsState::updateGui(const float& dt)
// {
// 	this->ddl->update(this->mousePosView, dt)
// }

void SettingsState::updateGui(const float& dt) {
	/*Updates all the buttons in the state and handles their functionality*/
	for(auto it : buttons) {
		it.update(mousePosView);
	}

	// Dropdown list
	for(auto& it : this->dropdownList) {
		it.second->update(this->mousePosView, dt);
	}

	// Apply selected settings
	// if(buttons["APPLY"]->isPressed()))
	//		this->window->create(this->modes[this->dropDownLists["RESOLUTION"]->getActiveElementId()], "Test",
	// sf::Style::Default);
	// Dropdown functionality
}


void SettingsState::updateMousePositions() {
	mousePosScreen = sf::Mouse::getPosition();
	mousePoseWindow = State::getMouse();
	mousePosView = getPos(mousePoseWindow);
}

void SettingsState::update(const float& dt) {
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateGui(dt);
}

void SettingsState::renderGui(sf::RenderTarget* target) {
	for(auto& it : this->buttons) {
		it.render(target);
	}

	for(auto& it : this->dropdownList) {
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target) {
	target->draw(background);
	renderGui(target);

	target->draw(this->optionsText);
}

void SettingsState::updateKeybinds(const float& dt) {}

bool SettingsState::shouldQuit() {
	return isQuit();
}

void SettingsState::quitStateActions() {
	std::cout << "Ending current game state" << std::endl;
}

StateAction SettingsState::handleKeys(sf::Keyboard::Key key, sf::View* view) {
	auto action = std::find_if(supportedKeys->begin(), supportedKeys->end(),
	    [key](const std::pair<KeyAction, sf::Keyboard::Key>& v) { return key == v.second; });
	if(action != supportedKeys->end()) {
		switch(action->first) {
		case KeyAction::UP: // Up arrow
			buttons[activeButton].setInactive();
			if(activeButton == 0) {
				activeButton = MAX_BUTTONS - 1;
			} else {
				activeButton--;
			}
			buttons[activeButton].setActive();
			break;
		case KeyAction::DOWN: // Down arrow
			buttons[activeButton].setInactive();
			if(activeButton == MAX_BUTTONS - 1) {
				activeButton = 0;
			} else {
				activeButton++;
			}
			buttons[activeButton].setActive();
			break;
		default: break;
		}
	}
	// play gasping sound each time change button.
	sound.play();
	return StateAction::NONE;
}

StateAction SettingsState::shouldAct() {
	if(activeButton == 0) {
		return StateAction::START_GAME;
	} else if(activeButton == 1) {
		return StateAction::SETTINGS_GAME;
	} else if(activeButton == 2) {
		return StateAction::EXIT_GAME;
	} else {
		return StateAction::NONE;
	}
}

void SettingsState::stopMusic() {
	music.stop();
}

void SettingsState::resumeMusic() {
	music.play();
}

void SettingsState::initGui() {
	buttons.push_back(gui::Button(380, 350, 200, 50, &font, "BACK", GREY, LIGHTGREY, BLACK));

	buttons.push_back(gui::Button(80, 350, 200, 50, &font, "APPLY", GREY, LIGHTGREY, BLACK));

	std::vector<std::string> modes_str;

	for(auto& i : this->modes) {
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}

	this->dropdownList["RESOLUTION"] =
	    new gui::DropDownList(230, 60, 200, 50, font, modes_str.data(), modes_str.size());

	// buttons.push_back(gui::Button(500, 880, 250, 50, &font, "BACK", GREY, LIGHTGREY, BLACK));
	// activeButton = 0;
}

void SettingsState::initVariables() {
	this->modes = sf::VideoMode::getFullscreenModes();
}
