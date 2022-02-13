#include "managers/EnemyManager.h"
#include <asset_data.h>

void EnemyManager::initEnemyMap() {
	for(auto& E : ENEMYDATA) {
		enemiesDefeated.emplace(E.name, false);
	}
}

bool EnemyManager::allEnemiesDefeated() {
	return std::all_of(enemiesDefeated.begin(), enemiesDefeated.end(),
	    [](const std::pair<const std::string, bool>& entry) { return entry.second; });
}

bool EnemyManager::isEnemyDefeated(std::string &enemyName) {
	return enemiesDefeated.find(enemyName)->second;
}

void EnemyManager::setEnemyDefeated(std::string enemyName) {
	enemiesDefeated.find(enemyName)->second = true;
}
