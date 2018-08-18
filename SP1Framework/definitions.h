#pragma once

/* SHARED BY ALL, NO ONE OWNS THIS FILE */

#ifndef DEFINITIONSHEAD
#define DEFINITIONSHEAD

#define DEBUG true
#define GRID_X 3
#define GRID_Y 5
#define ROOM_X 11
#define ROOM_Y 19
#define SPECIAL_ROOMS_COUNT 2
#define SHOOTSPEED 0.35
#define SHOOTVELOCITY 0.225
#define ENEMY_DYING_LENGTH 1.0
#define PELLET_CHARACTER_TOP "/\\"
#define PELLET_CHARACTER_BOTTOM "\\/"
#define PELLET_CHARACTER_HIT_TOP "\\/"
#define PELLET_CHARACTER_HIT_BOTTOM "/\\"

#define UNIQUE_ENEMY_BANDIT new EnemyMelee(&g_sLevel, "Bandit", "BBBB", "BBBB", c, (WORD)0x0E, 15, 3, 0.3, 0.3, 0.1, 0.3)
#define UNIQUE_ENEMY_MAGE new EnemyRanged(&g_sLevel, &g_sEntities.m_vPellets, "Mage", "MMMM", "MMMM", c, (WORD)0x0E, 10, 3, 0.4, 0.3, 0.1, 0.3, false, 0.25)

#endif // !DEFINITIONSHEAD
