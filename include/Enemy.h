#pragma once

#include "Combatant.h"
#include "Inanimated.h"
#include "NPC.h"

/// Class for non-playable characters who engage in combat
class Enemy : public Combatant, public NPC {
  public:
	Enemy() = default;
	Enemy(Name _name, Stats _stats, Animation _animation, MovementType _movementType, Position _endPosition,
	    float _stepsize)
	    : Entity(_name, _animation), Combatant(_stats, _stats), NPC(_movementType, _endPosition, _stepsize) {
		is_solid = true;
		can_interact = true;
		currentStats = _stats;
	};
	bool isEnemy() override { return true; }
};

Enemy createAlien(AssetsManager& am);