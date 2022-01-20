#pragma once

#include "characterSuperclasses/Entity.h"

class Object : public Entity {
	bool can_pick_up;
	int quantity;

  public:
	Object() : can_pick_up(true), quantity(1){};

	void drop(Position pos) { animation.set_position(pos); }
};

class Weapon : public Object {
	Name name;
	Stats stats;
  public:
	const Stats& getStats() { return stats; }
};
