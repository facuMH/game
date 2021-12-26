#pragma once

#include "Entity.h"
#include "Inanimated.h"

/// Class for playable characters
class Player : public Entity {
  public:
	Stats currentStats;
	Stats maxStats;
	Weapon* weapon = nullptr;

	Player() : maxStats(0, 0, 0, 0), currentStats(0, 0, 0, 0) {}
	Player(Name _name, Stats _stats, Animation _animation) : maxStats(_stats), currentStats(_stats) {
		name = _name;
		animation = std::move(_animation);
		is_solid = true;
		can_interact = true;
	}

	int get_str() const { return currentStats.str; }
	int get_dex() const { return currentStats.dex; }
	int get_hp() const { return currentStats.hp; }
	int get_mana() const { return currentStats.mana; }

	void set_stats(Stats new_stats) { currentStats = new_stats; }
	void reset_stats() { currentStats = maxStats; }

	void apply_damage(const int damage) { currentStats.hp -= damage; }
	void heal(const int health) { currentStats.hp += health; }
	void spend_mana(const int use) { currentStats.mana -= use; }
	void recover_mana(const int recover) { currentStats.mana += recover; }

	void equip(Weapon* arms);
	void move(KeyAction key, TileMap* map);
};
