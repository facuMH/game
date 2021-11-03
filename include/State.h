#ifndef RPG_STATE_H
#define RPG_STATE_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <fstream>
#include <sstream>
#include <stack>
#include <vector>

class State {
private:
  std::vector<sf::Texture> textures;
  sf::RenderWindow *window;

public:
  // Constructor
  explicit State(sf::RenderWindow *window);
  // Destructor
  virtual ~State();

  // virtual ==> these MUST be defined in child class
  virtual void update(const float &dt) = 0;
  virtual void render(sf::RenderTarget *target = nullptr) = 0;

  virtual void endState() = 0;
};

#endif // RPG_STATE_H
