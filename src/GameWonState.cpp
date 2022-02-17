#include <SFML/Window.hpp>

#include "AssetsPaths.h"
#include "states/GameWonState.h"

GameWonState::GameWonState(sf::RenderWindow* window, AssetsManager& _assetsManager) : State(window) {
	view = window->getDefaultView();
	initBackground(_assetsManager);
	view = window->getDefaultView();
	MusicPath* path = _assetsManager.getMusic(GAME_WON_MUSIC.c);
	music.openFromFile(*path);
	music.play();
}


void GameWonState::initBackground(AssetsManager& am) {
	background.setTexture(am.getTexture(GAME_WON_SCREEN.c));
	background.setSize(view.getSize());
}

void GameWonState::update(const float& dt) {}

void GameWonState::render(sf::RenderWindow* window) {
	window->setView(view);
	window->draw(background);
}

StateAction GameWonState::handleKeys(sf::Keyboard::Key key) {
	return StateAction::NONE;
}

void GameWonState::updateKeybinds(const float& dt) {}

void GameWonState::quitStateActions() {}

bool GameWonState::shouldQuit() {
	return isQuit();
}

StateAction GameWonState::shouldAct() {
	return StateAction::NONE;
}
