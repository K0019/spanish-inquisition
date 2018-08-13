#pragma once

#ifndef LEVELHEAD
#define LEVELHEAD

#include "entity.h"
#include <algorithm>
#include <fstream>

struct SLevel
{
	COORD playerStartRoom, exitRoom; // Stored in grid coordinates
	SAllEntities g_sEntities; // Hold all entities in the level
	std::string level[GRID_X + (ROOM_X + 1) * GRID_X + 2]; // Includes borders
	int floor;

	void generateLevel(); // Create a new level
	std::vector<COORD> seekToEnd(std::vector<COORD>& returned); // Find a path from playerStartRoom to exitRoom
	void uncoverAll(COORD room, bool * roomsHaveExit); // Create doors to all blocked rooms
	void modifyTile(COORD c, std::string ch); // Change a tile on the level, using tile coordinates
	char getTile(COORD c); // Get what tile is at the coordinate, using tile coordinates
	COORD * getCoordinatesForDoor(const SHORT& X, const SHORT& Y, const int& direction); // Get console coordinates of a door placement
};


#endif // !LEVELHEAD
