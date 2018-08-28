#include "level.h"
#include "Framework/console.h"

extern Console g_Console;

SLevel::~SLevel()
{
	if (this->miniMap != nullptr) delete this->miniMap;
}

void SLevel::generateLevel()
{
	// TEMPORARY VARIABLES
	bool * roomsHaveExit = new bool[GRID_X * GRID_Y];
	std::vector<std::string> roomSelections, itemRoomSelections;

	// INSTANTIATE VARIABLES
	for (int index = 0; index < GRID_X * GRID_Y; index++)
		roomsHaveExit[index] = false;

	// RESET MEMBER VARIABLES
	if (this->miniMap != nullptr) delete this->miniMap;

	// -----Clear Level-----
	for (int row = 0; row < (ROOM_X + 2) * GRID_X + 2; row++)
	{
		for (int column = 0; column < (ROOM_Y + 2) * GRID_Y + 2; column++)
		{
			this->level[row][column] = ' ';
		}
	}

	// Get possible room selections
	g_LoadFromFloor(this->floor, &roomSelections);
	g_LoadFromFloorItem(this->floor, &itemRoomSelections);

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
	// Set item room somewhere in the level
	do
	{
		this->itemRoom.X = rand() / (RAND_MAX / GRID_X);
		this->itemRoom.Y = rand() / (RAND_MAX / GRID_Y);
	} while ((this->exitRoom.X == this->itemRoom.X && this->exitRoom.Y == this->itemRoom.Y) ||
		(this->playerStartRoom.X == this->itemRoom.X && this->playerStartRoom.Y == this->itemRoom.Y));

	// Generate level
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
			else if (this->itemRoom.X == gridRow && this->itemRoom.Y == gridColumn)
			{
				g_LoadFromItemRoom(&itemRoomSelections[rand() / (RAND_MAX / itemRoomSelections.size())], &this->level, fastCoord(gridRow, gridColumn));
			}
			else
			{
				g_LoadFromRoom(&roomSelections[rand() / (RAND_MAX / roomSelections.size())], &this->level, fastCoord(gridRow, gridColumn));
			}
		}
	}

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

	// Add an extra door for every 6 rooms
	int extraDoors = 0;
	do
	{
		std::vector<int> directions;
		bool isDirectionPossible[4] = { true, true, true, true };
		COORD c;
		c.X = rand() / (RAND_MAX / GRID_X);
		c.Y = rand() / (RAND_MAX / GRID_Y);
		switch (c.X)
		{
		case 0:
			isDirectionPossible[2] = false;
			break;
		case GRID_X - 1:
			isDirectionPossible[0] = false;
			break;
		}
		switch (c.Y)
		{
		case 0:
			isDirectionPossible[1] = false;
			break;
		case GRID_Y - 1:
			isDirectionPossible[3] = false;
			break;
		}

		for (int direction = 0; direction < 4; direction++)
		{
			if (isDirectionPossible[direction] && this->getTile(this->getCoordinatesForDoor(c.X, c.Y, direction)[0]) != '$')
				directions.push_back(direction);
		}
		if (directions.empty()) continue;

		COORD * doors = this->getCoordinatesForDoor(c.X, c.Y, directions[rand() / (RAND_MAX / directions.size())]);
		this->modifyTile(doors[0], '$');
		this->modifyTile(doors[1], '$');
		extraDoors++;
	} while (extraDoors < GRID_X * GRID_Y / 6);

	// -----Stairs Down-----

	{
		if (this->floor != 5)
		{
			this->createStairs();
		}
	}

	// DELETE ALLOCATED STORAGE
	delete[] roomsHaveExit;

	// Generate minimap
	this->miniMap = new SMiniMap(&this->level, this->playerStartRoom, this->exitRoom);
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

