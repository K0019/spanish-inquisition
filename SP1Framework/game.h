#pragma once

#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include "level.h"
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
    S_GAME,
    S_COUNT
};

// struct for the game character
struct SGameChar
{
    COORD m_cLocation;
    bool  m_bActive;

	COORD getRealCoords();
};

void init        ( void );      // initialize your variables, allocate memory, etc
void getInput    ( void );      // get input from player
void update      ( CStopWatch * timer, double missedTime ); // update the game and the state of the game
void render      ( CStopWatch * timer );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory

void splashScreenWait();    // waits for time to pass in splash screen
void gameplay();            // gameplay logic
void moveCharacter();       // moves the character, collision detection, physics, etc
void playerShoot();
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 
void renderSplashScreen();  // renders the splash screen
void renderGame();          // renders the game stuff
void renderMap();           // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void renderLevel();  // renders the borders of the rooms
void renderPellets();

#endif // _GAME_H