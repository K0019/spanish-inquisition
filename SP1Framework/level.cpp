#include "level.h"
#include "Framework/console.h"

extern Console g_Console;

void SLevel::generateLevel()
{
	// TEMPORARY VARIABLES
	bool * roomsHaveExit = new bool[GRID_X * GRID_Y];

	// INSTANTIATE VARIABLES
	for (int index = 0; index < GRID_X * GRID_Y; index++)
		roomsHaveExit[index] = false;

	// RESET MEMBER VARIABLES
	this->roomSelections.clear();

	// -----Clear Level-----
	for (int row = 0; row < (ROOM_X + 2) * GRID_X + 2; row++)
	{
		for (int column = 0; column < (ROOM_Y + 2) * GRID_X + 2; column++)
		{
			this->level[row][column] = ' ';
		}
	}

	// Get possible room selections
	g_LoadFromFloor(this->floor, &this->roomSelections);

	// -----Borders and Room Contents-----
	// Set exit room, at least 2 rooms away from entry room
	do
	{
		this->exitRoom.X = rand() / (RAND_MAX / GRID_X);
		this->exitRoom.Y = rand() / (RAND_MAX / GRID_Y);
	} while (this->exitRoom.X >= this->playerStartRoom.X - 1 &&
		this->exitRoom.X <= this->playerStartRoom.X + 1 &&
		this->exitRoom.Y >= this->playerStartRoom.Y - 1 &&
		this->exitRoom.Y <= this->playerStartRoom.Y + 1);

	for (int gridRow = 0; gridRow < GRID_X; gridRow++)
	{
		for (int gridColumn = 0; gridColumn < GRID_Y; gridColumn++)
		{
			if ((this->exitRoom.X == gridRow && this->exitRoom.Y == gridColumn) ||
				(this->playerStartRoom.X == gridRow && this->playerStartRoom.Y == gridColumn))
			{
				for (int wallColumn = 0; wallColumn < ROOM_Y + 2; wallColumn++)
					this->level[1 + gridRow * (ROOM_X + 2)][1 + gridColumn * (ROOM_Y + 2) + wallColumn] = '#';
				for (int roomRow = 1; roomRow <= ROOM_X; roomRow++)
				{
					this->level[1 + gridRow * (ROOM_X + 2) + roomRow][1 + gridColumn * (ROOM_Y + 2)] = '#';
					this->level[1 + gridRow * (ROOM_X + 2) + roomRow][(gridColumn + 1) * (ROOM_Y + 2)] = '#';
				}
				for (int wallColumn = 0; wallColumn < ROOM_Y + 2; wallColumn++)
					this->level[(gridRow + 1) * (ROOM_X + 2)][1 + gridColumn * (ROOM_Y + 2) + wallColumn] = '#';
			}
			else
			{
				g_LoadFromRoom(&this->roomSelections[rand() / (RAND_MAX / this->roomSelections.size())], &this->level, fastCoord(gridRow, gridColumn));
			}
		}
	}

	//// -----Borders and Padding-----
	//// Add the top border
	//for (int i = 0; i < 2; i++)
	//{
	//	for (int gridColumn = 0; gridColumn <= GRID_Y * (ROOM_Y + 1) + GRID_Y + 1; gridColumn++)
	//	{
	//		this->level[i] += "#";
	//	}
	//}

	//// Add the middle w/ padding
	//for (int gridRow = 0; gridRow < GRID_X; gridRow++)
	//{
	//	for (int cRow = 0; cRow < ROOM_X; cRow++)
	//	{
	//		for (int gridColumn = 0; gridColumn <= GRID_Y; gridColumn++)
	//		{
	//			this->level[gridRow * ROOM_X + (gridRow << 1) + cRow + 2] += "##";
	//			if (gridColumn != GRID_Y)
	//				for (int padding = 0; padding < ROOM_Y; padding++)
	//					this->level[gridRow * ROOM_X + (gridRow << 1) + cRow + 2] += " ";
	//		}
	//	}
	//	if (gridRow == GRID_X - 1) break;
	//	for (int i = 0; i < 2; i++)
	//	{
	//		for (int gridColumn = 0; gridColumn <= GRID_Y * (ROOM_Y + 1) + GRID_Y + 1; gridColumn++)
	//		{
	//			this->level[(gridRow + 1) * (ROOM_X + 1) + i + gridRow + 1] += "#";
	//		}
	//	}
	//}

	//// Add the bottom border
	//for (int i = 0; i < 2; i++)
	//{
	//	for (int gridColumn = 0; gridColumn <= GRID_Y * (ROOM_Y + 1) + GRID_Y + 1; gridColumn++)
	//	{
	//		this->level[GRID_X + (ROOM_X + 1) * GRID_X + i] += "#";
	//	}
	//}


	// -----Required Border Holes-----

	// Generate a route to the end
	std::vector<COORD> routeToEnd = { this->playerStartRoom };
	seekToEnd(routeToEnd);

	// Flag rooms with openings already
	for (auto& c : routeToEnd)
	{
		roomsHaveExit[c.X * GRID_Y + c.Y] = true;
	}

	// Create mandatory route openings
	for (std::vector<COORD>::iterator iter = routeToEnd.begin() + 1; iter != routeToEnd.end(); iter++)
	{
		int xDiff = (iter - 1)->X - iter->X;
		int yDiff = (iter - 1)->Y - iter->Y;
		COORD * c = this->getCoordinatesForDoor(iter->X, iter->Y, (xDiff < 0) ? (2) : (0) + (yDiff != 0) ? ((yDiff > 0) ? (3) : (1)) : (0));
		this->modifyTile(c[0], '$');
		this->modifyTile(c[1], '$');
	}

	// Add an opening for rooms with no entrances

	for (auto& room : routeToEnd)
	{
		this->uncoverAll(room, roomsHaveExit);
	}

	// -----Stairs Down-----

	{
		COORD c;
		c.X = 2 + (ROOM_X >> 1) + this->exitRoom.X * (ROOM_X + 2);
		c.Y = 2 + (ROOM_Y >> 1) + this->exitRoom.Y * (ROOM_Y + 2);
		this->modifyTile(c, '&');
	}

	std::ofstream dump("level.txt");
	for (int row = 0; row < (ROOM_X + 2) * GRID_X + 2; row++)
	{
		for (int column = 0; column < (ROOM_Y + 2) * GRID_Y + 2; column++)
		{
			dump << level[row][column];
		}
		dump << std::endl;
	}
	dump.close();

	// DELETE ALLOCATED STORAGE
	delete[] roomsHaveExit;
}

