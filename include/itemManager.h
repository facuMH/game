#pragma once

#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "AssetsManager.h"
#include "Inanimated.h"
#include "definitions.h"

class ItemManager {
  private:
	std::unordered_map<std::string, Weapon> weapons;
	std::unordered_map<std::string, Potion> potions;
	std::unordered_map<Name, Stats> itemStats;
	std::unordered_set<Name> pickedUp;
	AssetsManager* am;

	Weapon make(const Name& name, const Position pos);
	Potion make(const Name& name, const Position pos, const int n);

  public:
	ItemManager(AssetsManager* am);
	Weapon* get(const Name& name, const Position pos);
	void pickUp(const Name& name) { pickedUp.emplace(name); }
	bool hasBeenPickedUp(const Name& name) { return pickedUp.find(name) != pickedUp.end(); }
};