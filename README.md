# C++ Role Play Game

Oh no! A bunch of aliens has taken over the town! Luckily, you are there to save the old lady that has been abducted and eaten by the aliens. The houses of the villagers are occupied by aliens. If you can defeat all of them with your ninja skills, the old lady will be saved and the town will be in peace again. GO hurry!

## Dependencies:
[SFML](https://www.sfml-dev.org/tutorials/2.5/#getting-started)

## Controls
- A: left
- S: down
- D: right
- W: up
- F: Interact
- I: Inventory
- Esc and Q: Quit application
- P: Pause the game
- Space: continue conversation

## Build process

### On Linux:

Build and run with:
```
cd path/to/game
mkdir build
cd build
cmake ..
make
./rpg
```

### On Windows

```
cd path/to/game
mkdir build
cd build
cmake ..
[open rpg.sln]
[build with MSVC]
cd Release
./rpg.exe
```

## Asset pack

Almost all assets are taken from the "Ninja Adventure" asset pack by pixel-boy: https://pixel-boy.itch.io/ninja-adventure-asset-pack

## Contribution Statement

Facu worked on:
- Animation
- AssetsManager
- AssetsPaths
- A little refactoring in Button
- Combatant
- CombatState
- EnemyManager with Andrea
- Entity
- GameState with Andrea
- Inanimate
- Item Manager
- Part of MainMenu
- Player
- Part of SettingsState
- State with Andrea
- Stats

Andrea worked on:
- Basic Game Framework (game loop, render, update, poll events, states stack), inspired by [1]
- Character movement (Player, with user input, and NPCs)
- HouseManager & Houses
- InteractionManager & DialogueBox
- GameOverState & GameWonState
- GameState with Facu
- EnemyManager with Facu
- State interface
- Music and sound effects
- TileMaps (Creation of maps using [2], implementation of TileMap and Tile classes, incl. collision map, using [3])
- Saving and loading the game (using [4])
- Villagers
- Story progress

Abdul worked on:
- Part of MainMenuState
- PauseState
- SettingsState (change resolution)

 ### References:

- [1] Youtube playlist by Suraj Sharma: https://www.youtube.com/playlist?list=PL6xSOsbVA1ebkU66okpi-KViAO8_9DJKg
- [2] Tiled: https://www.mapeditor.org/ (Map editor)
- [3] Tileson: https://github.com/SSBMTonberry/tileson (JSON tile map parser)
- [4] Cereal: https://github.com/USCiLab/cereal (Serialization library)

