#include <filesystem>

#include "SaveGame.h"


namespace fs = std::filesystem;

SaveGame::SaveGame()
    : player_stats(16,17,18,19,20,21)
{

}

SaveGame::~SaveGame() = default;

void SaveGame::DeleteItems()
{

}

void SaveGame::SetItems()
{

}

void SaveGame::NewGame()
{

}

void SaveGame::UpdateCombatantEquipment()
{

}

void SaveGame::saveCurrentGame()
{
	std::stringstream ss;

	int count = 0;
	if (!fs::exists("game_save/")) {
		fs::create_directories("game_save/");
	}

	for (auto &p : fs::directory_iterator("game_save/")) {
		count++;
	}

	std::string output_file = "game_save/saved_game_" + std::to_string(++count) + ".json";

	{
		cereal::JSONOutputArchive ar(ss);
		player_stats = {1,2,3,4,5,6};
		ar(player_stats);
	}

	std::ofstream outFile(output_file);

	outFile << ss.rdbuf();
    
    save_game_file = output_file;
}

void SaveGame::saveCurrentGame(const std::string & output_file)
{
    std::stringstream ss;
    std::remove(output_file.c_str());

    {
		cereal::JSONOutputArchive ar(ss);
        player_stats = {11,22,33,44,55,66};
		ar(player_stats);
    }

	std::ofstream outFile(output_file);

	outFile << ss.rdbuf();
}

void SaveGame::loadGame(const std::string &saved_game_path)
{
	std::ifstream file(saved_game_path);
	std::stringstream ss;
	if (file) {
		ss << file.rdbuf();
	} else {
		return;
	}
	{
		cereal::JSONInputArchive ir(ss);
		ir(player_stats);
        save_game_file = saved_game_path;
	}
}
