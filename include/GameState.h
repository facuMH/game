#pragma once

#include "AssetsManager.h"
#include "Enemy.h"
#include "Player.h"
#include "State.h"
#include "TileMap.h"
#include "definitions.h"
#include "Villager.h"

class GameState : public State {
  private:
	TileMap map;
	Player player;
	Villagers villagers;
	Enemies enemies;
	bool isHouse;
	std::unordered_map<DoorNumber, Position> housePositions;

	sf::View view;
	AssetsManager* am;
	KeyList* keybinds;
	sf::Clock clock;
	sf::SoundBuffer soundBuffer;
	sf::Sound gaspSound;
	sf::Music music;
	// just for demonstration purposes
	sf::Keyboard::Key previousKey;

  public:
	// Constructors
	GameState(sf::RenderWindow* window, AssetsManager& am, std::vector<MapBackground*> textureSheets,
	    JSONFilePath& path, KeyList* gameSupportedKeys, Player& _player, Villagers& _villagers, MusicPath& musicPath);

	GameState(sf::RenderWindow* window, AssetsManager& am, std::vector<MapBackground*> textureSheets,
	    JSONFilePath& path, KeyList* gameSupportedKeys, Player& _player, Enemies& _enemies, MusicPath& musicPath);
	// Destructor
	~GameState() override;

	// Functions
	void update(const float& dt) override;
	void render(sf::RenderWindow* window) override;
	void updateKeybinds(const float& dt) override;
	bool shouldQuit() override;
	void quitStateActions() override;
	StateAction handleKeys(sf::Keyboard::Key key) override;
	sf::View getView() override { return view; };
	DoorNumber getCurrentDoorNumber(Position position);
	std::vector<std::pair<Position, DoorNumber>> listHousePositions();
	Position getCurrentPlayerPosition();
	void drawPlayer(sf::RenderWindow* window) override;
	Player* getPlayer() { return &player; };
	StateAction shouldAct() override;
	void stopMusic() override;
	void resumeMusic() override;
};