#pragma once

#include <utility>

#include "Animation.h"

class Entity {
  public:
	Animation animation;
	Position currentPosition;
	bool is_solid{};
	bool can_interact{};
	sf::Vector2f size; // size in pixels (X offset, Y offset)

	Entity() = default;
	Entity(bool isSolid, bool canInteract) : is_solid(isSolid), can_interact(canInteract) {}
	Entity(Animation& anim, bool isSolid, bool canInteract)
	    : animation(anim), is_solid(isSolid), can_interact(canInteract) {}

	Position get_position() const { return animation.get_position(); }
	void setTileOccupation(TileMap* map, bool isOccupied) const { map->setTileOccupation(animation.get_position(), isOccupied); }

};
