#include <SFML/Window.hpp>

#include "Player.h"

// if a weapon is already equipped it is swapped with the new one
// otherwise simply equips the new one
void Player::equip(Weapon* arms) {
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

void Player::move(const KeyAction key, TileMap* map) {
	setTileOccupation(map, false);
	animation.next(key, map, 5.0f, animation.get_position());
	setTileOccupation(map, true);
}
