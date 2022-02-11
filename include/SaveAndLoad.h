#pragma once

#include <fstream>
#include <iostream>

#include "definitions.h"
#include "AssetsPaths.h"


class SaveAndLoad {
  public:
	static void saveGame(SaveObject saveObject) {
		std::ofstream file;
		file.open(SAVED.c, std::ofstream::trunc); // deletes the contents of the file before writing
		file << saveObject.houseNumber << std::endl;
		file << saveObject.positionX << " " << saveObject.positionY << std::endl;
		file << saveObject.level << std::endl;
		file.close();
	};

	static SaveObject loadGame() {
	    std::ifstream ifs(SAVED.c);

		SaveObject saveObject{};
		if (ifs.is_open()) {
			ifs >> saveObject.houseNumber;
			ifs >> saveObject.positionX >> saveObject.positionY;
			ifs >> saveObject.level;
		}
		ifs.close();
		return saveObject;
	};
};