#include <filesystem>
#include "AssetsManager.h"
#include "SaveGame.h"
#include "AssetsPaths.h"


namespace fs = std::filesystem;
AssetsManager assetsManager;

SaveGame::SaveGame()
{
	Texture* play_text = assetsManager.getTexture(NINJA_WALK.c);
	Animation player_animation(play_text, sf::IntRect(0, 0, TILESIZE, TILESIZE), Position(50, 50));
	player = Player("Adventurer", Stats(0, 0, 0, 0, 0, 0), player_animation, 5.0f);
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
	Texture* play_text = assetsManager.getTexture(NINJA_WALK.c);
	Animation player_animation(play_text, sf::IntRect(0, 0, TILESIZE, TILESIZE), Position(50, 50));
	player = Player("Adventurer", Stats(15, 20, 50, 30, 15, 1), player_animation, 5.0f);
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
		ar(player);
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
		ar(player);
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
		ir(player);
        save_game_file = saved_game_path;
	}
}
