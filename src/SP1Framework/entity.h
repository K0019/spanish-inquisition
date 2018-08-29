#pragma once

/* MADE BY: Kendrick */

#ifndef ENTITYHEAD
#define ENTITYHEAD

#include "pellet.h"
#include "enemy.h"
#include "boss.h"
#include "player.h"
#include "definitions.h"
#include <vector>
#include <memory>
#include "level.h"
#include "trap.h"

struct SAllEntities
{
	/*PELLETS RELATED*/
	std::vector<SPellet> m_vPellets; // Container for pellets
	SGameChar g_sChar; // The player
	Boss1 * boss; // Pointer to boss, pointer because dynamic
	void updatePellets(); // Update movement of pellets
	void clearPellets(); // Erase the pellets that should be erased

	/*ENEMY RELATED*/
	std::vector<std::unique_ptr<Enemy>> m_vEnemy; // Container for enemies
	void updateEnemies(); // Update movement and attack of enemies, also update enemy alive/dead status
	bool updateBoss(); // Update the boss, returns true if boss is dead
	void clearEnemies(); // Erase the enemies that are dead

	/*TRAP RELATED*/
	SAllTraps m_vTrapList; /* MADE BY: Winston */ // Container for traps

	~SAllEntities(); // Destructor
};

#endif // !ENTITYHEAD
