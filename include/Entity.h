#pragma once

#include "Animation.h"

class Entity {
  public:
	Animation animation;
	bool is_solid = true;
	bool can_interact = true;
	sf::Vector2f size; // size in pixels (X offset, Y offset)

	Entity(){};
	Entity(bool isSolid, bool canInteract) : is_solid(isSolid), can_interact(canInteract) {}
	Entity(Animation anim, bool isSolid, bool canInteract) : animation(anim), is_solid(isSolid), can_interact(canInteract) {}

	Position get_position() { return animation.get_position(); }
};
