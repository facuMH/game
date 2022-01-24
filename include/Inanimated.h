#pragma once

#include "Entity.h"

class Object : public Entity {
  private:
	Stats stats;

  public:
	bool can_equip = true;
	Object() {};
	Object(const Name& n, const Animation& a, const Stats s) : Entity(n, a) {
		if(s.str == 0 && s.dex == 0) can_equip = false;
	}

	void drop(Position pos) { animation.set_position(pos); }
	Name getName() { return Entity::name; }
	Stats getStats() const { return stats; }
};