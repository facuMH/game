#pragma once

#include <iostream>
#include <string>
#include <typeinfo>
#include <unordered_map>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "definitions.h"

template <typename T>
concept Loadable = requires(T a) {
	a.loadFromFile(std::declval<std::string>());
};

class AssetsManager {
  private:
	std::unordered_map<std::string, Texture> textures;
	std::unordered_map<std::string, sf::Font> fonts;
	std::unordered_map<std::string, MapBackground> maps;
	std::unordered_map<std::string, sf::SoundBuffer> sounds;
	std::unordered_map<std::string, JSONFilePath> mapDesigns;
	std::unordered_map<std::string, MusicPath> musicPaths;

	void emplace(const std::string& name, const Texture& newAsset) { textures.emplace(name, newAsset); }
	void emplace(const std::string& name, const sf::Font& newAsset) { fonts.emplace(name, newAsset); }
	void emplace(const std::string& name, const MapBackground& newAsset) { maps.emplace(name, newAsset); }
	void emplace(const std::string& name, const sf::SoundBuffer& newAsset) { sounds.emplace(name, newAsset); }
	void emplace(const std::string& name, const JSONFilePath& newAsset) { mapDesigns.emplace(name, newAsset); }
	void emplace(const std::string& name, const MusicPath& newAsset) { musicPaths.emplace(name, newAsset); }


	template <typename U, typename T = typename U::mapped_type>
	T* getAsset(const std::string& name, U& map) {
		auto found = map.find(name);
		if(found != map.end())
			return &found->second;
		else {
			if(loadAsset<T>(name)) {
				return &map.at(name);
			}
			std::cout << "RPG ERROR: " << name << " is not a texture\n";
			return nullptr;
		}
	}

  public:
	Texture* getTexture(const std::string& name) { return getAsset(name, textures); }
	sf::Font* getFont(const std::string& name) { return getAsset(name, fonts); }
	MapBackground* getMap(const std::string& name) { return getAsset(name, maps); }
	sf::SoundBuffer getSoundBuffer(const std::string& name) { return *getAsset(name, sounds); }
	JSONFilePath* getMapDesign(const std::string& name) { return getAsset(name, mapDesigns); }
	MusicPath* getMusic(const std::string& name) { return getAsset(name, musicPaths); }


	template <typename Asset>
	bool loadAsset(const std::string& path) requires Loadable<Asset> {
		Asset newAsset;
		if(newAsset.loadFromFile(path)) {
			emplace(path, newAsset);
			return true;
		} else {
			std::cout << "RPG ERROR: Error loading file " << path << ".\n";
		}
		return false;
	}
};