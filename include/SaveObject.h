#pragma once

#include <fstream>
#include <iostream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "definitions.h"
#include "AssetsPaths.h"


class SaveObject {
  public:
	int houseNumber;
	Position housePosition;
	Position mainGamePosition;
	int level;
	SaveObject() = default;
	SaveObject(int _houseNumber, Position _housePosition, Position _mainGamePosition, int _level) {
		this->houseNumber = _houseNumber;
		this->housePosition = _housePosition;
		this->mainGamePosition = _mainGamePosition;
		this->level = _level;
	}

};

