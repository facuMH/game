#pragma once

#include "Entity.h"

class Object : public Entity {
	Name name;

  public:
	bool can_equip;
	Object() : can_equip(true){};
	Object(const Name& n, const Animation& a) : Entity(n, a), can_equip(true) {}

	void drop(Position pos) { animation.set_position(pos); }
	Name getName() { return name; }
};

class Weapon : public Object {
	Stats stats;

  public:
	Weapon() = default;
	Weapon(const Name& n, const Animation& a, const Stats s) : Object(n, a), stats(s) {}
	const Stats& getStats() { return stats; }
};

class Potion : public Object {
	int heals;

  public:
	int quantity;
	Potion() : quantity(1), heals(0) {}
	Potion(const Name& n, const Animation& a, const int q, const int h) : Object(n, a), quantity(q), heals(h) {
		can_equip = false;
	}
	int consume() { return heals; }
};