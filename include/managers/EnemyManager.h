#pragma once

#include <Enemy.h>
#include <string>
#include <unordered_map>

class EnemyManager {
  public:
	std::unordered_map<std::string, bool> enemiesDefeated;

	bool isEnemyDefeated(std::string &enemyName);
	bool allEnemiesDefeated();
	void initEnemyMap();
	void setEnemyDefeated(std::string enemyName);
};
