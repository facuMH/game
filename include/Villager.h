#pragma once

#include <utility>

#include "Animation.h"
#include "Entity.h"
#include "definitions.h"
#include "entity_attributes/IdleMovement.h"

/// Class for non-playable characters, who don't engage in combat
class Villager : public Entity, public IdleMovement {
  private:
  public:
	std::string faceTexturePath; // for dialogue boxes
	Villager() = default;
	Villager(const Animation& _animation, const Name& _name, MovementType _movementType, Position _endPosition,
	    float _stepsize, std::string _faceTexturePath)
	    : Entity(_name, _animation), IdleMovement(_movementType, _animation.get_position(), _endPosition, _stepsize) {
		faceTexturePath = std::move(_faceTexturePath);
	}
};