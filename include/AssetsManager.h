#pragma once

#include <unordered_map>
#include <string>

#include <SFML/Graphics.hpp>

#include "definitions.h"

class AssetsManager {
private:
  std::unordered_map<std::string, sf::Texture> textures;
  std::unordered_map<std::string, sf::Font> fonts;
  std::unordered_map<std::string, MapBackground> maps;

public:
  sf::Texture getTexture(const std::string &name);
  sf::Font getFont(const std::string &name);
  MapBackground getMap(const std::string &name);

  void loadTexture(const std::string &path, const std::string &name);
  void loadFont(const std::string &path, const std::string &name);
  void loadMap(const std::string &path, const std::string &name);
};