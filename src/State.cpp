#include "State.h"

State::State(sf::RenderWindow* renderWindow, std::stack<State*>* states) {
	window = renderWindow;
	this->states = states;
}

State::~State() = default;
