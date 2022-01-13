#pragma once

#include "Combatant.h"
#include "Inanimated.h"

/// Class for playable characters
class Player : public Combatant {
  public:
	Weapon* weapon = nullptr;

	Player() {}
	Player(const Name& _name, const Stats& _stats, const Animation& _animation) : Entity(_name, _animation), Combatant(_stats, _stats) {
		is_solid = true;
		can_interact = true;
	}

	void equip(Weapon* arms);
	void move(KeyAction key, TileMap* map);
	bool isEnemy() override { return false; }
};
