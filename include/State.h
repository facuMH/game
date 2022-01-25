#pragma once

#include <fstream>
#include <sstream>
#include <stack>
#include <vector>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "AssetsManager.h"
#include "definitions.h"

/**
 * Parent class for States: GameState, ...
 */
class State {
  private:
	sf::RenderWindow* window;
	bool isQuitting = false;

  public:
	// Constructor
	explicit State(sf::RenderWindow* window);
	// Destructor
	virtual ~State();

	// virtual ==> application on run-time object of child class (i.e. GameState)
	// these MUST be defined in child class
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderWindow* window) = 0;
	virtual void updateKeybinds(const float& dt) = 0;
	virtual bool shouldQuit() = 0;
	const bool& isQuit() const { return isQuitting; }
	virtual void quitStateActions() = 0;
	virtual StateAction handleKeys(sf::Keyboard::Key key) = 0;
	virtual StateAction shouldAct() = 0;
	virtual void drawPlayer(sf::RenderWindow* window) = 0;
	virtual sf::View getView() = 0;
	Position_i getMouse() const { return sf::Mouse::getPosition(*window); }
	Position getPos(Position_i objectPosition) const { return window->mapPixelToCoords(objectPosition); }
	virtual void stopMusic() = 0;
	virtual void resumeMusic() = 0;
	sf::RenderWindow* getWindow() { return window; }
};