#pragma once

#ifndef ENTITYHEAD
#define ENTITYHEAD

#include "pellet.h"
#include "enemy.h"
#include "definitions.h"
#include <vector>

struct SAllEntities
{
	/*PELLETS RELATED*/
	std::vector<SPellet> m_vPellets;
	void updatePellets();
	void checkHitPellets();
	void clearPellets();

	/*ENEMY RELATED*/
	std::vector<Enemy> m_vEnemy;
};

#endif // !ENTITYHEAD
