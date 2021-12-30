#include "AssetsPaths.h"
#include <HouseManager.h>


void HouseManager::initHouses(AssetsManager assetsManager) {

	EnemyData enemyData1 = {"Mole", MOLE.c, {30, 30}};
	House house1 = House(enemyData1, *assetsManager.getMapDesign(HOUSE1.c), {60, 68});
	houses.emplace(1, house1);

	EnemyData enemyData2 = {"Reptile", REPTILE.c, {30, 30}};
	House house2 = House(enemyData2, *assetsManager.getMapDesign(HOUSE2.c), {45, 100});
	houses.emplace(2, house2);

	EnemyData enemyData3 = {"Skull" , SKULL.c, {30, 30}};
	House house3 = House(enemyData3, *assetsManager.getMapDesign(HOUSE3.c), {60, 100});
	houses.emplace(3, house3);

	EnemyData enemyData4 = {"Slime", SLIME.c, {30, 30}};
	House house4 = House(enemyData4, *assetsManager.getMapDesign(HOUSE4.c), {80, 100});
	houses.emplace(4, house4);

	EnemyData enemyData5 = {"Axolotl", AXOLOTL.c, {30, 30}};
	House house5 = House(enemyData5, *assetsManager.getMapDesign(HOUSE5.c), {40, 30});
	houses.emplace(5, house5);

	EnemyData enemyData6 = {"Bamboo", BAMBOO.c, {30, 30}};
	House house6 = House(enemyData6, *assetsManager.getMapDesign(HOUSE6.c), {30, 30});
	houses.emplace(6, house6);
}