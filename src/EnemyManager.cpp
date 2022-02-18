#include "managers/EnemyManager.h"
#include "asset_data.h"


bool EnemyManager::allEnemiesDefeated() const {
	return enemiesDefeated.size() == ENEMYDATA.size() - 1;
}

bool EnemyManager::isEnemyDefeated(const Name& enemyName) {
	return enemiesDefeated.find(enemyName) != enemiesDefeated.end();
}

void EnemyManager::setEnemyDefeated(const Name& enemyName) {
	enemiesDefeated.emplace(enemyName);
}
Enemy EnemyManager::makeEnemy(const DoorNumber doorNumber, AssetsManager& assetsManager) {
	EnemyData enemyData = ENEMYDATA[doorNumber - 1];
	Enemy enemy;
	if(!isEnemyDefeated(enemyData.name)) {
		Texture* texture = assetsManager.getTexture(enemyData.texturePath);
		Animation animation(texture, sf::IntRect(0, 0, TILESIZE, TILESIZE), enemyData.position);
		enemy = {enemyData.name, Stats(15, 15, 15, 15, 15, 15), animation, MovementType::HORIZONTAL, {30, 30}, 2.0f,
		    enemyData.experience, enemyData.bodyPart};
	}
	return enemy;
}
