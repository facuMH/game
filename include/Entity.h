#pragma once

#include "Animation.h"

class Entity {
	Animation animation;
	bool is_solid;
	bool can_interact;
	sf::Vector2f size; // size in pixels (X offset, Y offset)

public:
	
	Entity(Animation anim, bool isSolid, bool canInteract) : animation(anim), is_solid(isSolid), can_interact(canInteract) {}

	Position get_position() {
		return animation.get_position();
	}
};


