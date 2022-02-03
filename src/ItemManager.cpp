#include "ItemManager.h"
#include "asset_data.h"

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

// name of the item to be created, positioin where it should be displayed
Object ItemManager::make(const Name& itemName, const Position itemPosition) {
	Texture* t = am->getTexture(itemsPaths.at(itemName));
	sf::IntRect ir{{0, 0}, sf::Vector2i(t->getSize())};
	Animation a{t, ir, itemPosition};
	Stats s{itemStats.at(itemName)};
	Object ret{itemName, a, s};
	return ret;
}

// name of the item requested, positioin where it should be displayed in case it doesn't exist yet
Object* ItemManager::get(const Name& itemName, const Position itemPosition) {
	auto found = items.find(itemName);
	Object* item;
	if(found != items.end()) {
		item = &found->second;
	} else {
		item = &(items.emplace(itemName, make(itemName, itemPosition))).first->second;
	}
	return item;
}

// NOTE: only use this overload if you are sure the item has been loaded before
Object* ItemManager::get(const Name& itemName) {
	return &items.at(itemName);
}

void ItemManager::add_item(Player* player) {
	for(const auto item : itemStats) {
		if(!hasBeenPickedUp(item.first)) {
			get(item.first, {0,0});
			pickUp(item.first);
			break;
		}
	}
}