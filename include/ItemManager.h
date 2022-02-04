#pragma once

#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "AssetsManager.h"
#include "Inanimated.h"
#include "definitions.h"

class InventoryState;

class ItemManager {
  private:
	std::unordered_map<std::string, Object> items;
	std::unordered_map<Name, Stats> itemStats;
	std::unordered_set<Name> playerInventory;
	AssetsManager* am;

	Object make(const Name& name, const Position& pos);

	friend InventoryState;

  public:
	explicit ItemManager(AssetsManager* am);
	Object* get(const Name& name, const Position& pos);
	// WARNING: only use the overload that doesn't require position, if you are *sure* the weapon already exists.
	Object* get(const Name& name);
	void pickUp(const Name& name) { playerInventory.emplace(name); }
	bool hasBeenPickedUp(const Name& name) { return playerInventory.find(name) != playerInventory.end(); }
	void add_item();
};