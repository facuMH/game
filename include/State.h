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

	bool isQuitting{};

  public:
	// Constructor
	State(sf::RenderWindow* window);
	// Destructor
	virtual ~State();

	// virtual ==> application on run-time object of child class (i.e. GameState)
	// these MUST be defined in child class
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target) = 0;
	virtual void updateKeybinds(const float& dt) = 0;
	virtual void checkIfQuitting();
	const bool& isQuit() const;
	virtual void quitStateActions() = 0;
	virtual void handleKeys(sf::Keyboard::Key key) = 0;
	Position_i getMouse() const { return sf::Mouse::getPosition(*window); }
	Position getPos(Position_i objectPosition) const { return window->mapPixelToCoords(objectPosition); }
};
