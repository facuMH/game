#include "GameOverState.h"
#include "AssetsPaths.h"

void GameOverState::initBackground(sf::RenderWindow* window, AssetsManager& am) {
	background.setTexture(am.getTexture(GAME_OVER.c));
	background.setSize(view.getSize());
}
void GameOverState::initFonts(AssetsManager& am) {}

GameOverState::GameOverState(sf::RenderWindow* window, AssetsManager& am, KeyList* _supportedKeys) : State(window) {
	view = window->getDefaultView();
	initBackground(window, am);
	initFonts(am);
	soundBuffer = am.getSoundBuffer(MENU_BLIP.c);
	blipSound.setBuffer(soundBuffer);

	supportedKeys = _supportedKeys;
}
GameOverState::~GameOverState() = default;

void GameOverState::render(sf::RenderWindow* window) {
	window->draw(background);
}
void GameOverState::update(const float& dt) {}
StateAction GameOverState::handleKeys(sf::Keyboard::Key key) {
	return StateAction::PICK_ITEM;
}
void GameOverState::updateKeybinds(const float& dt) {}
void GameOverState::quitStateActions() {}
bool GameOverState::shouldQuit() {
	return false;
}
void GameOverState::drawPlayer(sf::RenderWindow* window) {}
StateAction GameOverState::shouldAct() {
	return StateAction::PICK_ITEM;
}
void GameOverState::stopMusic() {}
void GameOverState::resumeMusic() {}
