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

#include "definitions.h"

/**
 * Parent class for States: GameState, ...
 */
class State {
  private:
	std::vector<sf::Texture> textures;
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
	virtual void render(sf::RenderTarget* target) = 0;
	virtual void updateKeybinds(const float& dt) = 0;
	virtual bool shouldQuit() = 0;
	const bool& isQuit() const { return isQuitting; }
	virtual void endState() { isQuitting = true; }
	virtual void quitStateActions() = 0;
	virtual StateAction handleKeys(sf::Keyboard::Key key, sf::View* view) = 0;
	virtual StateAction shouldAct() = 0;
	virtual void drawPlayer(sf::RenderWindow* window) = 0;
	Position_i getMouse() const { return sf::Mouse::getPosition(*window); }
	Position getPos(Position_i objectPosition) const { return window->mapPixelToCoords(objectPosition); }
	virtual void stopMusic() = 0;
	virtual void resumeMusic() = 0;
};
