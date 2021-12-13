#pragma once

#include "AssetsManager.h"
#include "Characters.h"
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
	void addCombatString(const Character& c, AssetsManager& am, const int i);
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;
	Position initialText{50.f, 300.f};
	float textIntervalHeigh = 50;
	sf::Music music;

  public:
	// Constructor
	CombatState(sf::RenderWindow* window, AssetsManager& am, std::vector<MapBackground*> textureSheets,
	    JSONFilePath path, const Party& p, const Enemies& e, KeyList* gameSupportedKeys);

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