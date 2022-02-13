#include "states/State.h"
#include "AssetsManager.h"

State::State(sf::RenderWindow* renderWindow) {
	window = renderWindow;
}
void State::stopMusic() {
	music.stop();
}
void State::resumeMusic() {
	music.play();
}

State::~State() = default;