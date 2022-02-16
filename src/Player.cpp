#include <SFML/Window.hpp>

#include "Player.h"

// if a weapon is already weaponUsed it is swapped with the new one
// otherwise simply equips the new one
void Player::equip(Object* arms) {
	if(weapon != nullptr) {
		std::swap(weapon, arms);
	} else {
		weapon = arms;
		arms = nullptr;
	}
	weaponUsed = weapon->name;
	currentStats = maxStats + weapon->getStats();
}

void Player::move(const KeyAction key, TileMap* map) {
	setTileOccupation(map, animation.get_position(), false);
	animation.next(key);
	moveCharacter(key, &animation.sprite, map, animation.get_position());
	setTileOccupation(map, animation.get_position(), true);
}

bool Player::addExperience(const int xp) {
	experience += xp;
	bool levelUp = false;
	if(experience > 99) {
		level++;
		experience = 0;
		levelUp = true;
		Combatant::maxStats + levelUpStatsIncrement;
	}
	return levelUp;
}