void SLevel::createStairs()
{
	COORD c;
	c.X = 2 + (ROOM_X >> 1) + this->exitRoom.X * (ROOM_X + 2);
	c.Y = 2 + (ROOM_Y >> 1) + this->exitRoom.Y * (ROOM_Y + 2);
	this->modifyTile(c, '&');
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

SMiniMap::SMiniMap(char (*level)[(ROOM_X + 2) * GRID_X + 2][(ROOM_Y + 2) * GRID_Y + 2], COORD playerStartRoom, COORD exitRoom)
{
	for (int roomIndex = 0; roomIndex < GRID_X * GRID_Y; roomIndex++)
	{
		this->enteredRoom[roomIndex] = false;
	}

	this->level = level;
	this->enteredRoom[playerStartRoom.X * GRID_Y + playerStartRoom.Y] = true;
	this->playerEndRoom = exitRoom;
}

void SMiniMap::refresh(COORD playerLocation)
{
	// Empty map buffer
	for (int row = 0; row < 1 + (GRID_X << 1); row++)
	{
		for (int column = 0; column < 1 + (GRID_Y << 1); column++)
		{
			this->map[row][column] = ' ';
		}
	}

	// Add exit room if discovered
	if (this->enteredRoom[this->playerEndRoom.X * GRID_Y + this->playerEndRoom.Y])
	{
		this->map[(this->playerEndRoom.X << 1) + 1][(this->playerEndRoom.Y << 1) + 1] = '&';
	}

	// Buffer all of the uncovered minimap
	for (int roomIndex = 0; roomIndex < GRID_X * GRID_Y; roomIndex++)
	{
		if (this->enteredRoom[roomIndex])
		{
			for (int column = (roomIndex % GRID_Y) << 1; column <= (roomIndex % GRID_Y + 1) << 1; column++)
			{
				this->map[(roomIndex / GRID_Y) << 1][column] = '#';
			}
			this->map[((roomIndex / GRID_Y) << 1) + 1][(roomIndex % GRID_Y) << 1] = '#';
			if ((playerLocation.X - 1) / (ROOM_X + 2) * GRID_Y + (playerLocation.Y - 1) / (ROOM_Y + 2) == roomIndex)
			{
				this->map[((roomIndex / GRID_Y) << 1) + 1][((roomIndex % GRID_Y) << 1) + 1] = '!';
			}
			this->map[((roomIndex / GRID_Y) << 1) + 1][((roomIndex % GRID_Y) << 1) + 2] = '#';
			for (int column = (roomIndex % GRID_Y) << 1; column <= (roomIndex % GRID_Y + 1) << 1; column++)
			{
				this->map[((roomIndex / GRID_Y) << 1) + 2][column] = '#';
			}

			if (this->hasDoor(roomIndex, 0))
			{
				if (this->hasExplored(roomIndex, 0))
				{
					this->map[(roomIndex / GRID_Y) << 1][((roomIndex % GRID_Y) << 1) + 1] = '$';
				}
				else
				{
					this->map[(roomIndex / GRID_Y) << 1][((roomIndex % GRID_Y) << 1) + 1] = '@';
				}
			}
			if (this->hasDoor(roomIndex, 1))
			{
				if (this->hasExplored(roomIndex, 1))
				{
					this->map[((roomIndex / GRID_Y) << 1) + 1][(roomIndex % GRID_Y + 1) << 1] = '$';
				}
				else
				{
					this->map[((roomIndex / GRID_Y) << 1) + 1][(roomIndex % GRID_Y + 1) << 1] = '@';
				}
			}
			if (this->hasDoor(roomIndex, 2))
			{
				if (this->hasExplored(roomIndex, 2))
				{
					this->map[(roomIndex / GRID_Y + 1) << 1][((roomIndex % GRID_Y) << 1) + 1] = '$';
				}
				else
				{
					this->map[(roomIndex / GRID_Y + 1) << 1][((roomIndex % GRID_Y) << 1) + 1] = '@';
				}
			}
			if (this->hasDoor(roomIndex, 3))
			{
				if (this->hasExplored(roomIndex, 3))
				{
					this->map[((roomIndex / GRID_Y) << 1) + 1][(roomIndex % GRID_Y) << 1] = '$';
				}
				else
				{
					this->map[((roomIndex / GRID_Y) << 1) + 1][(roomIndex % GRID_Y) << 1] = '@';
				}
			}
		}
	}
}

bool SMiniMap::hasDoor(int roomIndex, int direction)
{
	switch (direction)
	{
	case 0: // Up
		if ((roomIndex / GRID_Y) - 1 < 0) return false;
		if ((*this->level)[(roomIndex / GRID_Y) * (ROOM_X + 2)][(roomIndex % GRID_Y) * (ROOM_Y + 2) + (ROOM_Y >> 1) + 2] == '$') return true;
		break;
	case 1: // Right
		if ((roomIndex % GRID_Y) + 1 < 0) return false;
		if ((*this->level)[(roomIndex / GRID_Y) * (ROOM_X + 2) + (ROOM_X >> 1) + 2][(roomIndex % GRID_Y + 1) * (ROOM_Y + 2)] == '$') return true;
		break;
	case 2: // Down
		if ((roomIndex / GRID_Y) + 1 >= GRID_X) return false;
		if ((*this->level)[(roomIndex / GRID_Y + 1) * (ROOM_X + 2)][(roomIndex % GRID_Y) * (ROOM_Y + 2) + (ROOM_Y >> 1) + 2] == '$') return true;
		break;
	case 3: // Left
		if ((roomIndex % GRID_Y) - 1 >= GRID_Y) return false;
		if ((*this->level)[(roomIndex / GRID_Y) * (ROOM_X + 2) + (ROOM_X >> 1) + 2][(roomIndex % GRID_Y) * (ROOM_Y + 2)] == '$') return true;
		break;
	}
	return false;
}

bool SMiniMap::hasExplored(int roomIndex, int direction)
{
	switch (direction)
	{
	case 0:
		if (this->enteredRoom[roomIndex - GRID_Y]) return true;
		break;
	case 1:
		if (this->enteredRoom[roomIndex + 1]) return true;
		break;
	case 2:
		if (this->enteredRoom[roomIndex + GRID_Y]) return true;
		break;
	case 3:
		if (this->enteredRoom[roomIndex - 1]) return true;
	}
	return false;
}

COORD fastCoord(int& x, int& y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	return c;
}