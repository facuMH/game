#pragma once

#include "Inanimated.h"
#include "entity_attributes/Combatant.h"
#include "entity_attributes/IdleMovement.h"

/// Class for non-playable characters who engage in combat
class Enemy : public Entity, public IdleMovement, public Combatant {
	int experience;
	Name bodyPart;

  public:
	Enemy() = default;
	Enemy(const Name& _name, const Stats& _stats, const Animation& _animation, const MovementType _movementType,
	    const Position& _endPosition, const float _stepsize, const int _xp, const Name& _bodyPart)
	    : Entity(_name, _animation), Combatant(_stats, _stats),
	      IdleMovement(_movementType, animation.get_position(), _endPosition, _stepsize), experience(_xp),
	      bodyPart(_bodyPart) {
		currentStats = _stats;
	};
	bool isEnemy() override { return true; }
	int getExperience() const { return experience; }
	bool isEmpty() const { return name.empty(); }
	Name getBodyPart() const { return bodyPart; }

	bool operator==(const Enemy& e) const { return name == e.name; }
};