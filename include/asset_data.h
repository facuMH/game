#pragma once

#include "definitions.h"

struct EnemyData {
	Name name;
	std::string texturePath;
	Position position;
};

const EnemyData MOLE_DATA = {"Mole", MOLE.c, {30, 30}};
const EnemyData REPTILE_DATA = {"Reptile", REPTILE.c, {30, 30}};
const EnemyData LIZARD_DATA = {"Lizard", LIZARD.c, {30, 30}};
const EnemyData SKULL_DATA = {"Skull", SKULL.c, {30, 30}};
const EnemyData BAMBOO_DATA = {"Bamboo", BAMBOO.c, {30, 30}};
const EnemyData AXOLOTL_DATA = {"Axolotl", AXOLOTL.c, {30, 30}};

const std::vector<EnemyData> ENEMYDATA {MOLE_DATA, REPTILE_DATA, LIZARD_DATA, SKULL_DATA, BAMBOO_DATA, AXOLOTL_DATA};

struct HouseData {
	DoorNumber doorNumber;
	JSONFilePath mapDesignPath;
	Position doorPosition;
};

const HouseData HOUSE1_DATA = {1, HOUSE1.c, {60, 60}};
const HouseData HOUSE2_DATA = {2, HOUSE2.c, {45, 100}};
const HouseData HOUSE3_DATA = {3, HOUSE3.c, {60, 100}};
const HouseData HOUSE4_DATA = {4, HOUSE4.c, {80, 100}};
const HouseData HOUSE5_DATA = {5, HOUSE5.c, {40, 30}};
const HouseData HOUSE6_DATA = {6, HOUSE6.c, {30, 30}};

const std::vector<HouseData> HOUSEDATA {HOUSE1_DATA, HOUSE2_DATA, HOUSE3_DATA, HOUSE4_DATA, HOUSE5_DATA, HOUSE6_DATA};