// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <sstream>

double	g_dElapsedTime;
double	g_dDeltaTime;
int		g_iCurrentFrameCount, g_iLastFrameCount, g_iLastMeasuredSecond;
double	g_dAccurateElapsedTime;
bool	g_abKeyPressed[K_COUNT];
COORD	r_cRenderOffset; // To be used for level rendering, tile coordinates
COORD	r_curspos;
int		r_iMoveDirection;
double	r_dMoveTime;

// Game specific variables here
EGAMESTATES			g_eGameState = S_SPLASHSCREEN;
SLevel				g_sLevel;
SaveDataStorage		saveDataStorage;
SAllEntities		g_sEntities; // Hold all entities in the level
double				g_adBounceTime[K_COUNT]; // this is to prevent key bouncing, so we won't trigger keypresses more than once

bool g_bHasShot;
bool g_bHasWeapon;

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
	if (DEBUG) g_eGameState = S_MENU;

	g_bHasShot = false;
	g_sEntities.g_sChar.m_cLocation.X = 2 + (GRID_X >> 1) * (ROOM_X + 2) + (ROOM_X >> 1);
	g_sEntities.g_sChar.m_cLocation.Y = 2 + (GRID_Y >> 1) * (ROOM_Y + 2) + (ROOM_Y >> 1);
	g_sLevel.playerStartRoom.X = GRID_X >> 1;
	g_sLevel.playerStartRoom.Y = GRID_Y >> 1;
	g_sEntities.g_sChar.m_cRoom = g_sLevel.playerStartRoom;
	r_cRenderOffset.X = 1 + g_sEntities.g_sChar.m_cRoom.X * (ROOM_X + 2);
	r_cRenderOffset.Y = 1 + g_sEntities.g_sChar.m_cRoom.Y * (ROOM_Y + 2);
	r_curspos.X = g_Console.getConsoleSize().X >> 1;
	r_curspos.Y = g_Console.getConsoleSize().Y >> 1;
	g_sLevel.generateLevel();
	g_sLevel.floor = 1;
	COORD c;
	c.X = (GRID_X >> 1) * (ROOM_X + 2) + (ROOM_X >> 1);
	c.Y = 2 + (GRID_Y >> 1) * (ROOM_Y + 2) + (ROOM_Y >> 1);
	g_sEntities.m_vEnemy.push_back(std::move(std::unique_ptr<EnemyRanged> (new EnemyRanged(&g_sEntities.m_vPellets, "Test", "tt", c, (WORD)0x09, 10, 0.4, 0.3, 0.1, 0.3, false, 0.25))));
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");
	g_LoadFromSave(saveDataStorage.g_iSaveData);
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
		case S_MENU: mainMenu();
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
		case S_MENU: renderMainMenu();
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
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
	if (g_dAccurateElapsedTime > 3.0) // wait for 3 seconds to switch to game mode, else do nothing
		g_eGameState = S_MENU;
}

void mainMenu()
{
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
	menuNavigate();
	//g_eGameState = S_GAME;
}

void gameplay()            // gameplay logic
{
	processUserInput();	// checks if you should change states or do something else with the game, e.g. pause, exit
	controlPlayer();	// moves the character, collision detection, physics, etc
	playerShoot();
	g_sEntities.updatePellets();
	g_sEntities.updateEnemies();
					// sound can be played here too.
}

void menuNavigate()
{

}

void resetLevel(int floor)
{
	g_sLevel.playerStartRoom = g_sLevel.exitRoom;
	g_sLevel.generateLevel();
}

