# C++ Role Play Game

## Dependencies:
- SFML (Install using ```sudo apt-get install libsfml-dev```)

## Controls
- A: left
- S: down
- D: right
- W: up
- C: start combat
- X: end combat
- Esc and Q: Quit application
- P: Pause the game

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