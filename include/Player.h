#pragma once

#include "Inanimated.h"
#include "object_attributes/Combatant.h"
#include "object_attributes/SteeredMovement.h"

/// Class for playable characters
class Player : public Entity, public Combatant, public SteeredMovement {
  public:
	Weapon* weapon = nullptr;

	Player() {}
	Player(Name _name, Stats _stats, Animation _animation, float _stepsize)
	    : Entity(_name, _animation), Combatant(_stats, _stats), SteeredMovement(_stepsize) {}

	void equip(Weapon* arms);
	void move(KeyAction key, TileMap* map);
	bool isEnemy() override { return false; }
};
