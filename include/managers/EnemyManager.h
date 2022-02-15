#pragma once

#include <Enemy.h>
#include <string>

class EnemyManager {
  public:
	std::unordered_set<Name> enemiesDefeated;

	bool isEnemyDefeated(Name &enemyName);
	bool allEnemiesDefeated();
	void setEnemyDefeated(const Name& enemyName);
};
