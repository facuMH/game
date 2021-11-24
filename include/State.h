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


protected:
  std::vector<sf::Texture> textures;
  sf::RenderWindow *window;

  std::map<std::string, int>* supportedKeys;
  std::map<std::string, int> keybinds;
  std::stack<State*>* states;
  bool quit;

  sf::Vector2i mousePosScreen;
  sf::Vector2i mousePoseWindow;
  sf::Vector2f mousePosView;

  bool isQuitting{};

public:
  // Constructor
   State(sf::RenderWindow *window, std::map<std::string, int>* supportesKeys, std::stack<State*>* states);
  // Destructor
  virtual ~State();

  // virtual ==> application on run-time object of child class (i.e. GameState)
  // these MUST be defined in child class
  virtual void update(const float &dt) = 0;
  virtual void render(sf::RenderTarget *target) = 0;
  virtual void updateKeybinds(const float &dt) = 0;
  virtual void checkIfQuitting();
  const bool &isQuit() const;
  virtual void quitStateActions() = 0;


  virtual void initKeybinds() = 0;	//Each state is gona have to define keybind
  virtual void updateMousePositions();
};
