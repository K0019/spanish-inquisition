#pragma once

#ifndef LEVELHEAD
#define LEVELHEAD

#include "entity.h"
#include <algorithm>

struct SLevel
{
	COORD playerStartRoom, exitRoom;
	SAllEntities g_sEntities;
	std::string level[1 + (ROOM_X + 1) * GRID_X]; // Includes borders

	void generateLevel();
	std::vector<COORD> seekToEnd(std::vector<COORD>& returned);
	void uncoverAll(COORD room, bool * roomsHaveExit);
	void modifyTile(COORD c, std::string ch);
	char getTile(COORD c);
	COORD getCoordinatesForDoor(const SHORT& X, const SHORT& Y, const int& direction);
};


#endif // !LEVELHEAD
