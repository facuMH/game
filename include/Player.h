#pragma once

#include "Combatant.h"
#include "Inanimated.h"

/// Class for playable characters
class Player : public Combatant {
  public:
	Weapon* weapon = nullptr;

	Player() {}
	Player(Name _name, Stats _stats, Animation _animation) : Combatant(_stats, _stats) {
		name = _name;
		animation = std::move(_animation);
		is_solid = true;
		can_interact = true;
	}

	void equip(Weapon* arms);
	void move(KeyAction key, TileMap* map);
	bool isEnemy() override { return false; }
};
