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

	Entity() = default;
	Entity(Name _name, Animation _animation) {
	    name = _name;
		animation = _animation;
	};

	virtual Position get_position() const { return animation.get_position(); }
	virtual void setTileOccupation(TileMap* map, bool isOccupied) const {
		map->setTileOccupation(animation.get_position(), isOccupied);
	}
};

