#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <unordered_map>

#include "Button.h"

constexpr int TILESIZE = 16;

enum class StateAction {
	NONE,
	START_SETTING,
	START_GAME,
	START_COMBAT,
	START_HOUSE,
	EXIT_COMBAT,
	EXIT_GAME,
	EXIT_SETTING,
	EXIT_HOUSE
};
enum class KeyAction { UP, DOWN, RIGHT, LEFT, SELECT, BACK, INTERACT };
enum class MovementType { VERTICAL, HORIZONTAL };

using Position = sf::Vector2f;
using Position_i = sf::Vector2i;
using Name = std::string;
using Buttons = std::vector<Button>;
using KeyList = std::unordered_map<KeyAction, sf::Keyboard::Key>;
using DoorNumber = int;

class Enemy;
using Enemies = std::vector<Enemy>;
class Villager;
using Villagers = std::vector<Villager>;
using CombatText = std::unordered_map<Name, Button>;

class MapBackground : public sf::Texture {};
class Texture : public sf::Texture {};

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

struct Stats {
	int str = 0;     // Strength
	int dex = 0;     // Dexterity
	int hp = 0;      // Health Points - Life
	int mana = 0;    // Magic Energy
	int armor = 0;   // how hard it is to hit the character
	int baseAtk = 0; // how good is this character at hitting thigs
	Stats(const int s, const int d, const int h, const int m, const int a, const int b)
	    : str(s), dex(d), hp(h), mana(m), armor(a), baseAtk(b) {}
	Stats() : str(0), dex(0), hp(0), mana(0), armor(0), baseAtk(0) {}
};

const sf::Color GREY = sf::Color(70, 70, 70, 200);
const sf::Color LIGHTGREY = sf::Color(150, 150, 150, 255);
const sf::Color DARKBLUE = sf::Color(0, 0, 255, 255);

const Position COMBAT_FIRST_PLAYER_POSITION{150.f, 150.f};
const Position COMBAT_FIRST_ENEMY_POSITION{500.f, 150.f};


namespace std {
template <> struct hash<KeyAction> {
	size_t operator()(const KeyAction& k) const { return hash<int>()(static_cast<int>(k)); }
};
}; // namespace std

inline Position_i getDesktopCenter(const sf::RenderWindow& window) {
	auto desktop = sf::VideoMode::getDesktopMode();
	auto size = window.getSize();
	auto x = static_cast<int>(desktop.width / 2 - size.x / 2);
	auto y = static_cast<int>(desktop.height / 2 - size.y / 2);
	return {x, y};
}

inline Position getWindowCenter(const sf::RenderWindow& window) {
	auto center = window.getDefaultView().getSize();
	auto x = center.x / 2.f;
	auto y = center.y / 2.f;
	return {x, y};
}

inline bool positionsInRange(Position one, Position other, float epsilon) {
	return std::fabs(one.x - other.x) < epsilon && std::fabs(one.y - other.y) < epsilon;
}

// DEFINITIONS/CONSTANTS FOR DIALOGUE BOX
const int POSITION_OFFSET = 10;
const Position TEXT_POS_OFFSET = {55, 20};
const int MAX_TEXT_LINES = 2;
const float TIME_UNTIL_NEXT_CHAR = 0.05; // after this time the next character of the textToDraw is drawn
const Position CHARACTER_NAME_OFFSET = {10, -2};
const Position ARROW_POS_OFFSET = {10, 10};
const Position FACE_OFFSET = {6, 15};