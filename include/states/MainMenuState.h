
#pragma once

#include "Button.h"
#include "GameState.h"
#include "MakesErrorSound.h"
#include "SettingsState.h"
#include "definitions.h"

constexpr int MAX_BUTTONS = 4;

/// State which contains the Main Menu with START, LOAD, SETTINGS and QUIT buttons
class MainMenuState : public MakesErrorSound {
  private:
	// Variable
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	Buttons buttons;
	int activeButton;

	sf::Vector2i mousePoseWindow;
	sf::Vector2f mousePosView;

	KeyList* supportedKeys;

	// Functions
	void initBackground(sf::RenderWindow* window, AssetsManager& am);
	void initFonts(AssetsManager& am);
	void initButtons(const sf::Vector2f& pos);

	void updateMousePositions();

  public:
	MainMenuState(sf::RenderWindow* window, AssetsManager& am, KeyList* supportedKeys);

	~MainMenuState() override;

	// Functions
	void updateInput(const float& dt);
	void updateButtons();
	void renderButtons(sf::RenderWindow* window);

	void update(const float& dt) override;
	void render(sf::RenderWindow* window) override;
	StateAction handleKeys(sf::Keyboard::Key key) override;
	void updateKeybinds(const float& dt) override;
	void quitStateActions() override;
	bool shouldQuit() override;
	void drawPlayer(sf::RenderWindow* window) override{};
	StateAction shouldAct() override;
	void playErrorSound() override;
	StateAction programAction() override { return StateAction::NONE; };
};