void controlPlayer()
{
	bool bSomethingHappened = false;

	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
	if (g_abKeyPressed[K_UP] && g_sEntities.g_sChar.m_cLocation.X > 0 && g_adBounceTime[K_UP] < g_dElapsedTime)
	{
		g_sEntities.g_sChar.m_cLocation.X--;
		if (g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) == '#')
		{
			g_sEntities.g_sChar.m_cLocation.X++;
		}
		else
		{
			bSomethingHappened = true;
			if (g_sEntities.g_sChar.m_cLocation.X < r_cRenderOffset.X)
			{
				r_cRenderOffset.X -= (ROOM_X + 2);
				g_sEntities.clearPellets();
			}
		}
    }
    if (g_abKeyPressed[K_LEFT] && g_sEntities.g_sChar.m_cLocation.Y > 0 && g_adBounceTime[K_LEFT] < g_dElapsedTime)
    {
		g_sEntities.g_sChar.m_cLocation.Y--;
		if (g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) == '#')
		{
			g_sEntities.g_sChar.m_cLocation.Y++;
		}
		else
		{
			bSomethingHappened = true;
			if (g_sEntities.g_sChar.m_cLocation.Y < r_cRenderOffset.Y)
			{
				r_cRenderOffset.Y -= (ROOM_Y + 2);
				g_sEntities.clearPellets();
			}
		}
    }
    if (g_abKeyPressed[K_DOWN] && g_adBounceTime[K_DOWN] < g_dElapsedTime)
    {
		g_sEntities.g_sChar.m_cLocation.X++;
		if (g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) == '#')
		{
			g_sEntities.g_sChar.m_cLocation.X--;
		}
		else
		{
			bSomethingHappened = true;
			if (g_sEntities.g_sChar.m_cLocation.X >= r_cRenderOffset.X + ROOM_X + 2)
			{
				r_cRenderOffset.X += (ROOM_X + 2);
				g_sEntities.clearPellets();
			}
		}
    }
    if (g_abKeyPressed[K_RIGHT] && g_adBounceTime[K_RIGHT] < g_dElapsedTime)
    {
		g_sEntities.g_sChar.m_cLocation.Y++;
		if (g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) == '#')
		{
			g_sEntities.g_sChar.m_cLocation.Y--;
		}
		else
		{
			bSomethingHappened = true;
			if (g_sEntities.g_sChar.m_cLocation.Y >= r_cRenderOffset.Y + ROOM_Y + 2)
			{
				r_cRenderOffset.Y += (ROOM_Y + 2);
				g_sEntities.clearPellets();
			}
		}
    }
    if (g_abKeyPressed[K_SPACE] && g_adBounceTime[K_SPACE] < g_dElapsedTime)
    {
		if (g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) == '&')
		{
			resetLevel(++g_sLevel.floor);
			bSomethingHappened = true;
		}
		if (g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) == '%') //When spacebar is pressed when on top of item
		{
			g_sEntities.g_sChar.AddItem(true);
		}
    }

	if (bSomethingHappened)
	{
		for (int i = 0; i <= K_RIGHT; i++)
		{
			if (g_abKeyPressed[i])
			{
				g_adBounceTime[i] = g_dElapsedTime + 0.225;
				if (g_sEntities.g_sChar.m_sPlayerItems.m_vItemsList[6].m_bHasWeapon) // Index 7 (Blue Feather): Decrease movement delay by 10/20/30/40%
				{
					switch (g_sEntities.g_sChar.m_sPlayerItems.m_vItemsList[6].m_iWeaponLevel)
					{
					case 1:
						{
							g_adBounceTime[i] *= g_sEntities.g_sChar.m_sPlayerItems.m_vItemsList[6].m_fweaponMovementSpeed;
							break;
						}
					case 2:
						{
							g_adBounceTime[i] *= (g_sEntities.g_sChar.m_sPlayerItems.m_vItemsList[6].m_fweaponMovementSpeed - 0.1);
							break;
						}
					case 3:
						{
							g_adBounceTime[i] *= (g_sEntities.g_sChar.m_sPlayerItems.m_vItemsList[6].m_fweaponMovementSpeed - 0.2);
							break;
						}
					case 4:
						{
							g_adBounceTime[i] *= (g_sEntities.g_sChar.m_sPlayerItems.m_vItemsList[6].m_fweaponMovementSpeed - 0.3);
							break;
						}
					}
				}
			}
		}
		if (g_abKeyPressed[K_SPACE]) g_adBounceTime[K_SPACE] = g_dElapsedTime + 0.225;
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
	g_Console.clearBuffer(0x0f);
}

