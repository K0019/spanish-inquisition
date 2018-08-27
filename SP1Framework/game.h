#pragma once

/* SHARED */

#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include "level.h"
#include "entity.h"
#include "fileio.h"
#include "menu.h"
#include "definitions.h"
#include "MusicManager.h"
#include <string>
#include <cstdlib>
#include <vector>

extern CStopWatch g_swTimer; /* FRAMEWORK */
extern bool g_bQuitGame; /* FRAMEWORK */

// Enumeration to store the control keys that your game will have
enum EKEYS /* FRAMEWORK */
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
	K_V,
	K_SHOOTUP,
	K_SHOOTRIGHT,
	K_SHOOTDOWN,
	K_SHOOTLEFT,
    K_ESCAPE,
    K_SPACE,
	K_ENTER,
    K_COUNT
};

// Enumeration for the different screen states
enum EGAMESTATES /* FRAMEWORK */
{
    S_SPLASHSCREEN,
	S_MENU,
    S_GAME,
	S_PAUSED,
    S_COUNT
};
//	DO NOT DELETE: IMPORTANT
void init        ( void ); /* FRAMEWORK */ // initialize your variables, allocate memory, etc
void getInput    ( void ); /* FRAMEWORK */ // get input from player
void update      ( CStopWatch * timer, double missedTime ); /* FRAMEWORK */ // update the game and the state of the game
void render      ( CStopWatch * timer ); /* FRAMEWORK */ // renders the current state of the game to the console
void shutdown    ( void ); /* FRAMEWORK */ // do clean up, free memory
/*
	THE UPDATE FUNCTIONS
*/
void loadGame(); /* Made by: Yan Quan */
void saveGame(); /* Made by: Yan Quan */
void splashScreenWait(); /* FRAMEWORK */ // waits for time to pass in splash screen
void playerShoot(); /* Made by: Kendrick */ // allows the player to shoot
void gameplay(); /* SHARED */ // gameplay logic
void menuLogic(); /* Made by: Yan Quan */
void menuNav(); /* Made by: Yan Quan */
void submenuNav(); /* Made by: Yan Quan */
void resetLevel(int floor); /* Made by: Kendrick */ // Generate a new map, with input floor for what to put inside the rooms
void controlPlayer(); /* Made by: Kendrick, modified by Winston and Yan Quan */ // moves the character, collision detection, physics, etc
void checkHitPellets(); /* Made by: Kendrick, modified by Winston */ // Check if pellets have hit anything
void checkTrapCollision(); /* Made by: Winston */ //Check if player is standing on a trap
void doomButton(); /* Made by: Yan Quan */ // heehee
void detectPauseMenuProc(); /* Made by: Yan Quan */
void pauseScreen(); /* Made by: Yan Quan */
void pauseScreenNav(); /* Made by: Yan Quan */
void changedRoomUpdate(); /* Made by: Kendrick */ // Stuff to do when the player exits current room
bool loadEnemiesFromRoom(); /* Made by: Kendrick */ // Load all enemies from the room that the player entered
bool loadBoss(); /* Made by: Kendrick */ // Load the boss into the exit room, if player is in floor 5
void addEnemy(EnemyMelee * enemy); /* Made by: Kendrick */ // Add an enemy to the enemy list
void addEnemy(EnemyRanged * enemy); /* Made by: Kendrick */ // Add an enemy to the enemy list
void CharacterDeath(); /* Made by: Jo Chu */
void setUpMoveScreen(); /* Made by: Kendrick */ // Setup variables to move render screen
void moveScreen(); /* Made by: Kendrick */ // Moves the render scree
/*
	THE RENDER FUNCTIONS
*/
void clearScreen(); /* FRAMEWORK */ // clears the current screen and draw from scratch 
void renderSplashScreen(); /* Modified by: Yan Quan */ // renders the splash screen
void renderMenu(); /* Made by: Yan Quan */ // renders the main menu
void renderGame(); /* FRAMEWORK */ // renders the game stuff
void renderPause(); /* Made by: Yan Quan */
void renderPauseCursor(); /* Made by: Yan Quan */
void renderPauseMenu(); /* Made by: Yan Quan */
void renderScore(); /* Made by: Winston */ // render the current score from
void renderCharacter(); /* Modified by: Kendrick */ // renders the character into the buffer
void renderFramerate(); /* Modified by: Kendrick */ // renders debug information, frame rate, elapsed time, etc
void renderToScreen(); /* FRAMEWORK */ // dump the contents of the buffer to the screen, one frame worth of game
void renderLevel(); /* Made by: Kendrick */ // render the level elements to buffer
void renderPellets(); /* Made by: Kendrick */ // render pellets to buffer
void renderMiniMap(); /* Made by: Kendrick */ // render minimap to buffer
void renderEnemy(); /* Made by: Kendrick */ // renders all alive enemies to the buffer
void renderDeadEnemy(); /* Made by: Kendrick */ // renders all dead enemies to the buffer
void renderBoss(); /* Made by: Kendrick */ // renders boss
void renderStat(); /* Made by: Winston */ //renders the player stats on the right side of the console
void renderHealthIndicator(); /* Made by: Kendrick */ // renders the red border around the room when at 5 health or less health
void render(COORD c, LPCSTR text, LPCSTR text2, WORD color); /* Made by: Kendrick */ // Render sprite to screen
void render(COORD c, std::string& text, std::string& text2, WORD color); /* Made by: Kendrick */ // Render sprite to screen
void render(COORD c, std::string * text, WORD color); /* Made by: Kendrick */ // Render boss to screen

#endif // _GAME_H