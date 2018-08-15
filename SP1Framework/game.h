#pragma once

#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include "level.h"
#include "entity.h"
#include "fileio.h"
#include "definitions.h"
#include <string>
#include <cstdlib>
#include <vector>

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

// Enumeration to store the control keys that your game will have
enum EKEYS
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
    K_COUNT
};

// Enumeration for the different screen states
enum EGAMESTATES
{
    S_SPLASHSCREEN,
	S_MENU,
    S_GAME,
    S_COUNT
};

void init        ( void );      // initialize your variables, allocate memory, etc
void getInput    ( void );      // get input from player
void update      ( CStopWatch * timer, double missedTime ); // update the game and the state of the game
void render      ( CStopWatch * timer );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory


void splashScreenWait();	// waits for time to pass in splash screen
void mainMenu();			// main menu logic
void gameplay();			// gameplay logic
void moveCharacter();		// moves the character, collision detection, physics, etc
void playerShoot();			// allows the player to shoot
void resetLevel(int floor); // Generate a new map, with input floor for what to put inside the rooms
void processUserInput();	// checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();			// clears the current screen and draw from scratch 
void checkHitPellets(); // Check if pellets have hit anything
void renderSplashScreen();	// renders the splash screen
void renderMainMenu();		// renders the main menu
void renderGame();			// renders the game stuff
void renderCharacter();		// renders the character into the buffer
void renderFramerate();		// renders debug information, frame rate, elapsed time, etc
void renderToScreen();		// dump the contents of the buffer to the screen, one frame worth of game
void renderLevel();			// renders the borders of the rooms
void renderPellets();		// render pellets to buffer
void renderEnemy(); // renders all enemies to the buffer
void renderStat();   //renders the player stats on the right side of the console
void renderScore();			// render the current score from

#endif // _GAME_H