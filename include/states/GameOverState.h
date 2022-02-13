#pragma once

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "AssetsManager.h"
#include "State.h"

class GameOverState : public State {
  private:
	sf::RectangleShape background;
	sf::Font font;
	sf::Text text;

	KeyList* supportedKeys;

	int activeButton;
	Buttons buttons;

	Position_i mousePoseWindow;
	Position mousePosView;

	// Functions
	void initBackground(sf::RenderWindow* window, AssetsManager& am);
	void initFonts(AssetsManager& am);
	void initText(sf::RenderWindow* window);
	void initButtons(sf::RenderWindow* window);
	void updateButtons();
	void renderButtons(sf::RenderWindow* window);
	void updateMousePositions();

  public:
	GameOverState(sf::RenderWindow* window, AssetsManager& am, KeyList* supportedKeys);
	~GameOverState() override;

	// Functions
	void updateInput(const float& dt);
	void update(const float& dt) override;
	void render(sf::RenderWindow* window) override;
	StateAction handleKeys(sf::Keyboard::Key key) override;
	void updateKeybinds(const float& dt) override;
	void quitStateActions() override;
	bool shouldQuit() override;
	void drawPlayer(sf::RenderWindow* window) override;
	sf::View getView() override { return view; };
	StateAction shouldAct() override;
	void stopMusic() override;
	void resumeMusic() override;
	void playErrorSound();
};