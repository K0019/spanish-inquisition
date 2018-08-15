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
	std::vector<SPellet> m_vPellets;
	SGameChar g_sChar;
	void updatePellets();
	void clearPellets();
	void clearEnemies();

	/*ENEMY RELATED*/
	std::vector<std::unique_ptr<Enemy>> m_vEnemy;
	void updateEnemies();
};

#endif // !ENTITYHEAD
