#pragma once

#ifndef LEVELHEAD
#define LEVELHEAD

#include "definitions.h"
#include "fileio.h"
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <fstream>

struct SLevel
{
	COORD playerStartRoom, exitRoom; // Stored in grid coordinates
	char level[(ROOM_X + 2) * GRID_X + 2][(ROOM_Y + 2) * GRID_Y + 2]; // Includes borders
	short floor;
	std::vector<std::string> roomSelections;

	void generateLevel(); // Create a new level
	std::vector<COORD> seekToEnd(std::vector<COORD>& returned); // Find a path from playerStartRoom to exitRoom
	void uncoverAll(COORD room, bool * roomsHaveExit); // Create doors to all blocked rooms
	void modifyTile(COORD c, char ch); // Change a tile on the level, using tile coordinates
	char getTile(COORD c); // Get what tile is at the coordinate, using tile coordinates
	COORD * getCoordinatesForDoor(const SHORT& X, const SHORT& Y, const int& direction); // Get console coordinates of a door placement
};

COORD fastCoord(int& x, int& y);

#endif // !LEVELHEAD
