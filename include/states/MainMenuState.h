
#pragma once

#include "Button.h"
#include "GameState.h"
#include "SettingsState.h"
#include "definitions.h"

constexpr int MAX_BUTTONS = 4;

class MainMenuState : public State {
  private:
	// Variable
	sf::View view;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	sf::SoundBuffer soundBuffer;
	sf::Sound blipSound;
	sf::Music music;

	Buttons buttons;
	int activeButton;

	sf::Vector2i mousePoseWindow;
	sf::Vector2f mousePosView;

	KeyList* supportedKeys;

	bool quit{};

	// Functions
	void initBackground(sf::RenderWindow* window, AssetsManager& am);
	void initFonts(AssetsManager& am);
	void initButtons(sf::Vector2f pos);

	void updateMousePositions();

  public:
	MainMenuState(sf::RenderWindow* window, AssetsManager& am, KeyList* supportedKeys);

	~MainMenuState() override;

	// Functions
	void endState();

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
	StateAction programAction() override { return StateAction::NONE; };
	sf::View getView() override { return view; };
	void stopMusic() override;
	void resumeMusic() override;
};
