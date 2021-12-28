#pragma once

#include "definitions.h"
#include "Enemy.h"
#include "TileMap.h"

class House {
  public:
	int doorNum;
	Enemy enemy;
	std::vector<MapBackground*> tileSheets;
	JSONFilePath houseDesignPath;
	Position enterPosition;

	House(int _doorNum, Enemy _enemy, std::vector<MapBackground*> _tileSheets, JSONFilePath& _houseDesignPath, Position _enterPosition) {
		doorNum = _doorNum;
		enemy = _enemy;
		tileSheets = _tileSheets;
		houseDesignPath = _houseDesignPath;
		enterPosition = _enterPosition;
	};
};