#pragma once

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "AssetsManager.h"
#include "Button.h"
#include "State.h"
#include "SaveGame.h"

class LoadGameState : public State {
  private:
	sf::View view;
	sf::RectangleShape background;
	sf::Font font;
	sf::SoundBuffer soundBuffer;
	sf::Sound blipSound;
	sf::Music music;

	Position_i mousePoseWindow;
	Position mousePosView;

	KeyList* supportedKeys;
	Buttons buttons;

	int activeButton;
	bool quit;

	SaveGame save_game;

	// Functions
	void initBackground(sf::RenderWindow* window, AssetsManager& am);
	void initFonts(AssetsManager& am);
	void initButtons(sf::RenderWindow* window);
	void updateButtons();
	void renderButtons(sf::RenderWindow* window);
	void updateMousePositions();

  public:
	LoadGameState(sf::RenderWindow* window, AssetsManager& am, KeyList* supportedKeys);
	~LoadGameState() override;

	// Functions
	void endState();
	void updateInput(const float& dt);
	void update(const float& dt) override;
	void render(sf::RenderWindow* window) override;
	StateAction handleKeys(sf::Keyboard::Key key) override;
	void updateKeybinds(const float& dt) override;
	void quitStateActions() override;
	bool shouldQuit() override;
	Position getCurrentPlayerPosition() override { return {0, 0}; };
	void drawPlayer(sf::RenderWindow* window) override;
	sf::View getView() override { return view; };
	StateAction shouldAct() override;
	void stopMusic() override;
	void resumeMusic() override;
};