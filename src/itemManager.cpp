#include <iostream>
#include <string>

#include "asset_data.h"
#include "itemManager.h"

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

Object ItemManager::make(const Name& name, const Position pos) {
	Texture* t = am->getTexture(itemsPaths.at(name));
	sf::IntRect ir{{0, 0}, sf::Vector2i(t->getSize())};
	Animation a{t, ir, pos};
	Stats s{itemStats.at(name)};
	Object ret{name, a, s};
	return ret;
}

Object* ItemManager::get(const Name& name, const Position pos) {
	auto found = items.find(name);
	Object* item;
	if(found != items.end()) {
		item = &found->second;
	} else {
		item = &(items.emplace(name, make(name, pos))).first->second;
	}
	return item;
}

Object* ItemManager::get(const Name& name) {
	return &items.at(name);
}