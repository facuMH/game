#pragma once

#include <unordered_map>

#include "AssetsManager.h"
#include "AssetsPaths.h"
#include "Inanimated.h"

#include "definitions.h"

class ItemManager {
  private:
	std::unordered_map<std::string, Weapon> weapons;

  public:
	ItemManager(AssetsManager* am);
	Weapon get(const Name& name);


};