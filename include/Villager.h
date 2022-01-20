#pragma once

#include <utility>

#include "Animation.h"
#include "object_attributes/Entity.h"
#include "object_attributes/IdleMovement.h"
#include "definitions.h"

/// Class for non-playable characters, who don't engage in combat
class Villager : public Entity, public IdleMovement {
  private:
  public:
	std::string faceTexturePath; // for dialogue boxes
	Villager() = default;
	Villager(Animation _animation, Name _name, MovementType _movementType, Position _endPosition, float _stepsize,
	    std::string _faceTexturePath)
	    : Entity(std::move(_name), std::move(_animation)),
	      IdleMovement(_movementType, _animation.get_position(), _endPosition, _stepsize) {
		faceTexturePath = std::move(_faceTexturePath);
	}
};