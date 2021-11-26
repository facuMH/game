
#pragma once

#include "Button.h"
#include "GameState.h"
#include "definitions.h"

constexpr int MAX_BUTTONS = 3;

class MainMenuState : public State {
  private:
	// Variable
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	Buttons buttons;
	int activeButton;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePoseWindow;
	sf::Vector2f mousePosView;

	KeyList* supportedKeys;
	KeyList keybinds;

	bool quit{};

	// Functions
	void initBackground(sf::RenderWindow* windoww, AssetsManager& am);
	void initFonts(AssetsManager& am);
	void initKeybinds();
	void initButtons();

	void updateMousePositions();

  public:
	MainMenuState(sf::RenderWindow* window, AssetsManager& am, KeyList* supportedKeys);

	virtual ~MainMenuState();

	// Functions
	void endState();

	void updateInput(const float& dt);
	void updateButtons();
	void renderButtons(sf::RenderTarget* target = nullptr);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
	void handleKeys(sf::Keyboard::Key key) override;

	void updateKeybinds(const float& dt) override;
	void quitStateActions() override;
	void checkIfQuitting() override;
	StateAction shouldAct() override;
};
