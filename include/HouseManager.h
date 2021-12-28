#pragma once

#include "House.h"
#include "definitions.h"
class HouseManager {
  public:
	House getHouse(int doorNum) {
	    return houses.find(doorNum)->second;
	};
	void initHouses(AssetsManager assetsManager);

  private:
	std::unordered_map<int, House> houses;

};