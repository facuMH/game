#include <iostream>

#include "GameState.h"

GameState::GameState(sf::RenderWindow *window, AssetsManager &am, std::vector<MapBackground *> textureSheets,
                     std::vector<Design *> levelDesigns) : State(window), map(am, textureSheets, levelDesigns)
{}

GameState::~GameState() = default;

void GameState::update(const float &dt)
{
    this->updateKeybinds(dt);
}

void GameState::render(sf::RenderTarget *target)
{
    map.render(*target);
}

void GameState::checkIfQuitting()
{
    State::checkIfQuitting();
}

void GameState::updateKeybinds(const float &dt)
{
    this->checkIfQuitting();
}

void GameState::quitStateActions()
{
    std::cout << "Ending current game state" << std::endl;
}
