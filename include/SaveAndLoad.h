#pragma once
#include "SaveObject.h"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

class SaveAndLoad {
  public:


	static SaveObject loadGame() {
		std::ifstream ifs(SAVED.c);

		SaveObject saveObject{};
		if (ifs.is_open()) {
			ifs >> saveObject.houseNumber;
			ifs >> saveObject.housePosition.x >> saveObject.housePosition.y;
			ifs >> saveObject.mainGamePosition.x >> saveObject.mainGamePosition.y;
			ifs >> saveObject.level;
		}
		ifs.close();
		return saveObject;
	};


	static void saveGame(int _houseNumber, Position _housePosition, Position _mainGamePosition, int _level) {
		std::ofstream file;
		file.open(SAVED.c, std::ofstream::trunc); // deletes the contents of the file before writing
		file << _houseNumber << std::endl;
		file << _housePosition.x << " " << _housePosition.y << std::endl;
		file << _mainGamePosition.x << " " << _mainGamePosition.y << std::endl;
		file << _level << std::endl;
		file.close();
	};
};