void renderSplashScreen()  // renders the splash screen
{
	COORD c = g_Console.getConsoleSize();
	c.Y /= 3;
	c.X = g_Console.getConsoleSize().X / 2 - 20;
	g_Console.writeToBuffer(c, "A game in 3 seconds", 0x03);
	c.Y += 1;
	g_Console.writeToBuffer(c, "Press WASD to move the character", 0x09);
	c.Y += 1;
	g_Console.writeToBuffer(c, "Press Arrow keys to shoot", 0x09);
	c.Y += 1;
	g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);
}

void renderMainMenu()
{
	renderTitle();
	renderMenu();
	renderScore();
	renderCursor();
}

void renderGame()
{
	renderLevel();
	renderCharacter();    // renders the character into the buffer
	renderPellets();
	renderEnemy();
	renderStat();
}

void renderTitle()
{
	std::string ASCII[7];
	ASCII[0] = " ÛÛÛÛÛÛÛÛ²°           ÛÛÛÛÛÛ²°                     ÛÛÛÛÛÛÛÛ²°                                   ";
	ASCII[1] = " Û²°ÛÛ²°Û²°          ÛÛ²°  ÛÛ²°                     ÛÛ²°  Û²°                                   ";
	ASCII[2] = "    ÛÛ²° Û²°Û²ÛÛÛÛ²  ÛÛ²°     ÛÛÛ² ÛÛÛÛ²°ÛÛ²°ÛÛÛÛ   ÛÛ²°     ÛÛÛ²°ÛÛÛ²°ÛÛ²° ÛÛ²° ÛÛ²°ÛÛÛ²°ÛÛÛÛ²°";
	ASCII[3] = "    ÛÛ²° Û²°Û²Û²°    ÛÛ²°     Û²°Û²Û²°  Û²°Û² Û     ÛÛÛÛÛÛ²°Û²°  Û²°  Û²°Û²Û²°Û²Û²°Û²Û²°Û²Û²°   ";
	ASCII[4] = "    ÛÛ²° ÛÛÛÛ²ÛÛÛ²°  ÛÛ²° ÛÛÛ²ÛÛÛÛ²ÛÛÛ²°ÛÛÛÛ² Û     ÛÛ²°     ÛÛ²°Û²°  ÛÛÛÛ²ÛÛÛ²°ÛÛÛÛ²Û²°Û²ÛÛÛ²° ";
	ASCII[5] = "    ÛÛ²° Û²°Û²Û²°    ÛÛ²°  ÛÛ²Û²Û² Û²°  Û²°Û² Û     ÛÛ²°  Û²°  Û²Û²°  Û²°Û²Û²°  Û²°Û²Û²°Û²Û²°   ";
	ASCII[6] = "   ÛÛÛÛ²°Û²°Û²ÛÛÛÛ²   ÛÛÛÛÛÛ²°Û² Û²ÛÛÛÛ²Û²°Û² Û    ÛÛÛÛÛÛÛÛ²ÛÛÛ²° ÛÛÛ²Û²°Û²Û²°  Û²°Û²ÛÛÛ² ÛÛÛÛ²°";
	COORD c = g_Console.getConsoleSize();
	c.X *= 0.025;
	for (int i = 0; i < 7; i++)
	{
		c.Y = 2 + i;
		g_Console.writeToBuffer(c, ASCII[i], 0x64);
	}
}

void renderScore() 
{
	/*Label*/
	unsigned int LoadedScore = saveDataStorage.g_iSaveData[0];
	std::string g_sScore = std::to_string(LoadedScore);
	COORD c = g_Console.getConsoleSize();
	c.X -= g_sScore.length();
	c.Y -= 1;
	g_Console.writeToBuffer(c, g_sScore, 0x0f);
	c.X -= 7;
	g_Console.writeToBuffer(c, "Score: ", 0x0f);
}

void renderMenu()
{
	COORD c = g_Console.getConsoleSize();
	c.X >>= 1;
	c.Y >>= 1;
	g_Console.writeToBuffer(c, "Selection", 0x0f);
}

void renderCursor()
{
	COORD c = r_curspos;
	g_Console.writeToBuffer(c, ">", 0x0f);
}

