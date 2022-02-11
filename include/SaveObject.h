#pragma once

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
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

	SaveObject() = default;
	SaveObject(int houseNumber, const Position& housePosition, const Position& mainGamePosition, int level)
	    : houseNumber(houseNumber), housePositionX(housePosition.x), housePositionY(housePosition.y),
	      mainGamePositionX(mainGamePosition.x), mainGamePositionY(mainGamePosition.y), level(level) {}

  private:
	// must be implemented for serialization
	template <class Archive>
	void serialize(Archive& ar) {
		ar(houseNumber, housePositionX, housePositionY, mainGamePositionX, mainGamePositionY, level);
	}
};
