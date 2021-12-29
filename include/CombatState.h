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

	sf::SoundBuffer soundBuffer;
	sf::Sound sound;
	sf::Music music;
	sf::Font font;

	Party party;
	Enemies enemies;
	TileMap map;

	KeyList* keybinds;

	CombatText lifeCounters;
	void addCombatString(const Player& player, AssetsManager& am, const int i);
	Position initialText{50.f, 300.f};
	float textIntervalHeight = 50;

	std::vector<Entity*> turnList;
	int currentCharacterTurn;
	bool nextTurn;

	Animation cursor;
	int curosrOrientation;
	sf::Clock cursorClock;

	void addActionMenu(const sf::RenderWindow* window);
	Buttons actionButtons;
	int actionButtonActive;

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
	void drawPlayer(sf::RenderWindow* window) override;
	StateAction shouldAct() override;
	sf::View getView() override { return view; };
	void stopMusic() override;
	void resumeMusic() override;
};