#include <iostream>
#include "headers/GameState.h"

GameState::GameState(sf::RenderWindow *window): State(window)
{

}

GameState::~GameState()
{

}

void GameState::update(const float& dt)
{
    std::cout << "GameState is updated" << std::endl;
}

void GameState::render(sf::RenderTarget* target)
{

}

void GameState::endState()
{

}