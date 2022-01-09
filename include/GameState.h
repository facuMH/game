#pragma once

#include "AssetsManager.h"
#include "PauseMenu.h"
#include "Player.h"
#include "State.h"
#include "TileMap.h"
#include "definitions.h"
#include "Villager.h"

class GameState : public State {
  private:
	TileMap map;
	Player player;
	std::vector<Villager> villagers;

	sf::View view;
	AssetsManager* am;
	KeyList* keybinds;
	sf::Clock clock;
	sf::SoundBuffer soundBuffer;
	sf::Sound gaspSound;
	sf::Music music;
	// just for demonstration purposes
	sf::Keyboard::Key previousKey;
	PauseMenu pausemenu;
	bool paused;
	

  public:
	// Constructor
	GameState(sf::RenderWindow* window, AssetsManager& am, std::vector<MapBackground*> textureSheets,
	    JSONFilePath& path, KeyList* gameSupportedKeys);
	// Destructor
	~GameState() override;

	// Functions
	void updatePauseMenuCloseButtons();
	void handlePause();

	void update(const float& dt) override;
	void render(sf::RenderWindow* window) override;
	void updateKeybinds(const float& dt) override;
	bool shouldQuit() override;
	void quitStateActions() override;
	StateAction handleKeys(sf::Keyboard::Key key) override;
	sf::View getView() override { return view; };
	void drawPlayer(sf::RenderWindow* window) override;
	Player* getPlayer() { return &player; };
	Villager createVillager(const std::string& textureName, Name name, Position position, MovementType movementDirection, float stepsize);
	StateAction shouldAct() override;
	void stopMusic() override;
	void resumeMusic() override;
};