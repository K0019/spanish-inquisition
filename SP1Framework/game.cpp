// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <sstream>

double  g_dElapsedTime;
double  g_dDeltaTime;
int g_iCurrentFrameCount, g_iLastFrameCount, g_iLastMeasuredSecond;
double	g_dAccurateElapsedTime;
bool    g_abKeyPressed[K_COUNT];

// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
SLevel		g_sLevel;
double  g_adBounceTime[K_COUNT]; // this is to prevent key bouncing, so we won't trigger keypresses more than once

bool g_bHasShot;

// Console object
Console g_Console(100, 25, "SP1 Framework");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
	srand((unsigned int)time(NULL));
    // Set precision for floating point output
    g_dElapsedTime = 0.0;
	g_iCurrentFrameCount = g_iLastMeasuredSecond = 0;
	g_adBounceTime[K_SHOOTUP] = 0.0;
    for (int i = 0; i < K_COUNT; i++) g_adBounceTime[i] = 0.0;

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;
	if (DEBUG) g_eGameState = S_GAME;

	g_bHasShot = false;
    g_sChar.m_cLocation.X = 1 + (GRID_X >> 1) * (ROOM_X + 1) + (ROOM_X >> 1);
    g_sChar.m_cLocation.Y = 1 + (GRID_Y >> 1) * (ROOM_Y + 1) + (ROOM_Y >> 1);
    g_sChar.m_bActive = true;
	g_sLevel.playerStartRoom.X = GRID_X >> 1;
	g_sLevel.playerStartRoom.Y = GRID_Y >> 1;
	g_sLevel.generateLevel();
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{    
    g_abKeyPressed[K_UP]     = isKeyPressed(0x57);
    g_abKeyPressed[K_DOWN]   = isKeyPressed(0x53);
    g_abKeyPressed[K_LEFT]   = isKeyPressed(0x41);
    g_abKeyPressed[K_RIGHT]  = isKeyPressed(0x44);
	g_abKeyPressed[K_SHOOTUP] = isKeyPressed(VK_UP);
	g_abKeyPressed[K_SHOOTRIGHT] = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_SHOOTDOWN] = isKeyPressed(VK_DOWN);
	g_abKeyPressed[K_SHOOTLEFT] = isKeyPressed(VK_LEFT);
    g_abKeyPressed[K_SPACE]  = isKeyPressed(VK_SPACE);
    g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(CStopWatch * timer, double missedTime)
{
	double dt = timer->getElapsedTime() + missedTime;
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;
	g_dAccurateElapsedTime = timer->accurateTotalTime();

    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
        case S_GAME: gameplay(); // gameplay logic when we are in the game
            break;
    }
}
//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render(CStopWatch * timer)
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
        case S_SPLASHSCREEN: renderSplashScreen();
            break;
        case S_GAME: renderGame();
            break;
    }
    renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
	
	// Count average frames
	g_iCurrentFrameCount++;
	int currentSecond = (int)timer->accurateTotalTime();
	if (currentSecond > g_iLastMeasuredSecond)
	{
		g_iLastFrameCount = g_iCurrentFrameCount;
		g_iCurrentFrameCount = 0;
		g_iLastMeasuredSecond = currentSecond;
	}
}

void splashScreenWait()    // waits for time to pass in splash screen
{
    if (g_dAccurateElapsedTime > 3.0) // wait for 3 seconds to switch to game mode, else do nothing
        g_eGameState = S_GAME;
}

void gameplay()            // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
	playerShoot();
	g_sLevel.g_sEntities.updatePellets();
                        // sound can be played here too.
}

