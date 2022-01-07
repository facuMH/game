#pragma once

#include <utility>

#include "Animation.h"
#include "Entity.h"
#include "NPC.h"
#include "definitions.h"

/// Class for non-playable characters, who don't engage in combat
class Villager : public NPC {
  private:
  public:
	Villager(Animation _animation, Name _name, MovementType _movementType, Position _endPosition, float _stepsize)
	    : Entity(_name, _animation), NPC(_movementType, _endPosition, _stepsize) {
		is_solid = true;
		can_interact = true;
	}
};