#pragma once

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

class AssetsManager {
private:
  std::map<std::string, sf::Texture> textures;
  std::map<std::string, sf::Fonts> fonts;
};