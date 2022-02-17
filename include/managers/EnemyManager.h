#pragma once

#include "AssetsManager.h"
#include "Enemy.h"
#include "asset_data.h"
#include <string>

class EnemyManager {
  public:
	std::unordered_set<Name> enemiesDefeated;

	bool isEnemyDefeated(const Name& enemyName);
	bool allEnemiesDefeated() const;
	void setEnemyDefeated(const Name& enemyName);
	Enemy makeEnemy(const DoorNumber doorNumber, AssetsManager& assetsManager);
};
