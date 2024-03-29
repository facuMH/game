#pragma once

#include <cmath>
#include <list>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cereal/cereal.hpp>

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
	EXIT_HOUSE,
	LOAD_GAME,
	PAUSE_GAME,
	RESUME_GAME,
	PICK_ITEM,
	GAME_OVER,
	OPEN_INVENTORY,
	CLOSE_INVENTORY,
	ADD_ITEM,
	GAME_WON
};
enum class KeyAction { UP, DOWN, RIGHT, LEFT, SELECT, BACK, INTERACT, NONE, PAUSE };
enum class MovementType { VERTICAL, HORIZONTAL, STILL };

using Position = sf::Vector2f;
using Position_i = sf::Vector2i;

using Name = std::string;
using Buttons = std::vector<Button>;
using KeyList = std::unordered_map<KeyAction, sf::Keyboard::Key>;
using DoorNumber = int;

class Enemy;
class Villager;
using Villagers = std::vector<Villager>;
using CombatText = std::unordered_map<Name, Button>;
class Object;
using Inventory = std::vector<Object*>;

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

class House {
  public:
	JSONFilePath houseDesignPath;
};

struct Stats {
	int str = 0;     // Strength
	int dex = 0;     // Dexterity
	int hp = 0;      // Health Points - Life
	int mana = 0;    // Magic Energy
	int armor = 0;   // how hard it is to hit the character
	int baseAtk = 0; // how good is this character at hitting things
	Stats(const int s, const int d, const int h, const int m, const int a, const int b)
	    : str(s), dex(d), hp(h), mana(m), armor(a), baseAtk(b) {}
	Stats() : str(0), dex(0), hp(0), mana(0), armor(0), baseAtk(0) {}

	void operator+=(const Stats _s) {
		str += _s.str;
		dex += _s.dex;
		hp += _s.hp;
		mana += _s.mana;
		armor += _s.armor;
		baseAtk += _s.baseAtk;
	}

	Stats operator+(const Stats _s) {
		str += _s.str;
		dex += _s.dex;
		hp += _s.hp;
		mana += _s.mana;
		armor += _s.armor;
		baseAtk += _s.baseAtk;
		return *this;
	}

	template <class Archive>
	void serialize(Archive& archive) {
		archive(CEREAL_NVP(str),
		    CEREAL_NVP(dex),
		    CEREAL_NVP(hp),
		    CEREAL_NVP(mana),
		    CEREAL_NVP(armor),
		    CEREAL_NVP(baseAtk));
	}
};

const Stats levelUpStatsIncrement{3, 3, 10, 10, 5, 5};

const sf::Color GREY = sf::Color(70, 70, 70, 200);
const sf::Color LIGHTGREY = sf::Color(150, 150, 150, 255);
const sf::Color DARKBLUE = sf::Color(0, 0, 255, 255);
const sf::Color TRANSPARENT_BLACK = sf::Color(0, 0, 0, 180);

const Position COMBAT_FIRST_PLAYER_POSITION{150.f, 150.f};
const Position COMBAT_FIRST_ENEMY_POSITION{500.f, 150.f};


namespace std {
template <>
struct hash<KeyAction> {
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
	return std::fabs(one.x - other.x) <= epsilon && std::fabs(one.y - other.y) <= epsilon;
}

// DEFINITIONS/CONSTANTS FOR DIALOGUE BOX
const int Y_OFFSET_DIALOGUE_POSITION = 150;
const Position TEXT_POS_OFFSET = {55, 20};
const int DISTANCE_TEXT_TO_END_OF_BOX = 25;
const int MAX_TEXT_LINES = 2;
const float TIME_UNTIL_NEXT_CHAR = 0.05; // after this time the next character of the text is drawn
const Position CHARACTER_NAME_OFFSET = {8, 0};
const Position ARROW_POS_OFFSET = {20, 20};
const Position FACE_OFFSET = {6, 15};