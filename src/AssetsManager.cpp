#include <iostream>

#include <SFML/Graphics.hpp>

#include "AssetsManager.h"

void AssetsManager::loadTexture(const std::string &path, const std::string &name) {
  sf::Texture newTexture;
  if (newTexture.loadFromFile(path)) {
    textures.emplace(name, newTexture);
  } else {
    std::cout << " RGP ERROR: no Texture found at " << path << "\n";
  }
}

void AssetsManager::loadFont(const std::string &path, const std::string &name) {
  sf::Font newFont;
  if (newFont.loadFromFile(path)) {
    fonts.emplace(name, newFont);
  } else {
    std::cout << " RGP ERROR: no Font found at " << path << "\n";
  }
}

void AssetsManager::loadMap(const std::string& path, const std::string& name) {
  MapBackground newMap;
  if (newMap.loadFromFile(path)) {
    maps.emplace(name, newMap);
  } else {
    std::cout << " RGP ERROR: no Map found at " << path << "\n";
  }
}

sf::Texture AssetsManager::getTexture(const std::string &name) {
  return textures.at(name);
}
sf::Font AssetsManager::getFont(const std::string& name) {
  return fonts.at(name);
}
MapBackground AssetsManager::getMap(const std::string &name) {
  return maps.at(name);

}