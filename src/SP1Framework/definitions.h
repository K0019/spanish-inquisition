#pragma once

/* SHARED BY ALL, NO ONE OWNS THIS FILE */

#ifndef DEFINITIONSHEAD
#define DEFINITIONSHEAD

#define DEBUG false
#define PRESENTATION true
#define GRID_X 3
#define GRID_Y 5
#define ROOM_X 11
#define ROOM_Y 19
#define FINAL_FLOOR 5
#define SPECIAL_ROOMS_COUNT 2
#define SCREEN_SCROLL_LENGTH 0.7
#define SHOOTSPEED 0.35
#define SHOOTVELOCITY 0.225
#define ENEMY_DYING_LENGTH 1.0
#define PELLET_CHARACTER_TOP "/\\"
#define PELLET_CHARACTER_BOTTOM "\\/"
#define PELLET_CHARACTER_HIT_TOP "\\/"
#define PELLET_CHARACTER_HIT_BOTTOM "/\\"

/* ALL BELOW MADE BY: Winston */
#define UNIQUE_ENEMY_BANDIT new EnemyMelee(&g_sLevel, &g_sEntities.m_vEnemy, "Bandit", "BBBB", "BBBB", c, (WORD)0x0E, 12, 3, 0.3, 0.25, 0.1, 0.3, 10, 1)
#define UNIQUE_ENEMY_MAGE new EnemyRanged(&g_sLevel, &g_sEntities.m_vEnemy, &g_sEntities.m_vPellets, "Mage", "MMMM", "MMMM", c, (WORD)0x0E, 9, 2, 0.4, 0.3, 0.1, 0.3, false, 0.25, 10, 2)
#define UNIQUE_ENEMY_KNIGHT new EnemyMelee(&g_sLevel, &g_sEntities.m_vEnemy, "Knight", "KKKK", "KKKK", c, (WORD)0x0E, 25, 5, 0.2, 0.3, 0.1, 0.3, 20, 3)
#define UNIQUE_ENEMY_ENHANCEDSORCERER new EnemyRanged(&g_sLevel, &g_sEntities.m_vEnemy, &g_sEntities.m_vPellets, "Enhanced Sorcerer", "EEEE", "EEEE", c, (WORD)0x0E, 20, 2, 0.35, 0.4, 0.1, 0.2, true, 0.2, 30, 4)
#define UNIQUE_ENEMY_GUARDIAN new EnemyMelee(&g_sLevel, &g_sEntities.m_vEnemy, "Guardian", "GGGG", "GGGG", c, (WORD)0x0E, 35, 5, 0.18, 0.3, 0.1, 0.3, 40, 5)

#endif // !DEFINITIONSHEAD
