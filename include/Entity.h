#pragma once

#include <utility>

#include "Animation.h"

/// Base class for all entities, such as characters and items
class Entity {
  public:
	Name name;
	Animation animation;
	sf::Vector2f size; // size in pixels (X offset, Y offset)

	Entity() = default;
	Entity(const Name& _name, const Animation& _animation) {
		name = _name;
		animation = _animation;
	};

	virtual Position get_position() const { return animation.get_position(); }
};
