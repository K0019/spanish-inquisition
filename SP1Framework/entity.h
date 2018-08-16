#pragma once

#ifndef ENTITYHEAD
#define ENTITYHEAD

#include "pellet.h"
#include "enemy.h"
#include "player.h"
#include "definitions.h"
#include <vector>
#include <memory>
#include "level.h"

struct SAllEntities
{
	/*PELLETS RELATED*/
	std::vector<SPellet> m_vPellets; // Container for pellets
	SGameChar g_sChar; // The player
	void updatePellets(); // Update movement of pellets
	void clearPellets(); // Erase the pellets that should be erased

	/*ENEMY RELATED*/
	std::vector<std::unique_ptr<Enemy>> m_vEnemy; // Container for enemies
	void updateEnemies(); // Update movement and attack of enemies
	void clearEnemies(); // Erase the enemies that are dead
};

#endif // !ENTITYHEAD
