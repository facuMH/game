#pragma once

#include "Entity.h"

/// Base class for inanimate entities such as items and weapons
class Object : public Entity {
  private:
	Stats stats;

  public:
	bool can_equip = true;
	Object() = default;;
	Object(const Name& n, const Animation& a, const Stats s) : Entity(n, a) {
		if(s.str == 0 && s.dex == 0) can_equip = false;
	}

	Name getName() { return Entity::name; }
	Stats getStats() const { return stats; }
};