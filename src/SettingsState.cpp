#include "SettingsState.h"
#include "Gui.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <algorithm>

#include <SFML/Window.hpp>
#include <string>

#include "AssetsPaths.h"
#include "MainMenuState.h"

constexpr int MAX_RESOLUTION_COUNT = 7;

SettingsState::SettingsState(sf::RenderWindow* window, AssetsManager& am, KeyList* gameSupportedKeys, std::stack<State*>* states) : State(window, states), am(am), states(states) {
	supportedKeys = gameSupportedKeys;
	initBackground(window, am);
	initFonts(am);
	
	initButtons();
	view = window->getDefaultView();

	soundBuffer = am.getSoundBuffer(GASP.c);
	sound.setBuffer(soundBuffer);

	MusicPath* path = am.getMusic(MENU_MUSIC.c);
	music.openFromFile(*path);
	music.play();
}

SettingsState::~SettingsState()  = default;

void SettingsState::initBackground(sf::RenderWindow* window, AssetsManager& am) {
	background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	backgroundTexture = *am.getTexture(SETTING_BACKGROUND.c);
	background.setTexture(&backgroundTexture);
}

void SettingsState::applyResolution(unsigned int width, unsigned int height) {

	window->setSize(sf::Vector2u(width, height));
}

void SettingsState::initFonts(AssetsManager& am) {
	font = *am.getFont(DOSIS.c);
}

void SettingsState::updateGui() {

	if(activeButton == 1){
		applyResolution(800, 600);
	}
	if(activeButton == 2){
		applyResolution(1024, 768);
	}
	if(activeButton == 3){
		applyResolution(1280, 720);
	}
	if(activeButton == 4){
		applyResolution(1440, 900);
	}
	if(activeButton == 5){
		applyResolution(1920, 1080);
	}                      
}
//creating buttons showing different resolution
void SettingsState::initButtons() {

	// get the size of the window
	sf::Vector2u currentSize = window->getSize();
	unsigned int width = currentSize.x;
	unsigned int height = currentSize.y;
	unsigned int buttonPos = 150;
	unsigned int buttonPosInc = 30;
	buttons.push_back(gui::Button(300, buttonPos, 150, buttonPosInc, &font, std::to_string(width) + 'x' + std::to_string(height), GREY, LIGHTGREY, BLACK));
	activeButton = 0;
	buttons[activeButton].setActive();

	if(!(width == 800  && height == 600)){
		buttonPos += buttonPosInc;
		buttons.push_back(gui::Button(300, buttonPos, 150, buttonPosInc, &font, "800x600", GREY, LIGHTGREY, BLACK));
	}
	if(!(width == 1024 && height == 768)){
		buttonPos += buttonPosInc;
		buttons.push_back(gui::Button(300, buttonPos, 150, buttonPosInc, &font, "1024x768", GREY, LIGHTGREY, BLACK));
	}
	if(!(width == 1280 && height == 720)){
		buttonPos += buttonPosInc;
		buttons.push_back(gui::Button(300, buttonPos, 150, buttonPosInc, &font, "1280x720", GREY, LIGHTGREY, BLACK));
	}
	if(!(width == 1440 && height == 900)){
		buttonPos += buttonPosInc;
		buttons.push_back(gui::Button(300, buttonPos, 150, buttonPosInc, &font, "1440x900", GREY, LIGHTGREY, BLACK));
	}
	if(!(width == 1920 && height == 1080 )){
		buttonPos += buttonPosInc;
		buttons.push_back(gui::Button(300, buttonPos, 150, buttonPosInc, &font, "1920x1080", GREY, LIGHTGREY, BLACK));
	}
	buttonPos += buttonPosInc;
	buttons.push_back(gui::Button(300, buttonPos, 150, buttonPosInc, &font, "BACK", GREY, LIGHTGREY, BLACK));
}

void SettingsState::updateButtons() {

	for(auto it : buttons) {
		it.update(mousePosView);
	}
}

void SettingsState::renderButtons(sf::RenderTarget* target) {
	for(auto& it : buttons) {
		it.render(target);
	}
}

void SettingsState::updateMousePositions() {
	mousePosScreen = sf::Mouse::getPosition();
	mousePoseWindow = State::getMouse();
	mousePosView = getPos(mousePoseWindow);
}

void SettingsState::endState() {
	std::cout << "Ending Main Menu!"
	          << "\n";
}

void SettingsState::updateInput(const float& dt) {}

void SettingsState::update(const float& dt) {
	updateMousePositions();
	updateInput(dt);
	updateButtons();
}


void SettingsState::render(sf::RenderTarget* target) {
	target->setView(view);
	target->draw(background);
	renderButtons(target);
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

void SettingsState::drawPlayer(sf::RenderWindow* window) {}

bool SettingsState::shouldQuit() {
	return isQuit();
}

StateAction SettingsState::shouldAct() {
	updateGui();
	if(activeButton == 6){
		states->push(new MainMenuState(window, am, supportedKeys, states));
	}   
	return StateAction::NONE;
}

void SettingsState::stopMusic() {
	music.stop();
}

void SettingsState::resumeMusic() {
	music.play();
}
