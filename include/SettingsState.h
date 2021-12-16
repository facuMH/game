#pragma once

#include <vector>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "AssetsManager.h"
#include "Gui.h"
#include "State.h"



class SettingsState : public State {
  private:
	sf::View view;
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
	void applyResolution(unsigned int width, unsigned int height); 
	void initFonts(AssetsManager& am);
	void updateGui();
	void initButtons();
	void updateButtons();
	void renderButtons(sf::RenderWindow* window);

	void updateMousePositions();

  public:
	SettingsState(sf::RenderWindow* window, AssetsManager& am, KeyList* supportedKeys);

	virtual ~SettingsState() override;


	// Accessors

	// Functions

	void endState();

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
};
