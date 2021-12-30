#pragma once

#include "definitions.h"
#include "Enemy.h"
#include "TileMap.h"

class House {
  public:
	EnemyData enemyData;
	JSONFilePath houseDesignPath;
	Position doorPosition;

	House(EnemyData _enemyData, JSONFilePath& _houseDesignPath, Position _doorPosition) {
		enemyData = _enemyData;
		houseDesignPath = _houseDesignPath;
		doorPosition = _doorPosition;
	};
};