void moveCharacter()
{
	bool bSomethingHappened = false;

    // Updating the location of the character based on the key press
    // providing a beep sound whenver we shift the character
    if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.X > 0 && g_adBounceTime[K_UP] < g_dElapsedTime)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X--;
		if (g_sLevel.getTile(g_sChar.m_cLocation) == '#')
		{
			g_sChar.m_cLocation.X++;
		}
		else
		{
			bSomethingHappened = true;
		}
    }
    if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.Y > 0 && g_adBounceTime[K_LEFT] < g_dElapsedTime)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y--;
		if (g_sLevel.getTile(g_sChar.m_cLocation) == '#')
		{
			g_sChar.m_cLocation.Y++;
		}
		else
		{
			bSomethingHappened = true;
		}
    }
    if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().Y - 1 && g_adBounceTime[K_DOWN] < g_dElapsedTime)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X++;
		if (g_sLevel.getTile(g_sChar.m_cLocation) == '#')
		{
			g_sChar.m_cLocation.X--;
		}
		else
		{
			bSomethingHappened = true;
		}
    }
    if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().X - 2 && g_adBounceTime[K_RIGHT] < g_dElapsedTime)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y++;
		if (g_sLevel.getTile(g_sChar.m_cLocation) == '#')
		{
			g_sChar.m_cLocation.Y--;
		}
		else
		{
			bSomethingHappened = true;
		}
    }
    if (g_abKeyPressed[K_SPACE] && g_adBounceTime[K_SPACE] < g_dElapsedTime)
    {
        g_sChar.m_bActive = !g_sChar.m_bActive;
		bSomethingHappened = true;
    }

	if (bSomethingHappened)
	{
		for (int i = 0; i <= K_RIGHT; i++)
		{
			if (g_abKeyPressed[i]) g_adBounceTime[i] = g_dElapsedTime + 0.125;
		}
	}
}

void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_abKeyPressed[K_ESCAPE])
        g_bQuitGame = true;    
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x00);
}

void renderSplashScreen()  // renders the splash screen
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X / 2 - 9;
    g_Console.writeToBuffer(c, "A game in 3 seconds", 0x03);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 20;
    g_Console.writeToBuffer(c, "Press <Space> to change character colour", 0x09);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);
}

void renderGame()
{
    //renderMap();        // renders the map to the buffer first
	renderLevel();
    renderCharacter();  // renders the character into the buffer
	renderPellets();
	renderStat();
}

void renderMap()
{
    // Set up sample colours, and output shadings
    const WORD colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };

    COORD c;
    for (int i = 0; i < 12; ++i)
    {
        c.X = 5 * i;
        c.Y = i + 1;
        colour(colors[i]);
        g_Console.writeToBuffer(c, " °±²Û", colors[i]);
    }
}

void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0C;
    if (g_sChar.m_bActive)
    {
        charColor = 0x0A;
    }
    g_Console.writeToBuffer(g_sChar.getRealCoords(), "@@", charColor);
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = g_Console.getConsoleSize().X - 9;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

	// displays average fps
	ss.str("");
	ss << g_iLastFrameCount << "avg";
	c.Y++;
	g_Console.writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss << g_dAccurateElapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str(), 0x59);

	if (DEBUG)
	{
		ss.str("");
		// TODO: Show dropped frames
	}
}
void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}

