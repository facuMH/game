#pragma once

#include "AssetsManager.h"
#include "DialogueBox.h"
#include "Enemy.h"
#include "Player.h"
#include "State.h"
#include "TileMap.h"
#include "Villager.h"
#include "definitions.h"
#include "InteractionManager.h"

class GameState : public State {
  private:
	TileMap map;
	Player player;
	Villagers villagers;
	Enemies enemies;
	DialogueBox dialogueBox;
	bool inDialogue;
	sf::View view;
	AssetsManager* am;
	KeyList* keybinds;
	sf::Clock clock;
	std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
	std::unordered_map<std::string, sf::Sound> sounds;
	sf::Music music;
	// just for demonstration purposes
	sf::Keyboard::Key previousKey;
	float dialogueYPosition;

  public:
	bool isHouse;
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
	Position getCurrentPlayerPosition() override;
	void drawPlayer(sf::RenderWindow* window) override;
	Name getEntityInInteractionRange(Position position);
	void startDialogue(Name &characterName);
	Player* getPlayer() { return &player; };
	Enemy* getEnemy() { return &enemies[0]; }
	StateAction shouldAct() override;
	void stopMusic() override;
	void resumeMusic() override;
};