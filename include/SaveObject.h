#pragma once

#include <cereal/cereal.hpp>
#include <fstream>
#include <iostream>

#include "AssetsPaths.h"
#include "definitions.h"


class SaveObject {
  public:
	int houseNumber;
	Position housePosition;
	Position mainGamePosition;
	int level;
	Stats currentStats;

	SaveObject() = default;
	SaveObject(const int houseNumber, const Position& housePosition, const Position& mainGamePosition, int level, Stats _currentStats)
	    : houseNumber(houseNumber), housePosition(housePosition),
	      mainGamePosition(mainGamePosition), level(level), currentStats(_currentStats) {}

	Position getHouseStatePosition() const { return housePosition; }
	Position getMainGamePosition() const { return mainGamePosition; }


	// must be implemented for serialization
	template <class Archive>
	void serialize(Archive& ar) {
		ar(CEREAL_NVP(houseNumber), CEREAL_NVP(housePosition.x), CEREAL_NVP(housePosition.y),
		    CEREAL_NVP(mainGamePosition.x), CEREAL_NVP(mainGamePosition.y), CEREAL_NVP(level), currentStats);
	}
};
