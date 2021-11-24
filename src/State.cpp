#include "State.h"

State::State(sf::RenderWindow *window, std::map<std::string, int>* supportesKeys, std::stack<State*>* states)
{ 	this->window = window;
	this->supportedKeys = supportedKeys;
	this->states = states;
	this->quit = false;
}

State::~State() = default;

void State::checkIfQuitting() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
    this->isQuitting = true;
  }

  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
  {
	  this->isQuitting = true;
  }
}

const bool &State::isQuit() const { return this->isQuitting; }

void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePoseWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}
