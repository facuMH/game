#pragma once

#include "State.h"

class MakesErrorSound : public State {
  public:
	MakesErrorSound(sf::RenderWindow* window) : State(window) {}
	virtual void playErrorSound() = 0;
};