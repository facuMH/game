#pragma once

#include "Inanimated.h"
#include "characterSuperclasses/Combatant.h"
#include "characterSuperclasses/IdleMovement.h"


/// Class for non-playable characters who engage in combat
class Enemy : public Entity, public IdleMovement, public Combatant {
  public:
	Enemy() = default;
	Enemy(Name _name, Stats _stats, Animation _animation, MovementType _movementType, Position _endPosition,
	    float _stepsize)
	    : Entity(_name, _animation),
	      Combatant(_stats, _stats),
	      IdleMovement(_movementType, animation.get_position(), _endPosition, _stepsize) {
		currentStats = _stats;
	};
	bool isEnemy() override { return true; }

};

Enemy createAlien(AssetsManager& am);