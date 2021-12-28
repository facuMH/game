#include "AssetsPaths.h"
#include <HouseManager.h>


void HouseManager::initHouses(AssetsManager assetsManager) {
	std::vector<MapBackground*> tileSheets = {assetsManager.getMap(TILESHEET_INTERIOR_FLOOR.c),
	    assetsManager.getMap(TILESHEET_INTERIOR_FLOOR.c), assetsManager.getMap(TILESHEET_FURNITURE.c)};

	House house1 = House(1, Enemy(), tileSheets, *assetsManager.getMapDesign(HOUSE1.c), {30, 30});
	houses.emplace(1, house1);

	House house2 = House(2, Enemy(), tileSheets, *assetsManager.getMapDesign(HOUSE2.c), {30, 30});
	houses.emplace(2, house2);

	House house3 = House(3, Enemy(), tileSheets, *assetsManager.getMapDesign(HOUSE3.c), {30, 30});
	houses.emplace(3, house3);

	House house4 = House(4, Enemy(), tileSheets, *assetsManager.getMapDesign(HOUSE4.c), {30, 30});
	houses.emplace(4, house4);
}
