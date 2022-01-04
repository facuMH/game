#pragma once

#include "definitions.h"
#include "Enemy.h"
#include "TileMap.h"

class House {
  public:
	JSONFilePath houseDesignPath;
	Position doorPosition;

	House(JSONFilePath& _houseDesignPath, Position _doorPosition) {
		houseDesignPath = _houseDesignPath;
		doorPosition = _doorPosition;
	};
};