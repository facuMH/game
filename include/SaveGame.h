#pragma once

#include <fstream>



#include "definitions.h"

class SaveGame {
  private:
	void UpdateCombatantEquipment();

  public:
	struct Stats player_stats;
    std::string save_game_file;

	SaveGame();
	~SaveGame();

	void NewGame();
    void DeleteItems();
    void SetItems();

	template <class Archive>
	void serialize(Archive &archive)
	{
		archive(CEREAL_NVP(player_stats));
	}

	void saveCurrentGame();
	void saveCurrentGame(const std::string &saved_game_path);
	void loadGame(const std::string &saved_game_path);
};