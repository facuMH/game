#pragma once

#include "State.h"

/// State which allows a subclass state to make an error sound
class MakesErrorSound : public State {
  public:
	explicit MakesErrorSound(sf::RenderWindow* window) : State(window) {}
	virtual void playErrorSound() = 0;
};