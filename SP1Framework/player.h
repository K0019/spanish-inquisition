#pragma once

#ifndef PLAYERHEAD
#define PLAYERHEAD
#include <Windows.h>
#include "definitions.h"
#include <algorithm>

// struct for the game character
struct SGameChar
{
	COORD m_cLocation;
	COORD m_cRoom; // Room coordinates that the player is in
	int m_iPlayerHealth = 10;
	int	m_iPlayerDamage = 3;
	int	m_iPlayerScore = 0;

	COORD getRealCoords();
	SGameChar();
	SGameChar(COORD location, bool active, int playerHealth, int playerDamage, int playerScore);
};

#endif // !PLAYERHEAD
