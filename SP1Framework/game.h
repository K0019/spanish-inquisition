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
	S_SHOP,
	S_OPTIONS,
	S_HOWTOPLAY,
    S_GAME,
    S_COUNT
};



void init        ( void ); /* FRAMEWORK */ // initialize your variables, allocate memory, etc
void getInput    ( void ); /* FRAMEWORK */ // get input from player
void update      ( CStopWatch * timer, double missedTime ); /* FRAMEWORK */ // update the game and the state of the game
void render      ( CStopWatch * timer ); /* FRAMEWORK */ // renders the current state of the game to the console
void shutdown    ( void ); /* FRAMEWORK */ // do clean up, free memory

/*
	THE UPDATE FUNCTIONS
*/

void splashScreenWait();	// waits for time to pass in splash screen
void mainMenu();			// main menu logic
void tutorial();			// how to play screen logic
void shop();				// shop logic
void options();				// options logic
void playerShoot();			// allows the player to shoot
void gameplay();			// gameplay logic
void menuNavigate();		// Navigation of menu
void goBack();
void resetLevel(int floor); // Generate a new map, with input floor for what to put inside the rooms
void controlPlayer();		// moves the character, collision detection, physics, etc
void processUserInput();	// checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();			// clears the current screen and draw from scratch 
void checkHitPellets(); // Check if pellets have hit anything
void processMenuEvent();

/*
	THE RENDER FUNCTIONS
*/

void renderSplashScreen();	// renders the splash screen
void renderMainMenu();		// renders the main menu
void renderTutorial();
void renderShop();
void renderOptions();
void renderGame();			// renders the game stuff
void renderScore();			// render the current score from
void renderCharacter();		// renders the character into the buffer
void renderFramerate();		// renders debug information, frame rate, elapsed time, etc
void renderToScreen();		// dump the contents of the buffer to the screen, one frame worth of game
void renderLevel();			// renders the borders of the rooms
void renderPellets();		// render pellets to buffer
void renderEnemy();			// renders all enemies to the buffer
void renderStat();			//renders the player stats on the right side of the console
void render(COORD c, LPCSTR text, LPCSTR text2, WORD color); // Render sprite to screen
void render(COORD c, std::string& text, std::string& text2, WORD color); // Render sprite to screen
bool loadEnemiesFromRoom(); // Load all enemies from the room that the player entered
void addEnemy(EnemyMelee * enemy); // Add an enemy to the enemy list
void addEnemy(EnemyRanged * enemy); // Add an enemy to the enemy list

#endif // _GAME_H