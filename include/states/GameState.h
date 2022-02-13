#pragma once

#include "AssetsManager.h"
#include "DialogueBox.h"
#include "Enemy.h"
#include "InteractionManager.h"
#include "Player.h"
#include "State.h"
#include "TileMap.h"
#include "Villager.h"
#include "definitions.h"

class GameState : public State {
  private:
	TileMap map;
	Player player;
	Villagers villagers;
	Enemies enemies;
	DialogueBox dialogueBox;
	bool inDialogue;
	AssetsManager* am;
	KeyList* keybinds;
	sf::Clock clock;
	sf::Keyboard::Key previousKey; // for gasping sound effect
	float dialogueYPosition;       // position depends on current view
	Object* item = nullptr;        // if in a house there will be an item, if not previously picked up
	bool itemPicked = false;


  public:
	bool isHouse;
	DoorNumber doorNumber;
	// Constructors
	GameState(sf::RenderWindow* window, AssetsManager& am, std::vector<MapBackground*> textureSheets,
	    JSONFilePath& path, KeyList* gameSupportedKeys, Player& _player, Villagers& _villagers, MusicPath& musicPath);

	GameState(sf::RenderWindow* window, AssetsManager& am, std::vector<MapBackground*> textureSheets,
	    JSONFilePath& path, KeyList* gameSupportedKeys, Player& _player, Enemies& _enemies, MusicPath& musicPath,
	    Object* _item, DoorNumber _doorNumber);
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
	void drawPlayer(sf::RenderWindow* window) override;
	StateAction shouldAct() override;

	DoorNumber getCurrentDoorNumber(Position position);
	std::vector<std::pair<Position, DoorNumber>> listHousePositions();
	Position getCurrentPlayerPosition();
	Name getEntityInInteractionRange(Position position);
	void startDialogue(Name& characterName);
	Enemy* getEnemy() { return &enemies[0]; }
	Name getItemName() const { return item->getName(); }
};