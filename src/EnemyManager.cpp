#include "managers/EnemyManager.h"
#include <asset_data.h>


bool EnemyManager::allEnemiesDefeated() {
	return enemiesDefeated.size() == ENEMYDATA.size();
}

bool EnemyManager::isEnemyDefeated(std::string &enemyName) {
	return enemiesDefeated.find(enemyName) != enemiesDefeated.end();
}

void EnemyManager::setEnemyDefeated(const std::string& enemyName) {
	enemiesDefeated.emplace(enemyName);
}
