#pragma once

#include <cereal/archives/json.hpp>
#include <filesystem>

#include "SaveObject.h"

namespace fs = std::filesystem;

class SaveAndLoad {
  public:
	static void saveGame(SaveObject saveObject) {
		if(!fs::is_directory(SAVED_GAMES)) {
			fs::create_directory(SAVED_GAMES);
		}
		std::ofstream ofs(SAVED.c);
		cereal::JSONOutputArchive outputArchive(ofs); // Create an output archive
		outputArchive(saveObject);                    // Write the data to the archive
	}

	static SaveObject loadGame() {
		std::ifstream ifs(SAVED.c);
		cereal::JSONInputArchive inputArchive(ifs); // Create an input archive
		SaveObject saveObject{};
		inputArchive(saveObject); // Read the data from the archive
		return saveObject;
	}
};
