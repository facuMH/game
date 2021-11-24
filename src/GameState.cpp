#include <iostream>
#include "GameState.h"


GameState::GameState(sf::RenderWindow *window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) : State(window, supportedKeys, states)
{
	this->initKeybinds();
}

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_Keysbind.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] =  this->supportedKeys->at(key2);
		}
	}

	ifs.close();






	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("D");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("S");

}


GameState::~GameState() = default;

void GameState::update(const float &dt)
{
    this->updateKeybinds(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        std::cout << "A pressed" << std::endl;
    }
}

void GameState::render(sf::RenderTarget *target)
{
    map.render(*target);
}

void GameState::checkIfQuitting()
{ State::checkIfQuitting(); }

void GameState::updateKeybinds(const float &dt)
{ this->checkIfQuitting(); }

void GameState::quitStateActions()
{
    std::cout << "Ending current game state" << std::endl;
}
