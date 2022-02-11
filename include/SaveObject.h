#pragma once

#include <cereal/cereal.hpp>
#include <fstream>
#include <iostream>

#include "AssetsPaths.h"
#include "definitions.h"


class SaveObject {
  public:
	int houseNumber;
	float housePositionX;
	float housePositionY;
	float mainGamePositionX;
	float mainGamePositionY;
	int level;
	Stats currentStats;

	SaveObject() = default;
	SaveObject(int houseNumber, const Position& housePosition, const Position& mainGamePosition, int level, Stats _currentStats)
	    : houseNumber(houseNumber), housePositionX(housePosition.x), housePositionY(housePosition.y),
	      mainGamePositionX(mainGamePosition.x), mainGamePositionY(mainGamePosition.y), level(level), currentStats(_currentStats) {}

	Position getHouseStatePosition() const { return {housePositionX, housePositionY}; }
	Position getMainGamePosition() const { return {mainGamePositionX, mainGamePositionY}; }



	// must be implemented for serialization
	template <class Archive>
	void serialize(Archive& ar) {
		ar(CEREAL_NVP(houseNumber), CEREAL_NVP(housePositionX), CEREAL_NVP(housePositionY),
		    CEREAL_NVP(mainGamePositionX), CEREAL_NVP(mainGamePositionY), CEREAL_NVP(level), currentStats);
	}
};
