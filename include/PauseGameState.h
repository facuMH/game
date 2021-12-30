#pragma once

#include <vector>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "AssetsManager.h"
#include "State.h"

class PauseGameState : public State {
  private:
	sf::View view;
	sf::RectangleShape background;
	sf::Font font;
	sf::Text text;

	KeyList* supportedKeys;

	bool quit{};

	// Functions
	void initBackground(sf::RenderWindow* window);
	void initFonts(AssetsManager& am);
	void initText(sf::RenderWindow* window);
  public:
	PauseGameState(sf::RenderWindow* window, AssetsManager& am, KeyList* supportedKeys);
	virtual ~PauseGameState() override;

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