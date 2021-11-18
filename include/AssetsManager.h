#pragma once

#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "definitions.h"

class AssetsManager {
  private:
	std::unordered_map<std::string, sf::Texture> textures;
	std::unordered_map<std::string, sf::Font> fonts;
	std::unordered_map<std::string, MapBackground> maps;

	template <typename Asset, std::enable_if_t<std::is_same_v<Asset, sf::Texture>, bool> = true>
	void emplace(Asset& newAsset) {
		textures.emplace(newAsset);
	}

	template <typename Asset, std::enable_if_t<std::is_same_v<Asset, sf::Font>, bool> = true>
	void emplace(Asset& newAsset) {
		fonts.emplace(newAsset);
	}

	template <typename Asset, std::enable_if_t<std::is_same_v<Asset, MapBackground>, bool> = true>
	void emplace(Asset& newAsset) {
		maps.emplace(newAsset);
	}

  public:
	sf::Texture getTexture(const std::string& name) { return maps.at(name); }
	sf::Font getFont(const std::string& name) { return fonts.at(name); }
	MapBackground getMap(const std::string& name) { return textures.at(name); }

	template <typename Asset>
	void loadAsset(const std::string& path, const std::string& name) {
		Asset newAsset;
		if(newAsset.loadFromFile(path)) {
			emplace<Asset>(&newAsset);
		} else {
			std::cout << "RPG ERROR: no " << decltype(Asset) << " found at " << path << "\n";
		}
	}
};