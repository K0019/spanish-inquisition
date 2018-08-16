#pragma once

#ifndef PLAYERHEAD
#define PLAYERHEAD
#include <Windows.h>
#include "definitions.h"
#include "item.h"
#include "consumables.h"
#include <algorithm>


// struct for the game character
struct SGameChar
{
	COORD m_cLocation; // Tile coordinates of the player
	COORD m_cRoom; // Room coordinates that the player is in
	bool m_bInBattle; // If player is in a room with enemies
	int m_iMaxHealth = 10;
	int m_iPlayerHealth = 10;
	int	m_iPlayerDamage = 3;
	unsigned int m_iPlayerScore = 0;
	double m_dRange = 2.5;
	SAllItems m_sPlayerItems;
	SAllConsumables m_sConsumables;

	COORD getRealCoords(); // Get console coordinates of the player
	SGameChar(); // Constructor
	SGameChar(COORD location, bool active, int playerHealth, int playerDamage, int playerScore); // Constructor
	void addItem(bool g_bHasWeapon); //Adds an item to the player's inventory when picked up
	void hasItem(bool g_bHasWeapon);
	void addConsumable(bool g_bHasConsumable, int index);
	void hasConsumable(bool g_bHasConsumable, int index);
	void minimumScore(int playerScore);
};


#endif // !PLAYERHEAD
