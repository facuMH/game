#pragma once

#include "Entity.h"
#include "Inanimated.h"

/// Class for non-playable characters who engage in combat
class Enemy : public Entity {
  public:
	Enemy() : maxStats(0, 0, 0, 0), currentStats(0, 0, 0, 0) {}
	Enemy(Name _name, Stats _stats, Animation _animation) : maxStats(_stats), currentStats(_stats) {
		name = _name;
		animation = std::move(_animation);
		is_solid = true;
		can_interact = true;
		currentStats = _stats;
	};

	Stats currentStats;
	Stats maxStats;
	Weapon* weapon = nullptr;
};
