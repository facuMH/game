#pragma once

#include "Entity.h"
#include "definitions.h"

class Combatant : public Entity {
  public:
	Stats currentStats;
	Stats maxStats;

	Combatant(){};
	Combatant(Stats max, Stats current) : maxStats(max), currentStats(current){};

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

	int attack() const { return currentStats.str + currentStats.baseAtk; }
	int defend() const { return currentStats.dex + currentStats.armor; }
	int atkDamage() const { return currentStats.str; }
	virtual bool isEnemy() = 0;
};