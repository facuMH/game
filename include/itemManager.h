#pragma once

#include <tuple>
#include <unordered_map>
#include <vector>

#include "AssetsManager.h"
#include "Inanimated.h"

#include "definitions.h"

class ItemManager {
  private:
	std::unordered_map<std::string, Weapon> weapons;
	std::unordered_map<std::string, Potion> potions;
	std::unordered_map<Name, Stats> itemStats;
	AssetsManager* am;

	Weapon make(const Name& name);
	Potion make(const Name& name, const int n);

  public:
	ItemManager(AssetsManager* am);
	Weapon get(const Name& name);
};