#pragma once

#include "AssetsPaths.h"
#include "definitions.h"

struct EnemyData {
	Name name;
	std::string texturePath;
	Position position;
	int experience;
	std::string bodyPart;
};

const EnemyData MOLE_DATA = {"Mole", MOLE.c, {30, 30}, 50, "Head"};
const EnemyData REPTILE_DATA = {"Reptile", REPTILE.c, {30, 30}, 50, "Right Arm"};
const EnemyData LIZARD_DATA = {"Lizard", LIZARD.c, {30, 30}, 50, "Left Arm"};
const EnemyData SKULL_DATA = {"Skull", SKULL.c, {30, 30}, 50, "Torso"};
const EnemyData BAMBOO_DATA = {"Bamboo", BAMBOO.c, {30, 30}, 50, "Left Foot"};
const EnemyData AXOLOTL_DATA = {"Axolotl", AXOLOTL.c, {30, 30}, 50, "Teeth"};
const EnemyData GRANDPA_DATA = {"Evil Grandpa", OLD_MAN_WALK.c, {30, 30}, 100};

const std::vector<EnemyData> ENEMYDATA{
    MOLE_DATA, REPTILE_DATA, LIZARD_DATA, SKULL_DATA, BAMBOO_DATA, AXOLOTL_DATA, GRANDPA_DATA};

struct HouseData {
	DoorNumber doorNumber;
	JSONFilePath mapDesignPath;
	Position doorPosition;
	Name itemName;
	Position itemPosition;
	bool isWeapon;
};

const HouseData HOUSE1_DATA = {1, HOUSE1.c, {60, 60}, "Club", {80, 80}, true};
const HouseData HOUSE2_DATA = {2, HOUSE2.c, {45, 100}, "Fork", {35, 90}, true};
const HouseData HOUSE3_DATA = {3, HOUSE3.c, {60, 100}, "Sword", {50, 90}, true};
const HouseData HOUSE4_DATA = {4, HOUSE4.c, {80, 100}, "Wand", {70, 90}, true};
const HouseData HOUSE5_DATA = {5, HOUSE5.c, {40, 95}, "LifePot", {30, 20}, false};
const HouseData HOUSE6_DATA = {6, HOUSE6.c, {30, 75}, "MediPack", {20, 20}, false};
const HouseData FINAL_HOUSE_DATA = {7, FINAL_HOUSE.c, {65, 95}, "", {20, 20}, false};

const std::vector<HouseData> HOUSEDATA{
    HOUSE1_DATA, HOUSE2_DATA, HOUSE3_DATA, HOUSE4_DATA, HOUSE5_DATA, HOUSE6_DATA, FINAL_HOUSE_DATA};

const std::unordered_map<Name, std::string> itemsPaths{
    {"Club", CLUB.c},
    {"Fork", FORK.c},
    {"Sword", SWORD.c},
    {"Wand", WAND.c},
    {"LifePot", LIFEPOT.c},
    {"MediPack", MEDIPACK.c},
};