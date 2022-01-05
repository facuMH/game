#pragma once

#include "definitions.h"
#include "Entity.h"
#include "Inanimated.h"

/// Class for non-playable characters who engage in combat
class Enemy : public Entity {
  public:
	Enemy(Name _name, Stats _stats, Animation _animation) : maxStats(_stats), currentStats(_stats) {
		name = _name;
		animation = std::move(_animation);
		is_solid = true;
		can_interact = true;
		currentStats = _stats;
	};

	Stats currentStats;
	Stats maxStats;
};