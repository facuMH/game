#pragma once

#include <string>
#include <utility>

#include <SFML/Audio/Sound.hpp>

#include "Inanimated.h"

class Character : public Entity {
  public:
	Stats currentStats;
	Stats maxStats;
	Weapon* weapon = nullptr;

	Name name;
	Character() : name(""), maxStats(0, 0, 0, 0), currentStats(0, 0, 0, 0) {}
	Character(Name new_name, Stats new_stats, Animation new_anim) : name(new_name), maxStats(new_stats), currentStats(new_stats) {
		animation = std::move(new_anim);
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
	void move(KeyAction key, sf::View* view);

	// TODO: multiple animations (idle, run, attack) perhaps on Entity.
};