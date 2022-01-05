#pragma once

#include "Combatant.h"
#include "Inanimated.h"

/// Class for non-playable characters who engage in combat
class Enemy : public Combatant {
  public:
	Enemy() {}
	Enemy(Name _name, Stats _stats, Animation _animation) : Combatant(_stats, _stats) {
		name = _name;
		animation = std::move(_animation);
		is_solid = true;
		can_interact = true;
		currentStats = _stats;
	};
	bool isEnemy() { return true; }
};

Enemy createAlien(AssetsManager& am);