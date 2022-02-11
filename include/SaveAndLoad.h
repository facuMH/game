#pragma once

#include <fstream>
#include <iostream>

#include "definitions.h"
#include "AssetsPaths.h"


class SaveAndLoad {
  public:
	static void saveGame(SaveObject saveObject) {
		std::ofstream file;
		file.open("../saved_games/" + std::to_string(saveObject.slot) + ".txt", std::ofstream::trunc);
		file << saveObject.positionX << " " << saveObject.positionY << std::endl;
		file << saveObject.level << std::endl;
		file.close();
	};

	static SaveObject loadGame(int slot) {
	    std::ifstream ifs("../saved_games/" + std::to_string(slot) + ".txt");

		SaveObject saveObject{};
		if (ifs.is_open()) {
			ifs >> saveObject.slot;
			ifs >> saveObject.positionX >> saveObject.positionY;
			ifs >> saveObject.level;
		}
		ifs.close();
		return saveObject;
	};
};