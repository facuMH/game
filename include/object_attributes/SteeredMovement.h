#pragma once

#include "Movement.h"

class SteeredMovement : public Movement {
  public:
	SteeredMovement() = default;
	explicit SteeredMovement(float _stepsize) : Movement(_stepsize) {}
};