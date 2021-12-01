#pragma once

#include <iostream>
#include <string>
#include <typeinfo>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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


  public:
	Texture* getTexture(const std::string& name) {
		auto found = textures.find(name);
		if(found != textures.end())
			return &found->second;
		else {
			if(loadAsset<Texture>(name)) { return &textures.at(name); }
			std::cout << "RPG ERROR: " << name << " is not a texture\n";
			return nullptr;
		}
	}

	sf::Font* getFont(const std::string& name) {
		auto found = fonts.find(name);
		if(found != fonts.end())
			return &found->second;
		else {
			if(loadAsset<sf::Font>(name)) { return &fonts.at(name); }
			std::cout << "RPG ERROR: " << name << " is not a font\n";
			return nullptr;
		}
	}

	MapBackground* getMap(const std::string& name) {
		auto found = maps.find(name);
		if(found != maps.end())
			return &found->second;
		else {
			if(loadAsset<MapBackground>(name)) { return &maps.at(name); }
			std::cout << "RPG ERROR: " << name << " is not a map\n";
			return nullptr;
		}
	}

	Design* getDesign(const std::string& name) {
		auto found = design.find(name);
		if(found != design.end())
			return &found->second;
		else {
			if(loadAsset<Design>(name)) { return &design.at(name); }
			std::cout << "RPG ERROR: " << name << " is not a design\n";
			return nullptr;
		}
	}

    sf::SoundBuffer getSoundBuffer(const std::string& name) {
        auto found = sounds.find(name);
        if (found != sounds.end())
            return found->second;
        else
        {
            if (loadAsset<sf::SoundBuffer>(name))
            { return sounds.at(name); }
            std::cout << "RPG ERROR: " << name << " is not a sound\n";
            return {};
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