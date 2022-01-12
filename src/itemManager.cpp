#include <iostream>
#include <string>

#include "AssetsPaths.h"
#include "itemManager.h"

Weapon ItemManager::make(const Name& name) {
	return Weapon{};
}

Potion ItemManager::make(const Name& name, const int n) {
	return Potion{};
}

ItemManager::ItemManager(AssetsManager* am) {
	// itemStats
	std::ifstream ifs(ITEMSLIST.c);
	std::string line;
	std::string name;
	int std, dex, hp, mana, armor, atk;
	// discarding the first line since it's a comment
	std::getline(ifs, line);
	while(!ifs.eof()) {
		ifs >> name >> std >> dex >> hp >> mana >> armor >> atk;
		itemStats.emplace(name, Stats{std, dex, hp, mana, armor, atk});
	}
	ifs.close();
}

Weapon ItemManager::get(const Name& name) {
	auto found = weapons.find(name);
	Weapon weapon;
	if(found != weapons.end()) {
		weapon = found->second;
	} else {
		weapon = make(name);
	}
	return weapon;
}