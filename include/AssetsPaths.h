#include <string>


// consteexpr string concat from https://stackoverflow.com/a/65440575
template <unsigned L>
struct String {
	char c[L];
};
template <unsigned L1, unsigned L2>
constexpr auto cat(const char (&s1)[L1], const char (&s2)[L2]) {
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


// ---- CHARACTER
constexpr auto CHARACTER = cat(ASSETS, "character/");
constexpr auto IDLE = cat(CHARACTER.c, "Idle.png");
constexpr auto RUN = cat(CHARACTER.c, "Run.png");

// ---- TILES
constexpr auto TILES = cat(ASSETS, "tiles/");
constexpr auto TILESHEET = cat(TILES.c, "tilesheet.png");

// ---- CONFIG
constexpr char CONFIG[] = "../config/";
constexpr auto LEVEL1 = cat(CONFIG, "level1.txt");