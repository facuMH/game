#pragma once

#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "Button.h"

using Position = sf::Vector2f;
using Position_i = sf::Vector2i;
using Interval = sf::Vector2f;
using Name = std::string;

class JSONFilePath : public std::string {
  public:
	bool loadFromFile(const std::string& input) {
		append(input);
		return true;
	}
};

class MusicPath : public std::string {
  public:
	bool loadFromFile(const std::string& input) {
		append(input);
		return true;
	}
};

class MapBackground : public sf::Texture {};
class Texture : public sf::Texture {};

using Buttons = std::vector<Button>;

struct Stats {
	int str = 0;  // Strength
	int dex = 0;  // Dexterity
	int hp = 0;   // Health Points - Life
	int mana = 0; // Magic Energy
	Stats(const int s, const int d, const int h, const int m) : str(s), dex(d), hp(h), mana(m) {}
};

const sf::Color GREY = sf::Color(70, 70, 70, 200);
const sf::Color LIGHTGREY = sf::Color(150, 150, 150, 255);
const sf::Color BLACK = sf::Color(0, 0, 0, 255);

enum class StateAction { NONE, START_GAME, START_COMBAT, EXIT_COMBAT, EXIT_GAME };

enum class KeyAction { UP, DOWN, RIGHT, LEFT, SELECT, BACK, INTERACT };

namespace std {
template <> struct hash<KeyAction> {
	size_t operator()(const KeyAction& k) const { return hash<int>()(static_cast<int>(k)); }
};
}; // namespace std

using KeyList = std::unordered_map<KeyAction, sf::Keyboard::Key>;

class Character;
using Enemies = std::vector<Character>;
using Party = std::vector<Character>;
using CombatText = std::unordered_map<Name, Button>;

const Position COMBAT_FIRST_PLAYER_POSITION{150.f, 150.f};
const Position COMBAT_FIRST_ENEMY_POSITION{500.f, 150.f};