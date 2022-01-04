#include <string>

// constexpr string concat from https://stackoverflow.com/a/65440575
template <unsigned L> struct String { char c[L]; };
template <unsigned L1, unsigned L2> constexpr auto cat(const char (&s1)[L1], const char (&s2)[L2]) {
	constexpr unsigned L3 = L1 + L2;
	String<L3 + 1> result = {};
	result.c[L3] = '\0';
	char* dst = result.c;
	const char* src = s1;
	for(; *src != '\0'; src++, dst++) {
		*dst = *src;
	}
	src = s2;
	for(; *src != '\0'; src++, dst++) {
		*dst = *src;
	}
	return result;
}
// -------------------------

// ---- ASSETS
constexpr char ASSETS[] = "../assets/";

// ---- MAIN MENU
constexpr auto MAINMENU = cat(ASSETS, "menuBackgrounds/");
constexpr auto BACKGROUND = cat(MAINMENU.c, "Background.jpeg");
constexpr auto SETTING_BACKGROUND = cat(MAINMENU.c, "RPG_projects.jpg");

// ---- CHARACTER
constexpr auto CHARACTER = cat(ASSETS, "characters/");
constexpr auto NINJA = cat(CHARACTER.c, "green_ninja/");
constexpr auto NINJA_WALK = cat(NINJA.c, "Walk.png");
constexpr auto EGG_GIRL = cat(CHARACTER.c, "egg_girl/");
constexpr auto EGG_GIRL_WALK = cat(EGG_GIRL.c, "Walk.png");
constexpr auto OLD_MAN = cat(CHARACTER.c, "old_man/");
constexpr auto OLD_MAN_WALK = cat(OLD_MAN.c, "Walk.png");
constexpr auto PRINCESS = cat(CHARACTER.c, "princess/");
constexpr auto PRINCESS_WALK = cat(PRINCESS.c, "Walk.png");


// ---- ENEMIES
constexpr auto ENEMIES = cat(ASSETS, "enemies/");
constexpr auto ALIEN = cat(ENEMIES.c, "alien.png");
constexpr auto MOLE = cat(ENEMIES.c, "Mole.png");
constexpr auto REPTILE = cat(ENEMIES.c, "Reptile.png");
constexpr auto SKULL = cat(ENEMIES.c, "Skull.png");
constexpr auto LIZARD = cat(ENEMIES.c, "Lizard.png");
constexpr auto AXOLOTL = cat(ENEMIES.c, "Axolotl.png");
constexpr auto BAMBOO = cat(ENEMIES.c, "Bamboo.png");



// ---- TILES
constexpr auto TILES = cat(ASSETS, "tiles/");
constexpr auto MAP_LEVEL1 = cat(TILES.c, "map1.json");
constexpr auto COMBAT_LEVEL1 = cat(TILES.c, "combatArena.json");
constexpr auto HOUSE1 = cat(TILES.c, "house1.json");
constexpr auto HOUSE2 = cat(TILES.c, "house2.json");
constexpr auto HOUSE3 = cat(TILES.c, "house3.json");
constexpr auto HOUSE4 = cat(TILES.c, "house4.json");
constexpr auto HOUSE5 = cat(TILES.c, "house5.json");
constexpr auto HOUSE6 = cat(TILES.c, "house6.json");

constexpr auto TILESHEET_FLOOR = cat(TILES.c, "TilesetFloor.png");
constexpr auto TILESHEET_NATURE = cat(TILES.c, "TilesetNature.png");
constexpr auto TILESHEET_HOUSES = cat(TILES.c, "TilesetHouse.png");
constexpr auto TILESHEET_FURNITURE = cat(TILES.c, "TilesetFurniture.png");
constexpr auto TILESHEET_INTERIOR_FLOOR = cat(TILES.c, "TilesetInteriorFloor.png");


// ---- CONFIG
constexpr char CONFIG[] = "../config/";
constexpr auto KEYS = cat(CONFIG, "keysbind.ini");
constexpr auto KEYBIND = cat(CONFIG, "gamestate_Keysbind.ini");
constexpr auto MENUKEYBIND = cat(CONFIG, "mainmenustate_keysbind.ini");
constexpr auto WINDOW = cat(CONFIG, "window.ini");

// --- FONTS
constexpr auto FONTS = cat(ASSETS, "fonts/");
constexpr auto DOSIS = cat(FONTS.c, "Dosis-Light.ttf");
constexpr auto ALEX = cat(FONTS.c, "AlexandriaFLF.ttf");

// ---- SOUND FX
constexpr auto SOUNDS = cat(ASSETS, "sounds/");
constexpr auto GASP = cat(SOUNDS.c, "gasp.wav");
constexpr auto MENU_BLIP = cat(SOUNDS.c, "menu.wav");

// ---- MUSIC
constexpr auto MUSIC = cat(ASSETS, "music/");
constexpr auto MENU_MUSIC = cat(MUSIC.c, "main_menu.ogg");
constexpr auto VILLAGE_MUSIC = cat(MUSIC.c, "town.ogg");
constexpr auto COMBAT_MUSIC = cat(MUSIC.c, "combat.ogg");
constexpr auto HOUSE_MUSIC = cat(MUSIC.c, "house.ogg");

