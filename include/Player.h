#pragma once

#include "Inanimated.h"
#include "characterSuperclasses/Combatant.h"
#include "characterSuperclasses/SteeredMovement.h"

/// Class for playable characters
class Player : public Entity, public Combatant, public SteeredMovement {
  public:
	Weapon* weapon = nullptr;

	Player() {}
	Player(Name _name, Stats _stats, Animation _animation, float _stepsize)
	    : Entity(_name, _animation), Combatant(_stats, _stats), SteeredMovement(_stepsize) {
	}

	void equip(Weapon* arms);
	void move(KeyAction key, TileMap* map, Position position);
	bool isEnemy() override { return false; }
};
