
#include "Characters.h"

// if a weapon is already equipped it is swapped with the new one
// otherwise simply equips the new one
void Character::equip(Weapon *arms) {
  if (weapon != nullptr) {
    std::swap(weapon, arms);
    Position pos = animation.get_position();

    // TODO: check for a free MapTile where you can actually drop the item.
    arms->drop(pos);
  } else {
    weapon = arms;
    arms = nullptr;
  }
}

void Character::move(const Position pos) { animation.move(pos); }