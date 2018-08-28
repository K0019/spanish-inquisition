#pragma once

/* TRANSFERED FROM FRAMEWORK, Modified by: Kendrick and Winston */

#ifndef PLAYERHEAD
#define PLAYERHEAD
#include <Windows.h>
#include "definitions.h"
#include "item.h"
#include "consumables.h"
#include <algorithm>

// Struct for the game character, containing information about the player
struct SGameChar
{
	COORD m_cLocation; // Tile coordinates of the player
	COORD m_cRoom; // Room coordinates that the player is in
	bool m_bInBattle; // If player is in a room with enemies
	bool m_bDefeatedBoss; // If player has defeated boss
	int m_iMaxHealth = 10; //Max health of the player can only be increased by items, and does not go down when player is damaged
	int m_iPlayerHealth = 10; //The constantly changing variable, increased by items and consumables.
	int m_iPreviousHealth; // The health of the player at the last update. Used for hit indicator
	int	m_iPlayerDamage = 3; //The amount of damage the player deals per pellet
	unsigned int m_iPlayerScore = 0; //The player's score
	unsigned int m_iGlobalScore = 0; //The player's score after each run, to be spent at the shop
	double m_dRange = 2.5; //How long the player's pellets will last before de-spawning
	double m_dVelocity = SHOOTVELOCITY; //The velocity of the player's pellets
	SAllItems m_sPlayerItems; // Container for items
	SAllConsumables m_sConsumables; // Container for consumables
	std::string m_sLastItem = ""; //Storing last item picked up

	COORD getRealCoords(); // Get console coordinates of the player
	SGameChar(); // Default Constructor for the game character struct
	SGameChar(COORD location, bool active, int playerHealth, int playerDamage, int playerScore, std::string lastItem); // Constructor to initialise specific variables
	void addItem(bool g_bHasWeapon); //Adds an item to the player when picked up, using g_bHasWeapon as the condition checker
	void hasItem(bool g_bHasWeapon); //Main function with item spawning algorithm, choosing which item to give the player and what level of item depending on upgrades
	void addConsumable(bool g_bHasConsumable, int index); //Adds a consumable to the player when picked up, using g_bHasConsumable as the condition checker
	void hasConsumable(bool g_bHasConsumable, int index); //Main to give the player the correct stat. increase depending on which consumable is collected
	void minimumScore(int playerScore); //Ensures the player's score will not go below 0.
};

#endif // !PLAYERHEAD
