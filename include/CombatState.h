#pragma once

#include "AssetsManager.h"
#include "Enemy.h"
#include "Player.h"
#include "State.h"
#include "TileMap.h"
#include "definitions.h"

class CombatState : public State {
  private:
	sf::View view;
	Party party;
	Enemies enemies;
	TileMap map;
	CombatText lifeCounters;
	KeyList* keybinds;
	void addCombatString(const Player& player, AssetsManager& am, const int i);
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;
	Position initialText{50.f, 300.f};
	float textIntervalHeight = 50;
	sf::Music music;

  public:
	// Constructor
	CombatState(sf::RenderWindow* window, AssetsManager& am, std::vector<MapBackground*> textureSheets,
	    JSONFilePath& path, const std::vector<Player>& p, const std::vector<Enemy>& e, KeyList* gameSupportedKeys);

	// Destructor
	~CombatState() override;

	// Functions
	void update(const float& dt) override;
	void render(sf::RenderWindow* window) override;
	void updateKeybinds(const float& dt) override;
	bool shouldQuit() override;
	void quitStateActions() override;
	StateAction handleKeys(sf::Keyboard::Key key) override;
	Position getCurrentPlayerPosition() override { return {0, 0}; };
	void drawPlayer(sf::RenderWindow* window) override;
	StateAction shouldAct() override;
	sf::View getView() override { return view; };
	void stopMusic() override;
	void resumeMusic() override;
};