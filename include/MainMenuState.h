
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
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;

	Buttons buttons;
	int activeButton;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePoseWindow;
	sf::Vector2f mousePosView;

	KeyList* keybinds;

	bool quit{};

	// Functions
	void initBackground(sf::RenderWindow* window, AssetsManager& am, std::vector<MapBackground*> textureSheets,
	    std::vector<Design*> levelDesigns);
	void initFonts(AssetsManager& am);
	void initButtons();

	void updateMousePositions();

  public:
	MainMenuState(sf::RenderWindow* window, AssetsManager& am, std::vector<MapBackground*> textureSheets,
	    std::vector<Design*> levelDesigns, KeyList* gameSupportedKeys);

	~MainMenuState() override;

	// Functions
	void endState();

	void updateInput(const float& dt);
	void updateButtons();
	void renderButtons(sf::RenderTarget* target);

	void update(const float& dt) override;
	void render(sf::RenderTarget* target) override;
	StateAction handleKeys(sf::Keyboard::Key key, sf::View* view) override;
	void updateKeybinds(const float& dt) override;
	void quitStateActions() override;
	bool shouldQuit() override;
	void drawPlayer(sf::RenderWindow* window) override{};
	StateAction shouldAct() override;
};