std::vector<COORD> SLevel::seekToEnd(std::vector<COORD>& returned)
{
	std::vector<int> checkDirection = { 0, 1, 2, 3 };
	std::random_shuffle(checkDirection.begin(), checkDirection.end());

	for (auto direction : checkDirection)
	{
		COORD c = returned.back();
		switch (direction)
		{
		case 0: // Go Up
			if (!(returned.back().X - 1 < 0))
				c.X--;
			break;
		case 1: // Go Right
			if (!(returned.back().Y + 1 >= GRID_Y))
				c.Y++;
			break;
		case 2: // Go Down
			if (!(returned.back().X + 1 >= GRID_X))
				c.X++;
			break;
		case 3: // Go Left
			if (!(returned.back().Y - 1 < 0))
				c.Y--;
			break;
		}
		bool toContinue = false;
		for (auto each : returned)
		{
			if (c.X == each.X && c.Y == each.Y)
			{
				toContinue = true;
				break;
			}
		}
		if (toContinue) continue;
		returned.push_back(c);
		if (returned.back().X == this->exitRoom.X && returned.back().Y == this->exitRoom.Y)
			return returned;
		else
		{
			std::vector<COORD> check = seekToEnd(returned);
			if (check.back().X == this->exitRoom.X && check.back().Y == this->exitRoom.Y)
				return returned;
			else
				continue;
		}
	}
	returned.pop_back();
	return returned;
}

