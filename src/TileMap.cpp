#include "AssetsPaths.h"
#include "TileMap.h"

// Helper function for mapping an iteration counter to a tile from the tile sheet
sf::Vector2i map1Dto2D(int counter) {
	int row = counter / 16;
	int col = counter % 16;
	return {row, col};
}

// Constructor
TileMap::TileMap(AssetsManager& am) {
	gridSize = 16;
	// The window size fits exactly 32 x 24 tiles of grid size 20
	maxSize.x = 100;
	maxSize.y = 100;

    visibleFrom.x = 0;
    visibleTo.y = 0;
    visibleTo.x = 32;
    visibleTo.y = 24;
	nLayers = 2;

	// initialize first rectangle (or tile) position in the upper left corner of the window
	textureRectangle = sf::IntRect(0, 0, gridSize, gridSize);

	// load texture file
	tileTextureSheetLayer1 = am.getMap(TILESHEET_FLOOR.c);
    tileTextureSheetLayer2 = am.getMap(TILESHEET_NATURE.c);

	// load level design
    std::vector<MapBackground*> maps;
    maps.push_back(tileTextureSheetLayer1);
    maps.push_back(tileTextureSheetLayer2);

	LevelDesign layer1 = *am.getLevel(LAYER1.c);
    LevelDesign layer2 = *am.getLevel(LAYER2.c);

    std::vector<LevelDesign> designs;
    designs.push_back(layer1);
    designs.push_back(layer2);

	int counter = 0;

	// set up 3D vector
	tiles.resize(maxSize.x, TileMapRows());
	for(size_t y = 0; y < maxSize.y; y++) {
		for(size_t x = 0; x < maxSize.x; x++) {
			tiles[x].resize(maxSize.y, TileMapColumns());

			for(size_t z = 0; z < nLayers; z++) {
				tiles[x][y].resize(nLayers, TileLayers());

				// enter tiles only if within bounds, else, do nothing
				if(x < maxSize.x && x >= 0 && y < maxSize.y && y >= 0 && z < nLayers && z >= 0) {
					// store tiles in respective vector position
					sf::Vector2i pos = map1Dto2D(designs[z][y][x]);

					// move textureRectangle to specified position in tile sheet to get the correct texture
					textureRectangle.left = (pos.y * gridSize);
					textureRectangle.top = (pos.x * gridSize);

					// create new tile and save at correct position in the 3D array
					tiles[x][y][z].push_back(new Tile(float(x * gridSize), float(y * gridSize), float(gridSize), maps[z], textureRectangle));
                    counter++;
				}
			}
		}
	}
}


TileMap::~TileMap() {
	for(size_t x = 0; x < maxSize.x; x++) {
		for(size_t y = 0; y < maxSize.y; y++) {
			for(size_t z = 0; z < nLayers; z++) {
				delete tiles[x][y][z][0];
			}
		}
	}
}

void TileMap::update(sf::Vector2f playerPos) {
    // update depending on character position
    if (playerPos.x/gridSize >= float(visibleTo.x))
    {
        visibleFrom.x++;
        visibleTo.x++;
    }
    if (playerPos.y/gridSize  >= float(visibleTo.y)) {
        visibleFrom.y++;
        visibleTo.y++;
    }
    if (playerPos.x/gridSize  <= float(visibleFrom.x)) {
        visibleFrom.x--;
        visibleTo.x--;
    }
    if (playerPos.y/gridSize  <= float(visibleFrom.y)) {
        visibleFrom.y--;
        visibleTo.y--;
    }
}

void TileMap::render(sf::RenderTarget& target) {
	for(int x = 0; x < maxSize.x; x++) {
		for(int y = 0; y < maxSize.y; y++) {
			for(int z = 0; z < nLayers; z++) {
				tiles[x][y][z][0]->render(target);
			}
		}
	}
}
