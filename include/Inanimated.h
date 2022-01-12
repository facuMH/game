#pragma once

#include "Entity.h"

class Object : public Entity {
	Name name;
	bool can_pick_up;

  public:
	Object() : can_pick_up(true){};

	void drop(Position pos) { animation.set_position(pos); }
};

class Weapon : public Object {
	Stats stats;

  public:
	const Stats& getStats() { return stats; }
};

class Potion : public Object {
	int heals;
  public:
	int quantity;
	Potion() : quantity(1), heals(0) {}
	Potion(const int q, const int h) : quantity(q), heals(h) {}
	int consume() { return heals; }
};