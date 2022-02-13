#include "states/GameOverState.h"
#include "AssetsPaths.h"

#include <algorithm>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "definitions.h"

constexpr int MAX_RESOLUTION_COUNT = 2;

GameOverState::GameOverState(sf::RenderWindow* window, AssetsManager& am, KeyList* gameSupportedKeys)
    : State(window) {
	std::cout << "New game over state" << std::endl;
	view = window->getDefaultView();
	initBackground(window, am);
	initFonts(am);
	initText(window);
	initButtons(window);
	supportedKeys = gameSupportedKeys;

	soundBuffers.emplace("blip", am.getSoundBuffer(MENU_BLIP.c));
	soundBuffers.emplace("nope", am.getSoundBuffer(NOPE_SOUND.c));

	for(auto& sb : soundBuffers) {
		sf::Sound sound;
		sound.setBuffer(sb.second);
		sounds.emplace(sb.first, sound);
	}

	view = window->getDefaultView();
	MusicPath* path = am.getMusic(END_MUSIC.c);
	music.openFromFile(*path);
	music.play();
}

GameOverState::~GameOverState() = default;

void GameOverState::initBackground(sf::RenderWindow* window, AssetsManager& am) {
	background.setTexture(am.getTexture(GAME_OVER_SCREEN.c));
	background.setSize(view.getSize());
}

void GameOverState::initFonts(AssetsManager& am) {
	font = *am.getFont(DOSIS.c);
}

void GameOverState::initText(sf::RenderWindow* window) {
	text.setFont(font);
	text.setCharacterSize(26);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::White);
	sf::Vector2u currentSize = window->getSize();
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(currentSize.x / 2.0f, currentSize.y / 4.0f);
}

void GameOverState::initButtons(sf::RenderWindow* window){

	// button size
	unsigned int bWidth = 150;
	unsigned int bHeight = 40;
	activeButton = 0;
	auto offsetX = 2 * bWidth;
	auto offsetY = 8 * bHeight;

	auto center = getWindowCenter(*window);
	center.x -= offsetX;
	center.y += offsetY;
	auto bPos = center.x - 50;

	buttons.push_back(Button(bPos, center.y, bWidth, bHeight, &font, "TRY AGAIN", GREY, LIGHTGREY, sf::Color::Black));
	bPos = bPos + 3 * bWidth;
	buttons.push_back(Button(bPos, center.y, bWidth, bHeight, &font, "QUIT", GREY, LIGHTGREY, sf::Color::Black));
	buttons[activeButton].setInactive();
}

void GameOverState::updateButtons() {
	for(auto it : buttons) {
		it.update(mousePosView);
	}
}

void GameOverState::renderButtons(sf::RenderWindow* window) {
	for(auto& it : buttons) {
		it.render(window);
	}
}

void GameOverState::updateMousePositions() {
	mousePoseWindow = State::getMouse();
	mousePosView = getPos(mousePoseWindow);
}

void GameOverState::updateInput(const float& dt) {}


void GameOverState::update(const float& dt) {
	updateMousePositions();
	updateInput(dt);
	updateButtons();
}

void GameOverState::render(sf::RenderWindow* window) {
	window->setView(view);
	window->draw(background);
	window->draw(text);
	renderButtons(window);
}

StateAction GameOverState::handleKeys(sf::Keyboard::Key key) {
	StateAction result = StateAction::NONE;
	auto action = std::find_if(supportedKeys->begin(), supportedKeys->end(),
	    [key](const std::pair<KeyAction, sf::Keyboard::Key>& v) { return key == v.second; });
	if(action != supportedKeys->end()) {
		switch(action->first) {
		case KeyAction::RIGHT: // Right arrow
			buttons[activeButton].setInactive();
			if(activeButton == 0) {
				activeButton = MAX_RESOLUTION_COUNT - 1;
			} else {
				activeButton--;
			}
			buttons[activeButton].setActive();

			break;
		case KeyAction::LEFT: // Left arrow
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
	sounds.find("blip")->second.play();
	return result;
}

void GameOverState::updateKeybinds(const float& dt) {}

void GameOverState::quitStateActions() {
	std::cout << "Returning to game from Game Over screen" << std::endl;
}

bool GameOverState::shouldQuit() {
	return isQuit();
}

StateAction GameOverState::shouldAct() {
	if(activeButton == 0) {
		return StateAction::LOAD_GAME;
	} else if(activeButton == 1) {
		return StateAction::EXIT_GAME;
	} else {
		return StateAction::NONE;
	}
}

void GameOverState::playErrorSound() {
	sounds.find("nope")->second.play();
}