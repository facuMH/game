#pragma once

#include <string>

#include "Inanimated.h"

class Character : public Entity {
  Name name;
  Stats stats;
  Weapon *weapon = nullptr;

public:
  Character() : name(""), stats(0, 0, 0, 0) {}
  Character(Name new_name, Stats new_stats, Animation new_anim)
      : name(new_name), stats(new_stats) {
    animation = new_anim;
    is_solid = true;
    can_interact = true;
  }

  int get_str() { return stats.str; }
  int get_dex() { return stats.dex; }
  int get_hp() { return stats.hp; }
  int get_mana() { return stats.mana; }

  void set_stats(Stats new_stats) { stats = new_stats; }

  void apply_damage(const int damage) { stats.hp -= damage; }
  void heal(const int health) { stats.hp += health; }
  void spend_mana(const int use) { stats.mana -= use; }
  void recover_mana(const int recover) { stats.mana += recover; }

  void equip(Weapon *arms);
  void move(const Position pos);

  // TODO: multiple animations (idle, run, atack) perhaps on Entity.
};