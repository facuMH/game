#pragma once

#include "definitions.h"
#include "Entity.h"

class Combatant : public virtual Entity {
  public:
	Stats currentStats;
	Stats maxStats;

	Combatant() = default;
	Combatant(Stats max, Stats current) {
	    maxStats = max;
		currentStats = current;
	};

	~Combatant() = default;

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