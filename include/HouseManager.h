#pragma once

#include "House.h"
#include "definitions.h"
class HouseManager {
  public:
	static House getHouse(DoorNumber doorNum);
};