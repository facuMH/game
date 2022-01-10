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
	std::string faceTexturePath; // for dialogue boxes
	Villager(Animation _animation, Name _name, MovementType _movementType, Position _endPosition, float _stepsize,
	    std::string _faceTexturePath)
	    : Entity(std::move(_name), std::move(_animation)), NPC(_movementType, _endPosition, _stepsize) {
		faceTexturePath = std::move(_faceTexturePath);
		is_solid = true;
		can_interact = true;
	}
};