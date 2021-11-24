#pragma once

#include <iostream>
#include <string>
#include <typeinfo>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "definitions.h"

class AssetsManager {
  private:
	std::unordered_map<std::string, Texture> textures;
	std::unordered_map<std::string, sf::Font> fonts;
	std::unordered_map<std::string, MapBackground> maps;
	std::unordered_map<std::string, LevelDesign> levels;

	void emplace(const std::string& name, const Texture& newAsset) { textures.emplace(name, newAsset); }
	void emplace(const std::string& name, const sf::Font& newAsset) { fonts.emplace(name, newAsset); }
	void emplace(const std::string& name, const MapBackground& newAsset) { maps.emplace(name, newAsset); }
	void emplace(const std::string& name, const LevelDesign& newAsset) { levels.emplace(name, newAsset); }

  public:
	Texture* getTexture(const std::string& name) {
		auto found = textures.find(name);
		if(found != textures.end())
			return &found->second;
		else {
			if(loadAsset<Texture>(name)) { return &textures.at(name); }
			std::cout << "RPG ERROR: " << name << " is not a a texture\n";
			return nullptr;
		}
	}

	sf::Font* getFont(const std::string& name) {
		auto found = fonts.find(name);
		if(found != fonts.end())
			return &found->second;
		else {
			if(loadAsset<sf::Font>(name)) { return &fonts.at(name); }
			std::cout << "RPG ERROR: " << name << " is not a a texture\n";
			return nullptr;
		}
	}

	MapBackground* getMap(const std::string& name) {
		auto found = maps.find(name);
		if(found != maps.end())
			return &found->second;
		else {
			if(loadAsset<MapBackground>(name)) { return &maps.at(name); }
			std::cout << "RPG ERROR: " << name << " is not a a texture\n";
			return nullptr;
		}
	}

	LevelDesign* getLayer(const std::string& name) {
		auto found = levels.find(name);
		if(found != levels.end())
			return &found->second;
		else {
			if(loadAsset<LevelDesign>(name)) { return &levels.at(name); }
			std::cout << "RPG ERROR: " << name << " is not a a texture\n";
			return nullptr;
		}
	}

	template <typename Asset>
	bool loadAsset(const std::string& path) {
		Asset newAsset;
		if(newAsset.loadFromFile(path)) {
			emplace(path, newAsset);
		} else {
			std::cout << "RPG ERROR: no " << typeid(decltype(newAsset)).name() << " found at " << path << "\n";
			return false;
		}
		return true;
	}
};