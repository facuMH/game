#pragma once

#include "definitions.h"
#include "Enemy.h"
#include "TileMap.h"

class House {
  public:
	EnemyData enemyData;
	JSONFilePath houseDesignPath;
	Position enterPosition;

	House(EnemyData _enemyData, JSONFilePath& _houseDesignPath, Position _enterPosition) {
		enemyData = _enemyData;
		houseDesignPath = _houseDesignPath;
		enterPosition = _enterPosition;
	};
};