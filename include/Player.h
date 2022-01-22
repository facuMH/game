#pragma once

#include "Inanimated.h"
#include "entity_attributes/Combatant.h"
#include "entity_attributes/SteeredMovement.h"

/// Class for playable characters
class Player : public Entity, public Combatant, public SteeredMovement {
public:
  Object *weapon = nullptr;

  Player() {}
  Player(const Name &_name, const Stats &_stats, Animation _animation,
         float _stepsize)
      : Entity(_name, _animation), Combatant(_stats, _stats),
        SteeredMovement(_stepsize) {}

  void equip(Object *arms);
  void move(KeyAction key, TileMap *map);
  bool isEnemy() override { return false; }
};
