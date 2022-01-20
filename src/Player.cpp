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

void Player::move(const KeyAction key, TileMap* map, Position position) {
	setTileOccupation(map, position, false);
	animation.next(key);
	moveCharacter(key, &animation.sprite, map,animation.get_position());
	setTileOccupation(map, animation.get_position(), true);
}
