#pragma once

#ifndef ENTITYHEAD
#define ENTITYHEAD

#include "pellet.h"
#include "enemy.h"
#include "player.h"
#include "definitions.h"
#include <vector>

struct SAllEntities
{
	/*PELLETS RELATED*/
	std::vector<SPellet> m_vPellets;
	SGameChar g_sChar;
	void updatePellets();
	void checkHitPellets();
	void clearPellets();

	/*ENEMY RELATED*/
	std::vector<Enemy> m_vEnemy;
	void updateEnemies();
};

#endif // !ENTITYHEAD
