#pragma once

#include "AssetsManager.h"
#include "Characters.h"
#include "State.h"
#include "TileMap.h"
#include "definitions.h"

class GameState : public State {
  private:
	TileMap map;
	Character player;
	sf::View view;
	AssetsManager* am;
	KeyList* keybinds;
	sf::Clock clock;
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;
	sf::Music music;
	// just for demonstration purposes
	sf::Keyboard::Key previousKey;

  public:
	// Constructor
	GameState(sf::RenderWindow* window, AssetsManager& am, std::vector<MapBackground*> textureSheets, JSONFilePath& path, KeyList* gameSupportedKeys);
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
	Character* getPlayer() { return &player; };
	StateAction shouldAct() override;
	void stopMusic() override;
	void resumeMusic() override;
};
