#pragma once

#include <utility>

#include "Animation.h"

class Entity {
public:
  Animation animation;
  bool is_solid{};
  bool can_interact{};
  sf::Vector2f size; // size in pixels (X offset, Y offset)

  Entity()= default;
  Entity(bool isSolid, bool canInteract)
      : is_solid(isSolid), can_interact(canInteract) {}
  Entity(Animation anim, bool isSolid, bool canInteract)
      : animation(std::move(anim)), is_solid(isSolid), can_interact(canInteract) {}

  Position get_position() { return animation.get_position(); }
};
