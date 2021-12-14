#include <SFML/Window.hpp>

#include "Characters.h"

// if a weapon is already equipped it is swapped with the new one
// otherwise simply equips the new one
void Character::equip(Weapon* arms) {
	if(weapon != nullptr) {
		std::swap(weapon, arms);
		Position pos = animation.get_position();

		// TODO: check for a free Tile where you can actually drop the item.
		arms->drop(pos);
	} else {
		weapon = arms;
		arms = nullptr;
	}
}

void Character::move(const KeyAction key, sf::View* view, const TileMap* map) {
	animation.next(key, view, const_cast<TileMap*>(map), 6.0f);
}