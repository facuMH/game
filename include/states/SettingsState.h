#pragma once

#include <vector>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "AssetsManager.h"
#include "Button.h"
#include "State.h"

class SettingsState : public State {
  private:
	sf::RectangleShape background;
	sf::Font font;

	Position_i mousePoseWindow;
	Position mousePosView;

	KeyList* supportedKeys;
	Buttons buttons;

	int activeButton;
	bool quit{};

	// Functions
	void initBackground(AssetsManager& am);
	void applyResolution(const unsigned int width, const unsigned int height);
	void initFonts(AssetsManager& am);
	void updateGui();
	void initButtons(sf::RenderWindow* window);
	void updateButtons();
	void renderButtons(sf::RenderWindow* window);
	void updateMousePositions();

  public:
	SettingsState(sf::RenderWindow* window, AssetsManager& am, KeyList* supportedKeys);
	~SettingsState() override;

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
};