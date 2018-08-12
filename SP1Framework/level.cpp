#include "level.h"

void SLevel::generateLevel()
{
	// -----Borders and Padding-----
	// Add the top border
	for (int gridColumn = 0; gridColumn <= GRID_Y * (ROOM_Y + 1); gridColumn++)
	{
		this->level[0] += "##";
	}

	// Add the rest w/ padding
	for (int gridRow = 0; gridRow < GRID_X; gridRow++)
	{
		for (int cRow = 0; cRow < ROOM_X; cRow++)
		{
			for (int gridColumn = 0; gridColumn <= GRID_Y; gridColumn++)
			{
				this->level[gridRow * ROOM_X + gridRow + cRow + 1] += "##";
				if (gridColumn != GRID_Y)
					for (int padding = 0; padding < ROOM_Y; padding++)
						this->level[gridRow * ROOM_X + gridRow + cRow + 1] += "  ";
			}
		}
		for (int gridColumn = 0; gridColumn <= GRID_Y * (ROOM_Y + 1); gridColumn++)
		{
			this->level[(gridRow + 1) * (ROOM_X + 1)] += "##";
		}
	}

	// -----Required Border Holes-----
	// Set exit room, at least 2 rooms away from entry room
	do
	{
		this->exitRoom.X = rand() / (RAND_MAX / 3);
		this->exitRoom.Y = rand() / (RAND_MAX / 5);
	} while (this->exitRoom.X >= this->playerStartRoom.X - 1 &&
		this->exitRoom.X <= this->playerStartRoom.X + 1 &&
		this->exitRoom.Y >= this->playerStartRoom.Y - 1 &&
		this->exitRoom.Y <= this->playerStartRoom.Y + 1);

	// Generate a route to the end
	std::vector<COORD> routeToEnd = { this->playerStartRoom };
	routeToEnd = seekToEnd(routeToEnd);

	// Create openings
	for (std::vector<COORD>::iterator iter = routeToEnd.begin() + 1; iter != routeToEnd.end(); iter++)
	{
		int xDiff = (*(iter - 1)).X - (*iter).X;
		int yDiff = (*(iter - 1)).Y - (*iter).Y;
		COORD c;
		switch ((xDiff < 0) ? (2) : (0) + (yDiff != 0) ? ((yDiff > 0) ? (3) : (1)) : (0))
		{
		case 0: // Up
			c.X = ((*iter).X + 1) * (ROOM_X + 1);
			c.Y = (*iter).Y * (ROOM_Y + 1) + (ROOM_Y >> 1) + 1;
			break;
		case 1: // Right
			c.X = (*iter).X * (ROOM_X + 1) + (ROOM_X >> 1) + 1;
			c.Y = (*iter).Y * (ROOM_Y + 1);
			break;
		case 2: // Down
			c.X = ((*iter).X) * (ROOM_X + 1);
			c.Y = (*iter).Y * (ROOM_Y + 1) + (ROOM_Y >> 1) + 1;
			break;
		case 3: // Left
			c.X = (*iter).X * (ROOM_X + 1) + (ROOM_X >> 1) + 1;
			c.Y = ((*iter).Y + 1) * (ROOM_Y + 1);
			break;
		}
		this->modifyTile(c, "$$");
	}
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
		case 0:
			if (!(returned.back().X - 1 < 0))
				c.X--;
			break;
		case 1:
			if (!(returned.back().Y + 1 >= GRID_Y))
				c.Y++;
			break;
		case 2:
			if (!(returned.back().X + 1 >= GRID_X))
				c.X++;
			break;
		case 3:
			if (!(returned.back().Y - 1 < 0))
				c.Y--;
			break;
		default:
			throw std::invalid_argument("checkDirection out of range");
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

void SLevel::modifyTile(COORD c, std::string ch)
{
	this->level[c.X].replace(c.Y << 1, ch.length(), ch);
}