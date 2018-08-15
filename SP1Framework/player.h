#pragma once

#ifndef PLAYERHEAD
#define PLAYERHEAD
#include <Windows.h>
#include "definitions.h"
#include "item.h"
#include <algorithm>


// struct for the game character
struct SGameChar
{
	COORD m_cLocation;
	COORD m_cRoom; // Room coordinates that the player is in
	int m_iPlayerHealth = 10;
	int	m_iPlayerDamage = 3;
	unsigned int m_iPlayerScore = 0;
	SAllItems m_sPlayerItems;

	COORD getRealCoords();
	SGameChar();
	SGameChar(COORD location, bool active, int playerHealth, int playerDamage, int playerScore);
	void AddItem(bool g_bHasWeapon); //Adds an item to the player's inventory when picked up
	void hasItem(bool g_bHasWeapon);
	void minimumScore(int playerScore);
};


#endif // !PLAYERHEAD
