#pragma once

#include <utility>

#include "Animation.h"
#include "Entity.h"
#include "definitions.h"

class Villager : public Entity {
  private:

  public:
	explicit Villager(Animation new_anim, MovementDirection dir) {
		animation = std::move(new_anim);
		movementDirection = dir;
		is_solid = true;
		can_interact = true;
	}
	// TODO Define an area in which the villager can move
	Position startPosition;
	Position endPosition;
	Position currentPosition;
	MovementDirection movementDirection;

	void blockTile(TileMap* map) const {
		map->occupyTile(currentPosition);
	}
	void move(TileMap* map, float stepsize) {
		// TODO
	};
};