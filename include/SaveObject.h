#pragma once

#include <fstream>
#include <iostream>

#include <cereal/cereal.hpp>
#include <cereal/types/unordered_set.hpp>

#include "AssetsPaths.h"
#include "definitions.h"
#include "managers/EnemyManager.h"
#include "managers/ItemManager.h"

/// Class which defines which attributes of a game are saved and loaded
class SaveObject {
  public:
	int houseNumber;
	Position housePosition;
	Position mainGamePosition;
	int level;
	Stats currentStats;
	std::unordered_set<Name> items;
	std::unordered_set<Name> defeatedEnemies;
	std::unordered_set<Name> bodyParts;
	Name equippedWeapon;

	SaveObject() = default;
	SaveObject(const int houseNumber, const Position& housePosition, const Position& mainGamePosition, int level,
	    Stats _currentStats, ItemManager* itemManager, EnemyManager* enemyManager, const Name& _equippedWeapon)
	    : houseNumber(houseNumber), housePosition(housePosition), mainGamePosition(mainGamePosition), level(level),
	      currentStats(_currentStats), items(itemManager->playerInventory),
	      defeatedEnemies(enemyManager->enemiesDefeated), equippedWeapon(_equippedWeapon),
	      bodyParts(itemManager->grandmaParts) {}

	Position getHouseStatePosition() const { return housePosition; }
	Position getMainGamePosition() const { return mainGamePosition; }


	// must be implemented for serialization
	template <class Archive>
	void serialize(Archive& ar) {
		ar(CEREAL_NVP(houseNumber), CEREAL_NVP(housePosition.x), CEREAL_NVP(housePosition.y),
		    CEREAL_NVP(mainGamePosition.x), CEREAL_NVP(mainGamePosition.y), CEREAL_NVP(level), currentStats,
		    CEREAL_NVP(items), CEREAL_NVP(defeatedEnemies), CEREAL_NVP(equippedWeapon), CEREAL_NVP(bodyParts));
	}
};
