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

// ---- CHARACTER
constexpr auto CHARACTER = cat(ASSETS, "character/");
constexpr auto IDLE = cat(CHARACTER.c, "Idle.png");
constexpr auto RUN = cat(CHARACTER.c, "Run.png");

// ---- ENEMIES
constexpr auto ENEMIES = cat(ASSETS, "enemies/");
constexpr auto ALIEN = cat(ENEMIES.c, "alien.png");

// ---- TILES
constexpr auto TILES = cat(ASSETS, "tiles/");
constexpr auto MAP_LEVEL1 = cat(TILES.c, "map1.json");
constexpr auto COMBAT_LEVEL1 = cat(TILES.c, "combat.json");
constexpr auto TILESHEET_FLOOR = cat(TILES.c, "TilesetFloor.png");
constexpr auto TILESHEET_NATURE = cat(TILES.c, "TilesetNature.png");
constexpr auto TILESHEET_HOUSES = cat(TILES.c, "TilesetHouse.png");

// ---- CONFIG
constexpr char CONFIG[] = "../config/";
constexpr auto KEYS = cat(CONFIG, "keysbind.ini");
constexpr auto KEYBIND = cat(CONFIG, "gamestate_Keysbind.ini");
constexpr auto MENUKEYBIND = cat(CONFIG, "mainmenustate_keysbind.ini");

// --- FONTS
constexpr auto FONTS = cat(ASSETS, "fonts/");
constexpr auto DOSIS = cat(FONTS.c, "Dosis-Light.ttf");
constexpr auto ALEX = cat(FONTS.c, "AlexandriaFLF.ttf");

// ---- SOUND FX
constexpr auto SOUNDS = cat(ASSETS, "sounds/");
constexpr auto GASP = cat(SOUNDS.c, "gasp.wav");

// ---- MUSIC
constexpr auto MUSIC = cat(ASSETS, "music/");
constexpr auto MENU_MUSIC = cat(MUSIC.c, "main_menu.ogg");
constexpr auto VILLAGE_MUSIC = cat(MUSIC.c, "town.ogg");
constexpr auto COMBAT_MUSIC = cat(MUSIC.c, "combat.ogg");