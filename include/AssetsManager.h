#pragma once

#include <iostream>
#include <string>
#include <typeinfo>
#include <unordered_map>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "definitions.h"

class AssetsManager {
  private:
	std::unordered_map<std::string, Texture> textures;
	std::unordered_map<std::string, sf::Font> fonts;
	std::unordered_map<std::string, MapBackground> maps;
	std::unordered_map<std::string, Design> design;
	std::unordered_map<std::string, sf::SoundBuffer> sounds;

	void emplace(const std::string& name, const Texture& newAsset) { textures.emplace(name, newAsset); }
	void emplace(const std::string& name, const sf::Font& newAsset) { fonts.emplace(name, newAsset); }
	void emplace(const std::string& name, const MapBackground& newAsset) { maps.emplace(name, newAsset); }
	void emplace(const std::string& name, const Design& newAsset) { design.emplace(name, newAsset); }
	void emplace(const std::string& name, const sf::SoundBuffer& newAsset) { sounds.emplace(name, newAsset); }

	template <typename U, typename T = U::mapped_type>
	T* getAsset(const std::string& name, U map) {
		auto found = map.find(name);
		if(found != map.end())
			return &found->second;
		else {
			if(loadAsset<T>(name)) { return &map.at(name); }
			std::cout << "RPG ERROR: " << name << " is not a texture\n";
			return nullptr;
		}
	}

  public:
	Texture* getTexture(const std::string& name) { return getAsset(name, textures); }
	sf::Font* getFont(const std::string& name) { return getAsset(name, fonts); }
	MapBackground* getMap(const std::string& name) { return getAsset(name, maps); }
	Design* getDesign(const std::string& name) { return getAsset(name, design); }
	sf::SoundBuffer getSoundBuffer(const std::string& name) { return *getAsset(name, sounds); }

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