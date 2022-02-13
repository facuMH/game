#include "states/State.h"
#include "AssetsManager.h"
#include "AssetsPaths.h"

State::State(sf::RenderWindow* renderWindow) {
	window = renderWindow;
}

State::~State() = default;