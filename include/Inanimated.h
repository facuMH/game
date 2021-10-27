#pragma once

#include "Entity.h"

class Object : Entity {
	bool can_pick_up;
	int quantity;
public:
	Object() : can_pick_up(true), quantity(0) {};
};

class Map_section : Entity {
	
};