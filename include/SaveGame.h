#pragma once

#include <fstream>
#include "definitions.h"
#include "Player.h"
class SaveGame {
  private:
	void UpdateCombatantEquipment();
	Player player;

  public:
    std::string save_game_file;
	Player& getPlayer() { return player; };

	SaveGame();
	~SaveGame();

	void NewGame();
    void DeleteItems();
    void SetItems();

	template <class Archive>
	void serialize(Archive &archive)
	{
		archive(CEREAL_NVP(player));
	}

	void saveCurrentGame();
	void saveCurrentGame(const std::string &saved_game_path);
	void loadGame(const std::string &saved_game_path);
};