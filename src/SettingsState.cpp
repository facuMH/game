#include <algorithm>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "AssetsPaths.h"
#include "Button.h"
#include "MainMenuState.h"
#include "SettingsState.h"

#include "definitions.h"

constexpr int MAX_RESOLUTION_COUNT = 7;

SettingsState::SettingsState(sf::RenderWindow* window, AssetsManager& am, KeyList* gameSupportedKeys)
    : State(window), activeButton(0) {
	view = window->getDefaultView();
	initBackground(window, am);
	initFonts(am);
	soundBuffer = am.getSoundBuffer(MENU_BLIP.c);
	blipSound.setBuffer(soundBuffer);

	// Settings should keep on playing music from Menu

	supportedKeys = gameSupportedKeys;
	initButtons(window);
}

SettingsState::~SettingsState() = default;

void SettingsState::initBackground(sf::RenderWindow* window, AssetsManager& am) {
	background.setTexture(am.getTexture(SETTING_BACKGROUND.c));
	background.setSize(view.getSize());
}

void SettingsState::applyResolution(const unsigned int width, const unsigned int height) {
	sf::RenderWindow* window = getWindow();
	view.setSize(sf::Vector2f(width, height));
	window->setSize(sf::Vector2u(width, height));
	window->setView(view);
	window->setPosition(getDesktopCenter(*window));
}

void SettingsState::initFonts(AssetsManager& am) {
	font = *am.getFont(DOSIS.c);
}

void SettingsState::updateGui() {
	switch(activeButton) {
	case 0: applyResolution(720, 480); break;
	case 1: applyResolution(800, 600); break;
	case 2: applyResolution(1024, 768); break;
	case 3: applyResolution(1280, 720); break;
	case 4: applyResolution(1440, 900); break;
	case 5: applyResolution(1920, 1080); break;
	default: break;
	}
}

// creating buttons showing different resolution
void SettingsState::initButtons(sf::RenderWindow* window) {
	// get the size of the window
	sf::Vector2u currentSize = window->getSize();

	// button size
	unsigned int bWidth = 150;
	unsigned int bHeight = 40;
	auto offsetX = 0.5 * bWidth;
	auto offsetY = 4 * bHeight;

	auto center = getWindowCenter(*window);
	center.x -= offsetX;
	center.y -= offsetY;
	auto bPos = center.y;

	buttons.push_back(Button(center.x, bPos, bWidth, bHeight, &font, "720x480", GREY, LIGHTGREY, sf::Color::Black));
	bPos += bHeight;
	buttons.push_back(Button(center.x, bPos, bWidth, bHeight, &font, "800x600", GREY, LIGHTGREY, sf::Color::Black));
	bPos += bHeight;
	buttons.push_back(Button(center.x, bPos, bWidth, bHeight, &font, "1024x768", GREY, LIGHTGREY, sf::Color::Black));
	bPos += bHeight;
	buttons.push_back(Button(center.x, bPos, bWidth, bHeight, &font, "1280x720", GREY, LIGHTGREY, sf::Color::Black));
	bPos += bHeight;
	buttons.push_back(Button(center.x, bPos, bWidth, bHeight, &font, "1440x900", GREY, LIGHTGREY, sf::Color::Black));
	bPos += bHeight;
	buttons.push_back(Button(center.x, bPos, bWidth, bHeight, &font, "1920x1080", GREY, LIGHTGREY, sf::Color::Black));
	bPos += bHeight;
	buttons.push_back(Button(center.x, bPos, bWidth, bHeight, &font, "BACK", GREY, LIGHTGREY, sf::Color::Black));

	switch(currentSize.x) {
	case 720: activeButton = 0; break;
	case 800: activeButton = 1; break;
	case 1024: activeButton = 2; break;
	case 1280: activeButton = 3; break;
	case 1440: activeButton = 4; break;
	case 1920: activeButton = 5; break;
	default: break;
	}

	buttons[activeButton].setActive();
}

void SettingsState::updateButtons() {
	for(auto it : buttons) {
		it.update(mousePosView);
	}
}

void SettingsState::renderButtons(sf::RenderWindow* window) {
	for(auto& it : buttons) {
		it.render(window);
	}
}

void SettingsState::updateMousePositions() {
	mousePosScreen = sf::Mouse::getPosition();
	mousePoseWindow = State::getMouse();
	mousePosView = getPos(mousePoseWindow);
}

void SettingsState::endState() {
	std::cout << "Ending Settings Menu!\n";
}

void SettingsState::updateInput(const float& dt) {}

void SettingsState::update(const float& dt) {
	updateMousePositions();
	updateInput(dt);
	updateButtons();
}


void SettingsState::render(sf::RenderWindow* window) {
	window->setView(view);
	window->draw(background);
	renderButtons(window);
}

StateAction SettingsState::handleKeys(sf::Keyboard::Key key) {
	auto action = std::find_if(supportedKeys->begin(), supportedKeys->end(),
	    [key](const std::pair<KeyAction, sf::Keyboard::Key>& v) { return key == v.second; });
	if(action != supportedKeys->end()) {
		switch(action->first) {
		case KeyAction::UP: // Up arrow
			buttons[activeButton].setInactive();
			if(activeButton == 0) {
				activeButton = MAX_RESOLUTION_COUNT - 1;
			} else {
				activeButton--;
			}
			buttons[activeButton].setActive();

			break;
		case KeyAction::DOWN: // Down arrow
			buttons[activeButton].setInactive();
			if(activeButton == MAX_RESOLUTION_COUNT - 1) {
				activeButton = 0;
			} else {
				activeButton++;
			}
			buttons[activeButton].setActive();
			break;
		default: break;
		}
	}
	// play gasping gaspSound each time change button.
	blipSound.play();
	return StateAction::NONE;
}

void SettingsState::updateKeybinds(const float& dt) {}

void SettingsState::quitStateActions() {
	std::cout << "Ending current game state" << std::endl;
}

bool SettingsState::shouldQuit() {
	return isQuit();
}

void SettingsState::drawPlayer(sf::RenderWindow* window) {}

StateAction SettingsState::shouldAct() {
	updateGui();
	return StateAction::EXIT_SETTING;
}

void SettingsState::stopMusic() {
	music.stop();
}

void SettingsState::resumeMusic() {
	music.play();
}
