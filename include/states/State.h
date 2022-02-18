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
#include "managers/AssetsManager.h"

/**
 * Parent class for all states
 */
class State {
  private:
	sf::RenderWindow* window;
	bool isQuitting = false;

  public:
	sf::View view;
	std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
	std::unordered_map<std::string, sf::Sound> sounds;
	sf::Music music;

	// Constructor
	explicit State(sf::RenderWindow* window);
	// Destructor
	virtual ~State();

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderWindow* window) = 0;
	virtual void updateKeybinds(const float& dt) = 0;
	virtual bool shouldQuit() = 0;
	virtual void quitStateActions() = 0;
	virtual StateAction handleKeys(sf::Keyboard::Key key) = 0;
	virtual StateAction shouldAct() = 0;
	virtual void drawPlayer(sf::RenderWindow* window) = 0;
	virtual StateAction programAction() = 0;

	virtual sf::View getView() { return view; };
	Position_i getMouse() const { return sf::Mouse::getPosition(*window); }
	Position getPos(Position_i objectPosition) const { return window->mapPixelToCoords(objectPosition); }
	virtual void stopMusic();
	virtual void resumeMusic();
	sf::RenderWindow* getWindow() { return window; }
	const bool& isQuit() const { return isQuitting; }
};