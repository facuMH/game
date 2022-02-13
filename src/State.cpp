#include "states/State.h"
#include "AssetsPaths.h"
#include "managers/AssetsManager.h"

State::State(sf::RenderWindow* renderWindow) {
	window = renderWindow;
}

State::~State() = default;