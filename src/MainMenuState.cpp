#include <algorithm>
#include <filesystem>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "AssetsPaths.h"
#include "Button.h"
#include "states/MainMenuState.h"

#include "definitions.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, AssetsManager& am, KeyList* gameSupportedKeys)
    : MakesErrorSound(window) {
	supportedKeys = gameSupportedKeys;
	initBackground(window, am);
	initFonts(am);
	initButtons(getWindowCenter(*window));

	view = window->getDefaultView();

	soundBuffers.emplace("blip", am.getSoundBuffer(MENU_BLIP.c));
	soundBuffers.emplace("nope", am.getSoundBuffer(NOPE_SOUND.c));

	for(auto& sb : soundBuffers) {
		sf::Sound sound;
		sound.setBuffer(sb.second);
		sounds.emplace(sb.first, sound);
	}

	view = window->getDefaultView();
	MusicPath* path = am.getMusic(MENU_MUSIC.c);
	music.openFromFile(*path);
	music.play();
}

void MainMenuState::initBackground(sf::RenderWindow* window, AssetsManager& am) {
	background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	backgroundTexture = *am.getTexture(MAINMENU_BACKGROUND.c);
	background.setTexture(&backgroundTexture);
}

void MainMenuState::initFonts(AssetsManager& am) {
	font = *am.getFont(DOSIS.c);
}

void MainMenuState::initButtons(const Position& pos) {
	auto x = pos.x - 75;
	auto y = pos.y - 150;
	const Position size{150, 50};
	buttons.push_back(Button({x, y}, size, &font, "New Game", LIGHTGREY, sf::Color::Black));
	buttons.push_back(Button({x, y + 50}, size, &font, "Load Game", LIGHTGREY, sf::Color::Black));
	buttons.push_back(Button({x, y + 100}, size, &font, "Settings", LIGHTGREY, sf::Color::Black));
	buttons.push_back(Button({x, y + 150}, size, &font, "QUIT", LIGHTGREY, sf::Color::Black));
	activeButton = 0;
	buttons[activeButton].setActive();
}

MainMenuState::~MainMenuState() = default;

void MainMenuState::updateInput(const float& dt) {}

void MainMenuState::updateButtons() {
	/*Updates all the buttons in the state and handles their functionality*/
	for(auto it : buttons) {
		it.update(mousePosView);
	}
}

void MainMenuState::updateMousePositions() {
	mousePoseWindow = State::getMouse();
	mousePosView = getPos(mousePoseWindow);
}

void MainMenuState::update(const float& dt) {
	updateMousePositions();
	updateInput(dt);
	updateButtons();
}

void MainMenuState::renderButtons(sf::RenderWindow* window) {
	for(auto& it : buttons) {
		it.render(window);
	}
}

void MainMenuState::render(sf::RenderWindow* window) {
	window->setView(view);
	window->draw(background);
	renderButtons(window);
}

void MainMenuState::updateKeybinds(const float& dt) {}

bool MainMenuState::shouldQuit() {
	return isQuit();
}

void MainMenuState::quitStateActions() {
	std::cout << "Ending current game state" << std::endl;
}

StateAction MainMenuState::handleKeys(sf::Keyboard::Key key) {
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
	sounds.find("blip")->second.play();
	return StateAction::NONE;
}

StateAction MainMenuState::shouldAct() {
	if(activeButton == 0) {
		return StateAction::START_GAME;
	} else if(activeButton == 1) {
		if(!std::filesystem::exists(SAVED.c)) {
			playErrorSound();
			buttons[activeButton].setColor(sf::Color::Red);
		}
		return StateAction::LOAD_GAME;
	} else if(activeButton == 2) {
		return StateAction::START_SETTING;
	} else if(activeButton == 3) {
		return StateAction::EXIT_GAME;
	} else {
		return StateAction::NONE;
	}
}

void MainMenuState::playErrorSound() {
	sounds.find("nope")->second.play();
}
