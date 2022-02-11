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
	Position housePosition;
	Position mainGamePosition;
	int level;

	SaveObject() = default;

  private:
	// must be implemented for serialization
	template <class Archive>
	void serialize(Archive& ar) {
		ar(houseNumber, housePosition.x, housePosition.y, mainGamePosition.x, mainGamePosition.y, level);
	}
};
