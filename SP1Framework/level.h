#pragma once

/* Made by: Kendrick */

#ifndef LEVELHEAD
#define LEVELHEAD

#include "definitions.h"
#include "fileio.h"
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <memory>

struct SMiniMap
{
	char (*level)[(ROOM_X + 2) * GRID_X + 2][(ROOM_Y + 2) * GRID_Y + 2]; // Get access to the actual level
	bool enteredRoom[GRID_X * GRID_Y]; // Storage for whether the player has entered a certain room
	char map[1 + (GRID_X << 1)][1 + (GRID_Y << 1)]; // Minimap buffer
	COORD playerEndRoom; // Room coordinates of the end room

	void refresh(COORD playerLocation); // Refresh the minimap
	bool hasDoor(int roomIndex, int direction); // Check if specified direction has a door within the specified room
	bool hasExplored(int roomIndex, int direction); // Check if the next room over has been explored
	SMiniMap(char (*level)[(ROOM_X + 2) * GRID_X + 2][(ROOM_Y + 2) * GRID_Y + 2], COORD playerStartRoom, COORD exitRoom); // Constructor
};

struct SLevel
{
	COORD playerStartRoom, exitRoom, itemRoom; // Stored in grid coordinates
	char level[(ROOM_X + 2) * GRID_X + 2][(ROOM_Y + 2) * GRID_Y + 2]; // Includes borders
	short floor; // Floor player is in
	SMiniMap * miniMap; // Hold minimap

	void generateLevel(); // Create a new level
	void createStairs(); // Create stairs for end room of floor 5
	std::vector<COORD> seekToEnd(std::vector<COORD>& returned); // Find a path from playerStartRoom to exitRoom
	void uncoverAll(COORD room, bool * roomsHaveExit); // Create doors to all blocked rooms
	void modifyTile(COORD c, char ch); // Change a tile on the level, using tile coordinates
	char getTile(COORD c); // Get what tile is at the coordinate, using tile coordinates
	COORD * getCoordinatesForDoor(const SHORT& X, const SHORT& Y, const int& direction); // Get console coordinates of a door placement
	~SLevel();
};

COORD fastCoord(int& x, int& y); // Quick function to create a COORD

#endif // !LEVELHEAD
