#pragma once

#include <cmath>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Button.h"

constexpr int TILESIZE = 16;

enum class StateAction { NONE, START_SETTING, START_GAME, START_COMBAT, EXIT_COMBAT, EXIT_GAME, EXIT_SETTING, LOAD_GAME, PAUSE_GAME, RESUME_GAME };
enum class KeyAction { UP, DOWN, RIGHT, LEFT, SELECT, BACK, INTERACT, PAUSE };
enum class MovementType { VERTICAL, HORIZONTAL };

using Position = sf::Vector2f;
using Position_i = sf::Vector2i;
using Name = std::string;
using Buttons = std::vector<Button>;
using KeyList = std::unordered_map<KeyAction, sf::Keyboard::Key>;

class Player;
class Enemy;
using Enemies = std::vector<Enemy>;
using Party = std::vector<Player>;
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
	int str = 0;  // Strength
	int dex = 0;  // Dexterity
	int hp = 0;   // Health Points - Life
	int mana = 0; // Magic Energy
	Stats(const int s, const int d, const int h, const int m) : str(s), dex(d), hp(h), mana(m) {}
};

const sf::Color GREY = sf::Color(70, 70, 70, 200);
const sf::Color LIGHTGREY = sf::Color(150, 150, 150, 255);

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


inline const float p2pX(const float perc, const sf::VideoMode& vm)
{
	/*
	 * Converts a percentage value to pixels relative to the current resolution in the x-axis.
	 *
	 * @param		float perc				The percentage value.
	 * @param		sf::VideoMode& vm		The current videomode of the window (resolution).
	 *
	 * @return		float					The calculated pixel value.
	 */

	return std::floor(static_cast<float>(vm.width) * (perc / 100.f));
}

inline const float p2pY(const float perc, const sf::VideoMode& vm)
{
	/*
	 * Converts a percentage value to pixels relative to the current resolution in the y-axis.
	 *
	 * @param		float perc				The percentage value.
	 * @param		sf::VideoMode& vm		The current videomode of the window (resolution).
	 *
	 * @return		float					The calculated pixel value.
	 */

	return std::floor(static_cast<float>(vm.height) * (perc / 100.f));
}

inline const unsigned calcCharSize(const sf::VideoMode& vm, const unsigned modifier = 60)
{
	/*
	 * Calculates the character size for text using the current resolution and a constant.
	 *
	 * @param		sf::VideoMode& vm		The current videomode of the window (resolution).
	 * @param		unsigned modifier		Used to modify the character size in a more custom way.
	 *
	 * @return		unsigned				The calculated character size value.
	 */

	return static_cast<unsigned>((vm.width + vm.height) / modifier);
}
