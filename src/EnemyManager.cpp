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
Enemy EnemyManager::makeEnemy(EnemyData &enemyData, AssetsManager &assetsManager) {
	Texture* texture = assetsManager.getTexture(enemyData.texturePath);
	Animation animation(texture, sf::IntRect(0, 0, TILESIZE, TILESIZE), enemyData.position);
	return {enemyData.name, Stats(15, 15, 15, 15, 15, 15), animation, MovementType::HORIZONTAL,
	    {30, 30}, 2.0f, enemyData.experience};
}
