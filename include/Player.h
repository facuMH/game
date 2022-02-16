#pragma once

#include "Inanimated.h"
#include "entity_attributes/Combatant.h"
#include "entity_attributes/SteeredMovement.h"

/// Class for playable characters
class Player : public Entity, public Combatant, public SteeredMovement {
	int level = 1;
	int experience = 0;
	Name weaponUsed;

  public:
	Object* weapon = nullptr;

	Player() = default;
	Player(const Name& _name, const Stats& _stats, const Animation& _animation, float _stepsize)
	    : Entity(_name, _animation), Combatant(_stats, _stats), SteeredMovement(_stepsize) {}

	void equip(Object* arms);
	Name equippedWeapon() const { return weaponUsed; }
	void move(KeyAction key, TileMap* map);
	bool isEnemy() override { return false; }
	int getLevel() const { return level; }
	int getExp() const { return experience; }
	bool addExperience(const int xp);
};
