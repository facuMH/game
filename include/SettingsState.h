#pragma once
#include "AssetsManager.h"
#include "Gui.h"
#include "State.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <map>
#include <vector>

class SettingsState : public State {
  private:
	// Variable
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;
	sf::Music music;

	Buttons buttons;
	int activeButton;


	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePoseWindow;
	sf::Vector2f mousePosView;

	KeyList* supportedKeys;

	bool quit{};

	// Functions
	void initBackground(sf::RenderWindow* window, AssetsManager& am);
	void initFonts(AssetsManager& am);
	void updateGui();
	// void initGui();

	void initVariables();

	sf::Text optionsText;
	void initText();

	std::vector<sf::VideoMode> modes;

	void updateMousePositions();

  public:
	SettingsState(sf::RenderWindow* window, AssetsManager& am, KeyList* supportedKeys);

	virtual ~SettingsState() override;

	std::map<std::string, gui::DropDownList*> dropdownList;


	// Accessors

	// Functions

	void endState();

	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void renderGui(sf::RenderTarget* target);

	void update(const float& dt) override;
	void render(sf::RenderTarget* target) override;
	StateAction handleKeys(sf::Keyboard::Key key, sf::View* view) override;
	void updateKeybinds(const float& dt) override;
	void quitStateActions() override;
	bool shouldQuit() override;
	void drawPlayer(sf::RenderWindow* window) override{};
	StateAction shouldAct() override;
	void stopMusic() override;
	void resumeMusic() override;
	void initGui();
};