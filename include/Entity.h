#pragma once

#include <utility>

#include "Animation.h"

class Entity {
  public:
	Name name;
	Animation animation;
	bool is_solid{};
	bool can_interact{};
	sf::Vector2f size; // size in pixels (X offset, Y offset)

	Position get_position() const { return animation.get_position(); }
	void setTileOccupation(TileMap* map, bool isOccupied) const {
		map->setTileOccupation(animation.get_position(), isOccupied);
	}
};
