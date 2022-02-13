#include "managers/HouseManager.h"
#include "asset_data.h"

House HouseManager::getHouse(DoorNumber doorNum) {
	HouseData houseData;
	for(auto& H : HOUSEDATA) {
		if(H.doorNumber == doorNum) {
			houseData = H;
			break;
		}
	}
	return {houseData.mapDesignPath, houseData.doorPosition};
}