#pragma once

#ifndef PELLETHEAD
#define PELLETHEAD
#include <Windows.h>
#include "Framework/timer.h"
#include <iomanip>

struct SPellet
{
	CStopWatch Timer;
	COORD m_cLocation;
	short m_siDirection;
	bool m_bFriendly, m_bHit;
	double m_dTime;

	SPellet(COORD * c, short direction);
	void update();
	COORD getRealCoords();
};

#endif // !PELLET