// *******************************************************
// * Custom functions outside framework to go below here *
// *******************************************************
void playerShoot()
{
	if ((g_abKeyPressed[K_SHOOTDOWN] || g_abKeyPressed[K_SHOOTLEFT] || g_abKeyPressed[K_SHOOTRIGHT] || g_abKeyPressed[K_SHOOTUP]) && (g_adBounceTime[K_SHOOTUP] >= g_dElapsedTime + 0.225 || g_adBounceTime[K_SHOOTUP] < g_dElapsedTime))
	{
		g_bHasShot = false;
		if (g_adBounceTime[K_SHOOTUP] < g_dElapsedTime) g_adBounceTime[K_SHOOTUP] = g_dElapsedTime + 0.250;
	}
	else if (!g_bHasShot && g_adBounceTime[K_SHOOTUP] >= g_dElapsedTime && g_adBounceTime[K_SHOOTUP] < g_dElapsedTime + 0.225)
	{
		if (g_abKeyPressed[K_SHOOTUP] && !g_abKeyPressed[K_SHOOTDOWN])
		{
			if (g_abKeyPressed[K_SHOOTLEFT] && !g_abKeyPressed[K_SHOOTRIGHT])
			{
				COORD c = g_sChar.m_cLocation;
				c.X--;
				c.Y--;
				g_sLevel.g_sEntities.m_vPellets.push_back(SPellet(&c, 7));
				g_bHasShot = true;
				return;
			}
			else if (!g_abKeyPressed[K_SHOOTLEFT] && g_abKeyPressed[K_SHOOTRIGHT])
			{
				COORD c = g_sChar.m_cLocation;
				c.X--;
				c.Y++;
				g_sLevel.g_sEntities.m_vPellets.push_back(SPellet(&c, 1));
				g_bHasShot = true;
				return;
			}
			else if (!g_abKeyPressed[K_SHOOTLEFT] && !g_abKeyPressed[K_SHOOTRIGHT])
			{
				COORD c = g_sChar.m_cLocation;
				c.X--;
				g_sLevel.g_sEntities.m_vPellets.push_back(SPellet(&c, 0));
				g_bHasShot = true;
				return;
			}
		}
		else if (!g_abKeyPressed[K_SHOOTUP] && g_abKeyPressed[K_SHOOTDOWN])
		{
			if (g_abKeyPressed[K_SHOOTLEFT] && !g_abKeyPressed[K_SHOOTRIGHT])
			{
				COORD c = g_sChar.m_cLocation;
				c.X++;
				c.Y--;
				g_sLevel.g_sEntities.m_vPellets.push_back(SPellet(&c, 5));
				g_bHasShot = true;
				return;
			}
			else if (!g_abKeyPressed[K_SHOOTLEFT] && g_abKeyPressed[K_SHOOTRIGHT])
			{
				COORD c = g_sChar.m_cLocation;
				c.X++;
				c.Y++;
				g_sLevel.g_sEntities.m_vPellets.push_back(SPellet(&c, 3));
				g_bHasShot = true;
				return;
			}
			else if (!g_abKeyPressed[K_SHOOTLEFT] && !g_abKeyPressed[K_SHOOTRIGHT])
			{
				COORD c = g_sChar.m_cLocation;
				c.X++;
				g_sLevel.g_sEntities.m_vPellets.push_back(SPellet(&c, 4));
				g_bHasShot = true;
				return;
			}
		}
		else if (!g_abKeyPressed[K_SHOOTUP] && !g_abKeyPressed[K_SHOOTDOWN])
		{
			if (g_abKeyPressed[K_SHOOTLEFT] && !g_abKeyPressed[K_SHOOTRIGHT])
			{
				COORD c = g_sChar.m_cLocation;
				c.Y--;
				g_sLevel.g_sEntities.m_vPellets.push_back(SPellet(&c, 6));
				g_bHasShot = true;
				return;
			}
			else if (!g_abKeyPressed[K_SHOOTLEFT] && g_abKeyPressed[K_SHOOTRIGHT])
			{
				COORD c = g_sChar.m_cLocation;
				c.Y++;
				g_sLevel.g_sEntities.m_vPellets.push_back(SPellet(&c, 2));
				g_bHasShot = true;
				return;
			}
		}
		g_adBounceTime[K_SHOOTUP] = g_dElapsedTime;
	}
}

void renderLevel()
{
	// Start from offset of 1,1
	COORD c;
	c.X = 1;
	c.Y = 1;

	// Go through each character inside level and print its respective character
	for (unsigned int row = 0; row < 1 + (ROOM_X + 1) * GRID_X; row++)
	{
		for (unsigned int column = 0; column < g_sLevel.level[row].length(); column++)
		{
			switch (g_sLevel.level[row][column])
			{
			case '#':
				c.X = 1 + (column << 1);
				g_Console.writeToBuffer(c, "  ", 0x80);
				break;
			case '$':
				c.X = 1 + (column << 1);
				g_Console.writeToBuffer(c, "  ", 0x40);
				break;
			}
		}
		c.Y++;
	}
}

void renderPellets()
{
	for (auto& pellet : g_sLevel.g_sEntities.m_vPellets)
	{
		g_Console.writeToBuffer(pellet.getRealCoords(), "<>", 0x03);
	}
}

COORD SGameChar::getRealCoords()
{
	COORD c = this->m_cLocation;
	std::swap(c.X, c.Y);
	c.X = (c.X << 1) + 1;
	c.Y += 1;
	return c;
}

SGameChar::SGameChar()
{
}

void renderStat()
{
	//Rendering player's HP
	COORD c;
	std::ostringstream ss;
	ss.str("");
	ss << "HP: " << g_sChar.m_iPlayerHealth;
	c.X = g_Console.getConsoleSize().X - 9;
	c.Y = 2;
	g_Console.writeToBuffer(c, ss.str());

	//Rendering player's score
	ss.str("");
	ss << "Damage: " << g_sChar.m_iPlayerDamage;
	c.Y = 3;
	g_Console.writeToBuffer(c, ss.str());

	//Rendering player's score
	ss.str("");
	ss << "Score: " << g_sChar.m_iPlayerScore;
	c.Y = 4;
	g_Console.writeToBuffer(c, ss.str());
}
