#pragma once

#include "Enemy.h"
#include "asset_data.h"
#include "AssetsManager.h"
#include <string>

class EnemyManager {
  public:
	std::unordered_set<Name> enemiesDefeated;

	bool isEnemyDefeated(const Name &enemyName);
	bool allEnemiesDefeated();
	void setEnemyDefeated(const Name& enemyName);
	Enemy makeEnemy(const DoorNumber doorNumber, AssetsManager& assetsManager);
};
