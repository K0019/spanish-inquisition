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

	// -----Borders and Padding-----
	// Add the top border
	for (int gridColumn = 0; gridColumn <= GRID_Y * (ROOM_Y + 1); gridColumn++)
	{
		this->level[0] += "#";
	}

	// Add the rest w/ padding
	for (int gridRow = 0; gridRow < GRID_X; gridRow++)
	{
		for (int cRow = 0; cRow < ROOM_X; cRow++)
		{
			for (int gridColumn = 0; gridColumn <= GRID_Y; gridColumn++)
			{
				this->level[gridRow * ROOM_X + gridRow + cRow + 1] += "#";
				if (gridColumn != GRID_Y)
					for (int padding = 0; padding < ROOM_Y; padding++)
						this->level[gridRow * ROOM_X + gridRow + cRow + 1] += " ";
			}
		}
		for (int gridColumn = 0; gridColumn <= GRID_Y * (ROOM_Y + 1); gridColumn++)
		{
			this->level[(gridRow + 1) * (ROOM_X + 1)] += "#";
		}
	}

	// -----Required Border Holes-----
	// Set exit room, at least 2 rooms away from entry room
	do
	{
		this->exitRoom.X = rand() / (RAND_MAX / GRID_X);
		this->exitRoom.Y = rand() / (RAND_MAX / GRID_Y);
	} while (this->exitRoom.X >= this->playerStartRoom.X - 1 &&
		this->exitRoom.X <= this->playerStartRoom.X + 1 &&
		this->exitRoom.Y >= this->playerStartRoom.Y - 1 &&
		this->exitRoom.Y <= this->playerStartRoom.Y + 1);

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
		COORD c = this->getCoordinatesForDoor(iter->X, iter->Y, (xDiff < 0) ? (2) : (0) + (yDiff != 0) ? ((yDiff > 0) ? (3) : (1)) : (0));
		this->modifyTile(c, "$");
	}

	// Add an opening for rooms with no entrances

	for (auto& room : routeToEnd)
	{
		this->uncoverAll(room, roomsHaveExit);
	}

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
		switch (dir)
		{
		case 0:
			if (room.X - 1 < 0) continue;
			if (roomsHaveExit[(room.X - 1) * GRID_Y + room.Y]) continue;
			this->modifyTile(this->getCoordinatesForDoor(--c.X, c.Y, 0), "$");
			roomsHaveExit[c.X * GRID_Y + c.Y] = true;
			this->uncoverAll(c, roomsHaveExit);
			break;
		case 1:
			if (room.Y + 1 >= GRID_Y) continue;
			if (roomsHaveExit[room.X * GRID_Y + room.Y + 1]) continue;
			this->modifyTile(this->getCoordinatesForDoor(c.X, ++c.Y, 1), "$");
			roomsHaveExit[c.X * GRID_Y + c.Y] = true;
			this->uncoverAll(c, roomsHaveExit);
			break;
		case 2:
			if (room.X + 1 >= GRID_X) continue;
			if (roomsHaveExit[(room.X + 1) * GRID_Y + room.Y]) continue;
			this->modifyTile(this->getCoordinatesForDoor(++c.X, c.Y, 2), "$");
			roomsHaveExit[c.X * GRID_Y + c.Y] = true;
			this->uncoverAll(c, roomsHaveExit);
			break;
		case 3:
			if (room.Y - 1 < 0) continue;
			if (roomsHaveExit[room.X * GRID_Y + room.Y - 1]) continue;
			this->modifyTile(this->getCoordinatesForDoor(c.X, --c.Y, 3), "$");
			roomsHaveExit[c.X * GRID_Y + c.Y] = true;
			this->uncoverAll(c, roomsHaveExit);
			break;
		}
	}
}

void SLevel::modifyTile(COORD c, std::string ch)
{
	this->level[c.X].replace(c.Y, ch.length(), ch);
}

char SLevel::getTile(COORD c)
{
	return this->level[c.X][c.Y];
}

COORD SLevel::getCoordinatesForDoor(const SHORT& X, const SHORT& Y, const int& direction)
{
	COORD c;
	switch (direction)
	{
	case 0: // Up
		c.X = (X + 1) * (ROOM_X + 1);
		c.Y = Y * (ROOM_Y + 1) + (ROOM_Y >> 1) + 1;
		break;
	case 1: // Right
		c.X = X * (ROOM_X + 1) + (ROOM_X >> 1) + 1;
		c.Y = Y * (ROOM_Y + 1);
		break;
	case 2: // Down
		c.X = X * (ROOM_X + 1);
		c.Y = Y * (ROOM_Y + 1) + (ROOM_Y >> 1) + 1;
		break;
	case 3: // Left
		c.X = X * (ROOM_X + 1) + (ROOM_X >> 1) + 1;
		c.Y = (Y + 1) * (ROOM_Y + 1);
		break;
	}
	return c;
}