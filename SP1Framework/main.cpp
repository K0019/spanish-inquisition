// This is the main file to hold everthing together

#include "Framework\timer.h"
#include "game.h"

CStopWatch g_Timer;                            // Timer function to keep track of time and the frame rate
bool g_bQuitGame = false;                    // Set to true if you want to quit the game
const unsigned int gc_ucFPS = 100;                // FPS of this game
const double gc_uFrameTime = 1000 / (double)gc_ucFPS;    // time for each frame

//main loop declaration
void mainLoop( void );

// main function - starting function
// You should not be modifying this unless you know what you are doing
int main( void )
{
	init();		// initialize your variables
	mainLoop();	// main loop
	shutdown();	// do clean up, if any. free memory.
	
	return 0;
}

//--------------------------------------------------------------
// Purpose  : This main loop calls functions to get input, 
//            update and render the game at a specific frame rate
//            You should not be modifying this unless you know what you are doing.
// Input    : void
// Output   : void
//--------------------------------------------------------------
void mainLoop( void )
{
	g_Timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	double updateTime = g_Timer.getElapsedTime();
	while (!g_bQuitGame)										// run this loop until user wants to quit 
	{
		getInput();												// get keyboard input
		update(&g_Timer, updateTime);							// update the game
		render(&g_Timer);										// render the graphics output to screen
		updateTime = g_Timer.getElapsedTime();
		g_Timer.waitUntil(gc_uFrameTime - updateTime * 1000);	// Frame rate limiter. Limits each frame to a specified time in ms.      
	}
}