void SLevel::uncoverAll(COORD room, bool * roomsHaveExit)
{
	std::vector<int> direction = { 0, 1, 2, 3 };
	std::random_shuffle(direction.begin(), direction.end());
	for (auto& dir : direction)
	{
		COORD c = room;
		COORD * cPointer;
		switch (dir)
		{
		case 0:
			if (room.X - 1 < 0) continue;
			if (roomsHaveExit[(room.X - 1) * GRID_Y + room.Y]) continue;
			cPointer = this->getCoordinatesForDoor(--c.X, c.Y, 0);
			this->modifyTile(cPointer[0], '$');
			this->modifyTile(cPointer[1], '$');
			roomsHaveExit[c.X * GRID_Y + c.Y] = true;
			this->uncoverAll(c, roomsHaveExit);
			break;
		case 1:
			if (room.Y + 1 >= GRID_Y) continue;
			if (roomsHaveExit[room.X * GRID_Y + room.Y + 1]) continue;
			cPointer = this->getCoordinatesForDoor(c.X, ++c.Y, 1);
			this->modifyTile(cPointer[0], '$');
			this->modifyTile(cPointer[1], '$');
			roomsHaveExit[c.X * GRID_Y + c.Y] = true;
			this->uncoverAll(c, roomsHaveExit);
			break;
		case 2:
			if (room.X + 1 >= GRID_X) continue;
			if (roomsHaveExit[(room.X + 1) * GRID_Y + room.Y]) continue;
			cPointer = this->getCoordinatesForDoor(++c.X, c.Y, 2);
			this->modifyTile(cPointer[0], '$');
			this->modifyTile(cPointer[1], '$');
			roomsHaveExit[c.X * GRID_Y + c.Y] = true;
			this->uncoverAll(c, roomsHaveExit);
			break;
		case 3:
			if (room.Y - 1 < 0) continue;
			if (roomsHaveExit[room.X * GRID_Y + room.Y - 1]) continue;
			cPointer = this->getCoordinatesForDoor(c.X, --c.Y, 3);
			this->modifyTile(cPointer[0], '$');
			this->modifyTile(cPointer[1], '$');
			roomsHaveExit[c.X * GRID_Y + c.Y] = true;
			this->uncoverAll(c, roomsHaveExit);
			break;
		}
	}
}

void SLevel::modifyTile(COORD c, char ch)
{
	this->level[c.X][c.Y] = ch;
}

char SLevel::getTile(COORD c)
{
	return this->level[c.X][c.Y];
}

COORD * SLevel::getCoordinatesForDoor(const SHORT& X, const SHORT& Y, const int& direction)
{
	static COORD c[2];
	switch (direction)
	{
	case 0: // Up
		c[0].X = (X + 1) * (ROOM_X + 2);
		c[0].Y = Y * (ROOM_Y + 2) + (ROOM_Y >> 1) + 2;
		c[1] = c[0];
		c[1].X++;
		break;
	case 1: // Right
		c[0].X = X * (ROOM_X + 2) + (ROOM_X >> 1) + 2;
		c[0].Y = Y * (ROOM_Y + 2);
		c[1] = c[0];
		c[1].Y++;
		break;
	case 2: // Down
		c[0].X = X * (ROOM_X + 2);
		c[0].Y = Y * (ROOM_Y + 2) + (ROOM_Y >> 1) + 2;
		c[1] = c[0];
		c[1].X++;
		break;
	case 3: // Left
		c[0].X = X * (ROOM_X + 2) + (ROOM_X >> 1) + 2;
		c[0].Y = (Y + 1) * (ROOM_Y + 2);
		c[1] = c[0];
		c[1].Y++;
		break;
	}
	return c;
}

COORD fastCoord(int& x, int& y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	return c;
}