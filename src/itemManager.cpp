#include <iostream>
#include <string>

#include "asset_data.h"
#include "itemManager.h"

Weapon ItemManager::make(const Name& name, const Position pos) {
	Texture* t = am->getTexture(itemsPaths.at(name));
	sf::IntRect ir{{0, 0}, sf::Vector2i(t->getSize())};
	Animation a{t, ir, pos};
	Stats s{itemStats.at(name)};
	Weapon ret{name, a, s};
	return ret;
}

Potion ItemManager::make(const Name& name, const Position pos, const int n) {
	Texture* t = am->getTexture(itemsPaths.at(name));
	sf::IntRect ir{{0, 0}, sf::Vector2i(t->getSize())};
	Animation a{t, ir, pos};
	Stats s{itemStats.at(name)};
	Potion ret{name, a, n, s.hp};
	return ret;
}

ItemManager::ItemManager(AssetsManager* _am) : am(_am) {
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

Weapon* ItemManager::get(const Name& name, const Position pos) {
	auto found = weapons.find(name);
	Weapon* weapon;
	if(found != weapons.end()) {
		weapon = &found->second;
	} else {
		weapon = &(weapons.emplace(name, make(name, pos))).first->second;
	}
	return weapon;
}