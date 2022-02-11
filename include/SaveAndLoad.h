#pragma once
#include "SaveObject.h"

#include <cereal/archives/json.hpp>

class SaveAndLoad {
  public:
	static void saveGame(SaveObject saveObject) {
		std::ofstream ofs(SAVED.c);
		cereal::JSONOutputArchive oarchive(ofs); // Create an output archive
		oarchive(saveObject); // Write the data to the archive
	}

	static SaveObject loadGame() {
		std::ifstream ifs(SAVED.c);
		cereal::JSONInputArchive iarchive(ifs); // Create an input archive
		SaveObject saveObject;
		iarchive(saveObject); // Read the data from the archive
		return saveObject;
	}
};