void renderCharacter()
{
	// Draw the location of the character
	WORD charColor = 0x0A;
	g_Console.writeToBuffer(g_sEntities.g_sChar.getRealCoords(), "@@", charColor);
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
	double delay;

	if (g_sEntities.g_sChar.m_sPlayerItems.m_vItemsList[4].m_bHasWeapon)
	{
		switch (g_sEntities.g_sChar.m_sPlayerItems.m_vItemsList[4].m_iWeaponLevel) // Index 5 (Magic Potion): Decrease attack delay by 10/20/30/40%
		{
		case 1:
			{
				delay = SHOOTSPEED * 0.90;
				break;
			}
		case 2:
			{
				delay = SHOOTSPEED * 0.80;
				break;
			}
		case 3:
			{
				delay = SHOOTSPEED * 0.70;
				break;
			}
		case 4:
			{
				delay = SHOOTSPEED * 0.60;
				break;
			}
		}
	}
	else
	{
		delay = SHOOTSPEED;
	}

	if ((g_abKeyPressed[K_SHOOTDOWN] || g_abKeyPressed[K_SHOOTLEFT] || g_abKeyPressed[K_SHOOTRIGHT] || g_abKeyPressed[K_SHOOTUP]) && (g_adBounceTime[K_SHOOTUP] >= g_dElapsedTime + (delay - 0.025) || g_adBounceTime[K_SHOOTUP] < g_dElapsedTime))
	{
		g_bHasShot = false;
		if (g_adBounceTime[K_SHOOTUP] < g_dElapsedTime)
		{
			g_adBounceTime[K_SHOOTUP] = g_dElapsedTime + delay;
			
		}
	}
	else if (!g_bHasShot && g_adBounceTime[K_SHOOTUP] >= g_dElapsedTime && g_adBounceTime[K_SHOOTUP] < g_dElapsedTime + (delay - 0.025))
	{
		if (g_abKeyPressed[K_SHOOTUP] && !g_abKeyPressed[K_SHOOTDOWN])
		{
			if (g_abKeyPressed[K_SHOOTLEFT] && !g_abKeyPressed[K_SHOOTRIGHT])
			{
				COORD c = g_sEntities.g_sChar.m_cLocation;
				c.X--;
				c.Y--;
				g_sEntities.m_vPellets.push_back(SPellet(&c, 7, SHOOTVELOCITY, true));
				g_bHasShot = true;
				return;
			}
			else if (!g_abKeyPressed[K_SHOOTLEFT] && g_abKeyPressed[K_SHOOTRIGHT])
			{
				COORD c = g_sEntities.g_sChar.m_cLocation;
				c.X--;
				c.Y++;
				g_sEntities.m_vPellets.push_back(SPellet(&c, 1, SHOOTVELOCITY, true));
				g_bHasShot = true;
				return;
			}
			else if (!g_abKeyPressed[K_SHOOTLEFT] && !g_abKeyPressed[K_SHOOTRIGHT])
			{
				COORD c = g_sEntities.g_sChar.m_cLocation;
				c.X--;
				g_sEntities.m_vPellets.push_back(SPellet(&c, 0, SHOOTVELOCITY, true));
				g_bHasShot = true;
				return;
			}
		}
		else if (!g_abKeyPressed[K_SHOOTUP] && g_abKeyPressed[K_SHOOTDOWN])
		{
			if (g_abKeyPressed[K_SHOOTLEFT] && !g_abKeyPressed[K_SHOOTRIGHT])
			{
				COORD c = g_sEntities.g_sChar.m_cLocation;
				c.X++;
				c.Y--;
				g_sEntities.m_vPellets.push_back(SPellet(&c, 5, SHOOTVELOCITY, true));
				g_bHasShot = true;
				return;
			}
			else if (!g_abKeyPressed[K_SHOOTLEFT] && g_abKeyPressed[K_SHOOTRIGHT])
			{
				COORD c = g_sEntities.g_sChar.m_cLocation;
				c.X++;
				c.Y++;
				g_sEntities.m_vPellets.push_back(SPellet(&c, 3, SHOOTVELOCITY, true));
				g_bHasShot = true;
				return;
			}
			else if (!g_abKeyPressed[K_SHOOTLEFT] && !g_abKeyPressed[K_SHOOTRIGHT])
			{
				COORD c = g_sEntities.g_sChar.m_cLocation;
				c.X++;
				g_sEntities.m_vPellets.push_back(SPellet(&c, 4, SHOOTVELOCITY, true));
				g_bHasShot = true;
				return;
			}
		}
		else if (!g_abKeyPressed[K_SHOOTUP] && !g_abKeyPressed[K_SHOOTDOWN])
		{
			if (g_abKeyPressed[K_SHOOTLEFT] && !g_abKeyPressed[K_SHOOTRIGHT])
			{
				COORD c = g_sEntities.g_sChar.m_cLocation;
				c.Y--;
				g_sEntities.m_vPellets.push_back(SPellet(&c, 6, SHOOTVELOCITY, true));
				g_bHasShot = true;
				return;
			}
			else if (!g_abKeyPressed[K_SHOOTLEFT] && g_abKeyPressed[K_SHOOTRIGHT])
			{
				COORD c = g_sEntities.g_sChar.m_cLocation;
				c.Y++;
				g_sEntities.m_vPellets.push_back(SPellet(&c, 2, SHOOTVELOCITY, true));
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

	if (DEBUG)
	{
		for (int row = r_cRenderOffset.X; row < r_cRenderOffset.X + ROOM_X + 2; row++)
		{
			for (int column = r_cRenderOffset.Y; column < r_cRenderOffset.Y + ROOM_Y + 2; column++)
			{
				switch (g_sLevel.level[row][column])
				{
				case '#':
					c.X = 1 + ((column - r_cRenderOffset.Y) << 1);
					g_Console.writeToBuffer(c, "  ", 0x80);
					break;
				case '$':
					c.X = 1 + ((column - r_cRenderOffset.Y) << 1);
					g_Console.writeToBuffer(c, "  ", 0x40);
					break;
				case '&':
					c.X = 1 + ((column - r_cRenderOffset.Y) << 1);
					g_Console.writeToBuffer(c, "&_", 0x09);
					break;
				}
			}
			c.Y++;
		}
	}
	else
	{
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
}

void renderPellets()
{
	for (auto& pellet : g_sEntities.m_vPellets)
	{
		if (!pellet.m_bFriendly) continue;
		g_Console.writeToBuffer(pellet.getRealCoords(), "<>", 0x03);
	}
	for (auto& pellet : g_sEntities.m_vPellets)
	{
		if (pellet.m_bFriendly) continue;
		g_Console.writeToBuffer(pellet.getRealCoords(), "<>", 0x0C);
	}
}

void renderEnemy()
{
	for (auto& enemy : g_sEntities.m_vEnemy)
	{
		g_Console.writeToBuffer(enemy->getRealLocation(), enemy->getIdentifier(), enemy->getColor());
	}
}

void renderStat()
{
	//Rendering player's HP
	COORD c;
	std::ostringstream ss;
	ss.str("");
	ss << "HP: " << g_sEntities.g_sChar.m_iPlayerHealth;
	c.X = g_Console.getConsoleSize().X - 9;
	c.Y = 2;
	g_Console.writeToBuffer(c, ss.str());

	//Rendering player's damage
	ss.str("");
	ss << "Damage: " << g_sEntities.g_sChar.m_iPlayerDamage;
	c.Y = 3;
	g_Console.writeToBuffer(c, ss.str());

	//Rendering player's damage
	ss.str("");
	ss << "Items: " << g_sEntities.g_sChar.m_sPlayerItems.ItemCount;
	c.Y = 4;
	g_Console.writeToBuffer(c, ss.str());

	//Rendering player's score
	ss.str("");
	ss << "Score: " << g_sEntities.g_sChar.m_iPlayerScore;
	c.Y = 5;
	g_Console.writeToBuffer(c, ss.str());

	//Rendering floor level
	ss.str("");
	ss << "Floor: " << g_sLevel.floor;
	c.Y = 6;
	g_Console.writeToBuffer(c, ss.str());
}

