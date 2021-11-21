#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <fstream>
#include <sstream>
#include <stack>
#include <vector>

/**
 * Parent class for States: GameState, ...
 */
class State {
private:
  std::vector<sf::Texture> textures;
  sf::RenderWindow *window;
  bool isQuitting{};

public:
  // Constructor
  explicit State(sf::RenderWindow *window);
  // Destructor
  virtual ~State();

  // virtual ==> application on run-time object of child class (i.e. GameState)
  // these MUST be defined in child class
  virtual void update(const float &dt) = 0;
  virtual void render(sf::RenderTarget *target) = 0;
  virtual void updateKeybinds(const float &dt) = 0;
  virtual bool shouldQuit();
  const bool &isQuit() const;
  virtual void quitStateActions() = 0;
};
