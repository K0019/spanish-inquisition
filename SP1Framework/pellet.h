#pragma once

#ifndef PELLETHEAD
#define PELLETHEAD
#include <Windows.h>
#include "Framework/timer.h"
#include "definitions.h"
#include <iomanip>

namespace pellet
{
	enum PHitReason
	{
		P_WALL,
		P_DOOR,
		P_PLAYER,
		P_ENEMY
	};
}

struct SPellet
{
	CStopWatch Timer; // Timer to keep track of when the pellet should next move/be erased
	COORD m_cLocation; // Tile coordinate of pellet
	short m_siDirection; // Direction the pellet is travelling, 8-direction
	bool m_bFriendly; // UNUSED | If pellet is shot by player or enemy
	bool m_bHit; // If pellet has hit something. Used to decide if the pellet should be erased
	int m_bHitReason; // What the pellet hit
	double m_dTime; // Length of time that the pellet has not updated
	double m_dVelocity; // Delay to when pellet will move

	SPellet(COORD * c, int direction, double velocity, bool friendly); // Constructor
	void update(); // Update position of pellet
	COORD getRealCoords(); // Get console coordinates of pellet. Used for rendering
};

#endif // !PELLET
