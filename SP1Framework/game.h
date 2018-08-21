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
void splashScreenWait();	// waits for time to pass in splash screen
void playerShoot();			// allows the player to shoot
void gameplay();			// gameplay logic
void menuLogic();
void menuNav();
void submenuNav();
void resetLevel(int floor); // Generate a new map, with input floor for what to put inside the rooms
void controlPlayer();		// moves the character, collision detection, physics, etc
void processUserInput();	// checks if you should change states or do something else with the game, e.g. pause, exit
void checkHitPellets();		// Check if pellets have hit anything
void doomButton();			// heehee
void detectPauseMenuProc();
void pauseScreen();
void changedRoomUpdate(); // Stuff to do when the player exits current room
bool loadEnemiesFromRoom(); // Load all enemies from the room that the player entered
void addEnemy(EnemyMelee * enemy); // Add an enemy to the enemy list
void addEnemy(EnemyRanged * enemy); // Add an enemy to the enemy list

void setUpMoveScreen(); // Setup variables to move render screen
void moveScreen(); // Moves the render screen

/*
	THE RENDER FUNCTIONS
*/

void clearScreen();			// clears the current screen and draw from scratch 
void renderSplashScreen();	// renders the splash screen
void renderMenu();			// renders the main menu
void renderGame();			// renders the game stuff
void renderPause();
void renderScore();			// render the current score from
void renderCharacter();		// renders the character into the buffer
void renderFramerate();		// renders debug information, frame rate, elapsed time, etc
void renderToScreen();		// dump the contents of the buffer to the screen, one frame worth of game
void renderLevel();			// renders the borders of the rooms
void renderPellets();		// render pellets to buffer
void renderMiniMap();		// render minimap to buffer
void renderEnemy();			// renders all alive enemies to the buffer
void renderDeadEnemy(); // renders all dead enemies to the buffer
void renderStat();			//renders the player stats on the right side of the console
void render(COORD c, LPCSTR text, LPCSTR text2, WORD color); // Render sprite to screen
void render(COORD c, std::string& text, std::string& text2, WORD color); // Render sprite to screen

#endif // _GAME_H