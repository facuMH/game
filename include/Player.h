#pragma once

#include "Inanimated.h"
#include "entity_attributes/Combatant.h"
#include "entity_attributes/SteeredMovement.h"

/// Class for playable characters
class Player : public Entity, public Combatant, public SteeredMovement {
	int level = 1;
	int experience = 0;
	const Stats levelUpStatsIncrement{3, 3, 10, 10, 5, 5};

  public:
	Object* weapon = nullptr;

	Player() = default;
	Player(const Name& _name, const Stats& _stats, const Animation& _animation, float _stepsize)
	    : Entity(_name, _animation), Combatant(_stats, _stats), SteeredMovement(_stepsize) {}

	void equip(Object* arms);
	void move(KeyAction key, TileMap* map);
	bool isEnemy() override { return false; }
	int getLevel() const { return level; }
	int getExp() const { return experience; }
	bool addExperience(const int xp) {
		experience += xp;
		bool levelUp = false;
		if(experience > 99) {
			level++;
			experience = 0;
			levelUp = true;
			Combatant::maxStats + levelUpStatsIncrement;
		}
		return levelUp;
	}
};
