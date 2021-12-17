#include <algorithm>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "SettingsState.h"
#include "Button.h"
#include "AssetsPaths.h"
#include "MainMenuState.h"

constexpr int MAX_RESOLUTION_COUNT = 7;

SettingsState::SettingsState(sf::RenderWindow* window, AssetsManager& am, KeyList* gameSupportedKeys) : State(window), activeButton(0) {
	view = window->getDefaultView();
	initBackground(window, am);
	initFonts(am);
	soundBuffer = am.getSoundBuffer(MENU_BLIP.c);
	sound.setBuffer(soundBuffer);

	MusicPath* path = am.getMusic(MENU_MUSIC.c);
	music.openFromFile(*path);
	music.play();
	
	supportedKeys = gameSupportedKeys;
	initButtons();
}

SettingsState::~SettingsState()  = default;

void SettingsState::initBackground(sf::RenderWindow* window, AssetsManager& am) {
	background.setSize(Position(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	background.setTexture(am.getTexture(SETTING_BACKGROUND.c));
}

void SettingsState::applyResolution(const unsigned int width, const unsigned int height) {
	sf::RenderWindow* window = getWindow();
	window->setSize(sf::Vector2u(width, height));
}

void SettingsState::initFonts(AssetsManager& am) {
	font = *am.getFont(DOSIS.c);
}

void SettingsState::updateGui() {
	
	switch(activeButton) {
		case 0:
			applyResolution(720, 480);
			break;
		case 1:
			applyResolution(800, 600);
			break;	
		case 2:
			applyResolution(1024, 768);
			break;
		case 3:
			applyResolution(1280, 720);
			break;
		case 4:
			applyResolution(1440, 900);
			break;
		case 5:
			applyResolution(1920, 1080);
			break;
		default:
			break;
	}
		
}

//creating buttons showing different resolution
void SettingsState::initButtons() {

	// get the size of the window
	sf::RenderWindow* window = getWindow();
	sf::Vector2u currentSize = window->getSize();
	unsigned int width = currentSize.x;
	unsigned int height = currentSize.y;
	unsigned int buttonPos = 150;
	unsigned int buttonPosInc = 30;
	
	buttons.push_back(Button(300, buttonPos, 150, buttonPosInc, &font, "720x480", GREY, LIGHTGREY, BLACK)); buttonPos += buttonPosInc;
	buttons.push_back(Button(300, buttonPos, 150, buttonPosInc, &font, "800x600", GREY, LIGHTGREY, BLACK)); buttonPos += buttonPosInc;
	buttons.push_back(Button(300, buttonPos, 150, buttonPosInc, &font, "1024x768", GREY, LIGHTGREY, BLACK)); buttonPos += buttonPosInc;
	buttons.push_back(Button(300, buttonPos, 150, buttonPosInc, &font, "1280x720", GREY, LIGHTGREY, BLACK)); buttonPos += buttonPosInc;
	buttons.push_back(Button(300, buttonPos, 150, buttonPosInc, &font, "1440x900", GREY, LIGHTGREY, BLACK)); buttonPos += buttonPosInc;
	buttons.push_back(Button(300, buttonPos, 150, buttonPosInc, &font, "1920x1080", GREY, LIGHTGREY, BLACK)); buttonPos += buttonPosInc;
	buttons.push_back(Button(300, buttonPos, 150, buttonPosInc, &font, "BACK", GREY, LIGHTGREY, BLACK));
		
	if(width == 720){
		activeButton = 0;
	} else if(width == 800){
		activeButton = 1;
	} else if(width == 1024){
		activeButton = 2;
	} else if(width == 1280){
		activeButton = 3;
	} else if(width == 1440){
		activeButton = 4;
	} else {
		activeButton = 5;
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
	std::cout << "Ending Settings Menu!"
	          << "\n";
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
	// play gasping sound each time change button.
	sound.play();
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
