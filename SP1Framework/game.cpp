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

int		r_iMoveDirection;
double	r_dMoveTime;

// Console object
Console g_Console(120, 30, "The Great Escapade");

// Game specific variables here
EGAMESTATES			g_eGameState = S_SPLASHSCREEN;
SLevel				g_sLevel;
SaveDataStorage		saveDataStorage;
SAllEntities		g_sEntities; // Hold all entities in the level
MenuEvent			g_mEvent(&g_Console);
double				g_adBounceTime[K_COUNT]; // this is to prevent key bouncing, so we won't trigger keypresses more than once

bool g_bHasShot;
bool g_bHasWeapon;

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
	//if (DEBUG) g_sEntities.g_sChar.m_bInBattle = true;
	r_cRenderOffset.X = 1 + g_sEntities.g_sChar.m_cRoom.X * (ROOM_X + 2);
	r_cRenderOffset.Y = 1 + g_sEntities.g_sChar.m_cRoom.Y * (ROOM_Y + 2);
	g_mEvent.r_curspos.X = g_Console.getConsoleSize().X / 5;
	g_mEvent.r_curspos.Y = g_Console.getConsoleSize().Y / 10 * 8;
	g_sLevel.floor = 1;
	g_sLevel.generateLevel();
	g_sLevel.miniMap->refresh(g_sEntities.g_sChar.m_cLocation);
	COORD c;
	c.X = (GRID_X >> 1) * (ROOM_X + 2) + (ROOM_X >> 1);
	c.Y = 2 + (GRID_Y >> 1) * (ROOM_Y + 2) + (ROOM_Y >> 1);
	//addEnemy(UNIQUE_ENEMY_MELEETEST);
	//addEnemy(UNIQUE_ENEMY_RANGEDTEST);
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
	HWND currentWindow = GetForegroundWindow();
	if (currentWindow == g_Console.consoleWindow)
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
		g_abKeyPressed[K_ENTER] = isKeyPressed(VK_RETURN);
	}
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
		case S_HOWTOPLAY: tutorial();
			break;
		case S_SHOP: shop();
			break;
		case S_OPTIONS: options();
			break;
		case S_CREDITS: credits();
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
	clearScreen();		// clears the current screen and draw from scratch 
	switch (g_eGameState)
	{
		case S_SPLASHSCREEN: renderSplashScreen();
			break;
		case S_MENU: renderMainMenu();
			break;
		case S_HOWTOPLAY: renderTutorial();
			break;
		case S_SHOP: renderShop();
			break;
		case S_OPTIONS: renderOptions();
			break;
		case S_CREDITS: renderCredits();
			break;
		case S_GAME: renderGame();
			break;
	}
    renderFramerate();	// renders debug information, frame rate, elapsed time, etc
    renderToScreen();	// dump the contents of the buffer to the screen, one frame worth of game
	
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

void splashScreenWait()		// waits for time to pass in splash screen
{
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
	if (g_dAccurateElapsedTime > 3.0) // wait for 3 seconds to switch to game mode, else do nothing
		g_eGameState = S_MENU;
}

void mainMenu()
{
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
	menuNavigate();
	processMenuEvent();
}

void tutorial()
{
	goBack();
	processMenuEvent();
}

void shop()
{
	processUserInput();
}

void options()
{
	doomButton();
	processOptionsEvent();
}

void credits()
{
	goBack();
	processMenuEvent();
}

void gameplay()            // gameplay logic
{
	processUserInput();	// checks if you should change states or do something else with the game, e.g. pause, exit
	controlPlayer();	// moves the character, collision detection, physics, etc
	playerShoot(); // checks if the player should shoot
	g_sEntities.updatePellets(); // update locations of pellets
	checkHitPellets(); // checks if the pellets have hit anything, and update stats accordingly
	g_sEntities.updateEnemies(); // update locations of enemies and add pellets of the enemies'
	// sound can be played here too.
}

void menuNavigate()
{
	bool KeyPressed = false;
	if (g_abKeyPressed[K_SHOOTUP] && g_mEvent.sh_cursSel > 0 && g_adBounceTime[K_SHOOTUP] < g_dElapsedTime)
	{
		g_mEvent.sh_cursSel--;
		g_mEvent.r_curspos.Y--;
		KeyPressed = true;
	}
	else if (g_abKeyPressed[K_SHOOTDOWN] && g_mEvent.sh_cursSel < 4 && g_adBounceTime[K_SHOOTDOWN] < g_dElapsedTime)
	{
		g_mEvent.sh_cursSel++;
		g_mEvent.r_curspos.Y++;
		KeyPressed = true;
	}
	if (g_abKeyPressed[K_ENTER] && g_mEvent.bHasPressedButton == false)
	{
		switch (g_mEvent.sh_cursSel)
		{
		case 0:
			g_mEvent.bStartGame = true;
			break;
		case 1:
			g_mEvent.bHowToPlay = true;
			break;
		case 2:
			g_mEvent.bShop = true;
			break;
		case 3:
			g_mEvent.bOptions = true;
			break;
		case 4:
			g_mEvent.bCredits = true;
		default:
			break;
		}
	}
	if (KeyPressed)
	{
		if (g_abKeyPressed[K_SHOOTUP])
			g_adBounceTime[K_SHOOTUP] = g_dElapsedTime + 0.125;
		if (g_abKeyPressed[K_SHOOTDOWN]) 
			g_adBounceTime[K_SHOOTDOWN] = g_dElapsedTime + 0.125;
	}
}

void goBack()
{
	if (g_abKeyPressed[K_ENTER] == true || g_abKeyPressed[K_ESCAPE] == true)
	{
		g_mEvent.bMenu = true;
		g_mEvent.uiCreditsRollTime = 0;
	}
}

void resetLevel(int floor)
{
	g_sLevel.playerStartRoom = g_sLevel.exitRoom;
	g_sLevel.generateLevel();
	g_sLevel.miniMap->refresh(g_sEntities.g_sChar.m_cLocation);
}

void controlPlayer()
{
	bool bSomethingHappened = false;

	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
	if (g_abKeyPressed[K_UP] && g_sEntities.g_sChar.m_cLocation.X > 0 && g_adBounceTime[K_UP] < g_dElapsedTime)
	{
		g_sEntities.g_sChar.m_cLocation.X--;
		if (g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != ' ' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '&' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '\0' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '%' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '1' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '2' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '3' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '4' &&
			(g_sEntities.g_sChar.m_bInBattle || g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '$'))
		{
			g_sEntities.g_sChar.m_cLocation.X++;
		}
		else
		{
			bool skip = false;

			for (auto& enemy : g_sEntities.m_vEnemy)
			{
				if (g_sEntities.g_sChar.m_cLocation.X == enemy->getLocation().X && g_sEntities.g_sChar.m_cLocation.Y == enemy->getLocation().Y)
				{
					skip = true;
					g_sEntities.g_sChar.m_cLocation.X++;
					break;
				}
			}
			if (!skip)
			{
				bSomethingHappened = true;
				if (g_sEntities.g_sChar.m_cLocation.X < r_cRenderOffset.X)
				{
					r_cRenderOffset.X -= (ROOM_X + 2);
					g_sEntities.g_sChar.m_cLocation.X--;
					g_sEntities.clearPellets();
					g_sEntities.clearEnemies();
					if (loadEnemiesFromRoom())
						g_sEntities.g_sChar.m_bInBattle = true;
					g_sLevel.miniMap->enteredRoom[(g_sEntities.g_sChar.m_cLocation.X - 1) / (ROOM_X + 2) * GRID_Y + (g_sEntities.g_sChar.m_cLocation.Y - 1) / (ROOM_Y + 2)] = true;
					g_sLevel.miniMap->refresh(g_sEntities.g_sChar.m_cLocation);
				}
			}
		}
    }
    if (g_abKeyPressed[K_LEFT] && g_sEntities.g_sChar.m_cLocation.Y > 0 && g_adBounceTime[K_LEFT] < g_dElapsedTime)
    {
		g_sEntities.g_sChar.m_cLocation.Y--;
		if (g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != ' ' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '&' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '\0' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '%' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '1' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '2' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '3' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '4' &&
			(g_sEntities.g_sChar.m_bInBattle || g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '$'))
		{
			g_sEntities.g_sChar.m_cLocation.Y++;
		}
		else
		{
			bool skip = false;

			for (auto& enemy : g_sEntities.m_vEnemy)
			{
				if (g_sEntities.g_sChar.m_cLocation.X == enemy->getLocation().X && g_sEntities.g_sChar.m_cLocation.Y == enemy->getLocation().Y)
				{
					skip = true;
					g_sEntities.g_sChar.m_cLocation.Y++;
					break;
				}
			}
			if (!skip)
			{
				bSomethingHappened = true;
				if (g_sEntities.g_sChar.m_cLocation.Y < r_cRenderOffset.Y)
				{
					r_cRenderOffset.Y -= (ROOM_Y + 2);
					g_sEntities.g_sChar.m_cLocation.Y--;
					g_sEntities.clearPellets();
					g_sEntities.clearEnemies();
					if (loadEnemiesFromRoom())
						g_sEntities.g_sChar.m_bInBattle = true;
					g_sLevel.miniMap->enteredRoom[(g_sEntities.g_sChar.m_cLocation.X - 1) / (ROOM_X + 2) * GRID_Y + (g_sEntities.g_sChar.m_cLocation.Y - 1) / (ROOM_Y + 2)] = true;
					g_sLevel.miniMap->refresh(g_sEntities.g_sChar.m_cLocation);
				}
			}
		}
    }
    if (g_abKeyPressed[K_DOWN] && g_adBounceTime[K_DOWN] < g_dElapsedTime)
    {
		g_sEntities.g_sChar.m_cLocation.X++;
		if (g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != ' ' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '&' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '\0' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '%' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '1' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '2' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '3' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '4' &&
			(g_sEntities.g_sChar.m_bInBattle || g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '$'))
		{
			g_sEntities.g_sChar.m_cLocation.X--;
		}
		else
		{
			bool skip = false;

			for (auto& enemy : g_sEntities.m_vEnemy)
			{
				if (g_sEntities.g_sChar.m_cLocation.X == enemy->getLocation().X && g_sEntities.g_sChar.m_cLocation.Y == enemy->getLocation().Y)
				{
					skip = true;
					g_sEntities.g_sChar.m_cLocation.X--;
					break;
				}
			}
			if (!skip)
			{
				bSomethingHappened = true;
				if (g_sEntities.g_sChar.m_cLocation.X >= r_cRenderOffset.X + ROOM_X + 2)
				{
					r_cRenderOffset.X += (ROOM_X + 2);
					g_sEntities.g_sChar.m_cLocation.X++;
					g_sEntities.clearPellets();
					g_sEntities.clearEnemies();
					if (loadEnemiesFromRoom())
						g_sEntities.g_sChar.m_bInBattle = true;
					g_sLevel.miniMap->enteredRoom[(g_sEntities.g_sChar.m_cLocation.X - 1) / (ROOM_X + 2) * GRID_Y + (g_sEntities.g_sChar.m_cLocation.Y - 1) / (ROOM_Y + 2)] = true;
					g_sLevel.miniMap->refresh(g_sEntities.g_sChar.m_cLocation);
				}
			}
		}
    }
    if (g_abKeyPressed[K_RIGHT] && g_adBounceTime[K_RIGHT] < g_dElapsedTime)
    {
		g_sEntities.g_sChar.m_cLocation.Y++;
		if (g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != ' ' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '&' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '\0' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '%' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '1' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '2' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '3' &&
			g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '4' &&
			(g_sEntities.g_sChar.m_bInBattle || g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation) != '$'))
		{
			g_sEntities.g_sChar.m_cLocation.Y--;
		}
		else
		{
			bool skip = false;

			for (auto& enemy : g_sEntities.m_vEnemy)
			{
				if (g_sEntities.g_sChar.m_cLocation.X == enemy->getLocation().X && g_sEntities.g_sChar.m_cLocation.Y == enemy->getLocation().Y)
				{
					skip = true;
					g_sEntities.g_sChar.m_cLocation.Y--;
					break;
				}
			}
			if (!skip)
			{
				bSomethingHappened = true;
				if (g_sEntities.g_sChar.m_cLocation.Y >= r_cRenderOffset.Y + ROOM_Y + 2)
				{
					r_cRenderOffset.Y += (ROOM_Y + 2);
					g_sEntities.g_sChar.m_cLocation.Y++;
					g_sEntities.clearPellets();
					g_sEntities.clearEnemies();
					if (loadEnemiesFromRoom())
						g_sEntities.g_sChar.m_bInBattle = true;
					g_sLevel.miniMap->enteredRoom[(g_sEntities.g_sChar.m_cLocation.X - 1) / (ROOM_X + 2) * GRID_Y + (g_sEntities.g_sChar.m_cLocation.Y - 1) / (ROOM_Y + 2)] = true;
					g_sLevel.miniMap->refresh(g_sEntities.g_sChar.m_cLocation);
				}
			}
		}
    }
    if (g_abKeyPressed[K_SPACE] && g_adBounceTime[K_SPACE] < g_dElapsedTime)
    {
		switch (g_sLevel.getTile(g_sEntities.g_sChar.m_cLocation))
		{
			case '&':
			{
				resetLevel(++g_sLevel.floor);
				bSomethingHappened = true;
				break;
			}
			case '%': //When spacebar is pressed on top of an item
			{
				g_sEntities.g_sChar.addItem(true);
				COORD c = g_sEntities.g_sChar.m_cLocation;
				g_sLevel.modifyTile(c, '\0');
				break;
			}
			case '1':
			{
				g_sEntities.g_sChar.addConsumable(true, 1);
				COORD c = g_sEntities.g_sChar.m_cLocation;
				g_sLevel.modifyTile(c, '\0');
				break;
			}
			case '2':
			{
				g_sEntities.g_sChar.addConsumable(true, 2);
				COORD c = g_sEntities.g_sChar.m_cLocation;
				g_sLevel.modifyTile(c, '\0');
				break;
			}
			case '3':
			{
				g_sEntities.g_sChar.addConsumable(true, 3);
				COORD c = g_sEntities.g_sChar.m_cLocation;
				g_sLevel.modifyTile(c, '\0');
				break;
			}
			case '4':
			{
				g_sEntities.g_sChar.addConsumable(true, 4);
				COORD c = g_sEntities.g_sChar.m_cLocation;
				g_sLevel.modifyTile(c, '\0');
				break;
			}
		}
		if (g_abKeyPressed[K_SPACE]) g_adBounceTime[K_SPACE] = g_dElapsedTime + 0.250;
    }

	if (bSomethingHappened)
	{
		for (int i = 0; i <= K_RIGHT; i++)
		{
			if (g_abKeyPressed[i])
			{
				g_adBounceTime[i] = g_dElapsedTime + 0.250; //0.250 acts as the movement delay of the player, decreasing it makes the player go faster
				if (g_sEntities.g_sChar.m_sPlayerItems.m_vItemsList[6].m_bHasWeapon) // Index 7 (Blue Feather): Decrease movement delay by 20/30/40/50%
				{
					switch (g_sEntities.g_sChar.m_sPlayerItems.m_vItemsList[6].m_iWeaponLevel)
					{
					case 1: //Blue Feather Level 1: Decrease movement delay by 20%
						{
							g_adBounceTime[i] = g_dElapsedTime + ((g_sEntities.g_sChar.m_sPlayerItems.m_vItemsList[6].m_fweaponMovementSpeed - 0.20) * 0.250);
							break;
						}
					case 2: //Blue Feather Level 2: Decrease movement delay by 30%
						{
						g_adBounceTime[i] = g_dElapsedTime + ((g_sEntities.g_sChar.m_sPlayerItems.m_vItemsList[6].m_fweaponMovementSpeed - 0.30) * 0.250);
							break;
						}
					case 3: //Blue Feather Level 3: Decrease movement delay by 40%
						{
						g_adBounceTime[i] = g_dElapsedTime + ((g_sEntities.g_sChar.m_sPlayerItems.m_vItemsList[6].m_fweaponMovementSpeed - 0.40) * 0.250);
							break;
						}
					case 4: //Blue Feather Level 4: Decrease movement delay by 50%
						{
						g_adBounceTime[i] = g_dElapsedTime + ((g_sEntities.g_sChar.m_sPlayerItems.m_vItemsList[6].m_fweaponMovementSpeed - 0.50) * 0.250);
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

void processMenuEvent()
{
	if (g_mEvent.bHasPressedButton == false)
	{
		if (g_abKeyPressed[K_ENTER] == false)
		{
			if (g_mEvent.bStartGame == true)
			{
				g_eGameState = S_GAME;
				g_mEvent.bStartGame = false;
			}
			if (g_mEvent.bHowToPlay == true)
			{
				g_eGameState = S_HOWTOPLAY;
				g_mEvent.bHowToPlay = false;
			}
			if (g_mEvent.bShop == true)
			{
				g_eGameState = S_SHOP;
				g_mEvent.bShop = false;
			}
			if (g_mEvent.bOptions == true)
			{
				g_eGameState = S_OPTIONS;
				g_mEvent.bOptions = false;
			}
			if (g_mEvent.bMenu == true)
			{
				g_eGameState = S_MENU;
				g_mEvent.bMenu = false;
			}
			if (g_mEvent.bCredits == true)
			{
				g_eGameState = S_CREDITS;
				g_mEvent.bCredits = false;
			}
		}
	}
	else
	{
		if (g_abKeyPressed[K_ENTER] == true)
		{
			g_mEvent.bHasPressedButton = true;
		}
		else
			g_mEvent.bHasPressedButton = false;
	}
}

void doomButton()
{
	if (g_abKeyPressed[K_ENTER] && g_mEvent.sh_optionSel == 0)
	{
		if (g_mEvent.uiActivateDoomButton < 1000)
		{
			g_mEvent.uiActivateDoomButton++;
		}
		else
		{
			g_mEvent.uiActivateDoomButton = 0;
			unsigned int NukedSaveData[9];
			for (int i = 0; i < 9; i++)
			{
				NukedSaveData[i] = 0;
			}
			g_SaveToSave(NukedSaveData);
			g_eGameState = S_MENU;
			g_mEvent.bHasPressedButton = true;
			g_LoadFromSave(saveDataStorage.g_iSaveData);
		}
	}
	else
	{
		g_mEvent.uiActivateDoomButton = 0;
	}
}

void processOptionsEvent()
{
	
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
	g_mEvent.renderTitle();
	g_mEvent.renderMenu();
	g_mEvent.renderCursor();
	renderScore();
}

void renderTutorial()
{
	g_mEvent.renderTutorialDetails();
}

void renderShop()
{
	g_mEvent.renderItemTitleSelected();
	g_mEvent.renderItemPriceSelected();
	g_mEvent.renderItemDescSelected();
}

void renderOptions()
{
	g_mEvent.renderDoomButton();
	if (g_mEvent.sh_optionSel == 0)
	{
		g_mEvent.renderDoomButtonBrackets();
	}
	g_mEvent.renderOtherOptions();
}

void renderCredits()
{
	g_mEvent.renderCreditsRollAnimation();
	g_mEvent.renderCreditsRollText();
}

void renderGame()
{
	renderLevel();
	renderCharacter();    // renders the character into the buffer
	renderEnemy();
	renderPellets();
	renderMiniMap();
	renderStat();
}

void renderScore() 
{
	unsigned int LoadedScore = saveDataStorage.g_iSaveData[0];
	std::string g_sScore = std::to_string(LoadedScore);
	COORD c = g_Console.getConsoleSize();
	c.X -= (SHORT)g_sScore.length();
	c.Y -= 1;
	g_Console.writeToBuffer(c, g_sScore, 0x0f);
	c.X -= 7;
	g_Console.writeToBuffer(c, "Score: ", 0x0f);
}

void renderCharacter()
{
	// Draw the location of the character
	COORD c = g_sEntities.g_sChar.getRealCoords();
	WORD charColor = g_mEvent.wPlayerColor;
	//WORD charColor = 0x0A;
	g_Console.writeToBuffer(c, "@@@@", charColor);
	c.Y++;
	g_Console.writeToBuffer(c, "@@@@", charColor);
}

void renderFramerate()
{
	COORD c;
	// displays the framerate
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(3);
	ss << 1.0 / g_dDeltaTime << "fps";
	c.X = g_Console.getConsoleSize().X - 15;
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
		switch (g_sEntities.g_sChar.m_sPlayerItems.m_vItemsList[4].m_iWeaponLevel) // Index 5 (Magic Potion): Decrease attack delay by 20/30/40/50%
		{
		case 1: //Magic Potion Level 1: Decrease attack delay by 20%
			{
				delay = SHOOTSPEED * (g_sEntities.g_sChar.m_sPlayerItems.m_vItemsList[4].m_fWeaponAttackSpeed - 0.20);
				break;
			}
		case 2: //Magic Potion Level 2: Decrease attack delay by 30%
			{
				delay = SHOOTSPEED * (g_sEntities.g_sChar.m_sPlayerItems.m_vItemsList[4].m_fWeaponAttackSpeed - 0.30);
				break;
			}
		case 3: //Magic Potion Level 3: Decrease attack delay by 40%
			{
				delay = SHOOTSPEED * (g_sEntities.g_sChar.m_sPlayerItems.m_vItemsList[4].m_fWeaponAttackSpeed - 0.40);
				break;
			}
		case 4: //Magic Potion Level 4: Decrease attack delay by 50%
			{
				delay = SHOOTSPEED * (g_sEntities.g_sChar.m_sPlayerItems.m_vItemsList[4].m_fWeaponAttackSpeed - 0.50);
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
				g_sEntities.m_vPellets.push_back(SPellet(&c, 7, g_sEntities.g_sChar.m_iPlayerDamage ,g_sEntities.g_sChar.m_dVelocity, true));
				g_bHasShot = true;
				return;
			}
			else if (!g_abKeyPressed[K_SHOOTLEFT] && g_abKeyPressed[K_SHOOTRIGHT])
			{
				COORD c = g_sEntities.g_sChar.m_cLocation;
				c.X--;
				c.Y++;
				g_sEntities.m_vPellets.push_back(SPellet(&c, 1, g_sEntities.g_sChar.m_iPlayerDamage, g_sEntities.g_sChar.m_dVelocity, true));
				g_bHasShot = true;
				return;
			}
			else if (!g_abKeyPressed[K_SHOOTLEFT] && !g_abKeyPressed[K_SHOOTRIGHT])
			{
				COORD c = g_sEntities.g_sChar.m_cLocation;
				c.X--;
				g_sEntities.m_vPellets.push_back(SPellet(&c, 0, g_sEntities.g_sChar.m_iPlayerDamage, g_sEntities.g_sChar.m_dVelocity, true));
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
				g_sEntities.m_vPellets.push_back(SPellet(&c, 5, g_sEntities.g_sChar.m_iPlayerDamage, g_sEntities.g_sChar.m_dVelocity, true));
				g_bHasShot = true;
				return;
			}
			else if (!g_abKeyPressed[K_SHOOTLEFT] && g_abKeyPressed[K_SHOOTRIGHT])
			{
				COORD c = g_sEntities.g_sChar.m_cLocation;
				c.X++;
				c.Y++;
				g_sEntities.m_vPellets.push_back(SPellet(&c, 3, g_sEntities.g_sChar.m_iPlayerDamage, g_sEntities.g_sChar.m_dVelocity, true));
				g_bHasShot = true;
				return;
			}
			else if (!g_abKeyPressed[K_SHOOTLEFT] && !g_abKeyPressed[K_SHOOTRIGHT])
			{
				COORD c = g_sEntities.g_sChar.m_cLocation;
				c.X++;
				g_sEntities.m_vPellets.push_back(SPellet(&c, 4, g_sEntities.g_sChar.m_iPlayerDamage, g_sEntities.g_sChar.m_dVelocity, true));
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
				g_sEntities.m_vPellets.push_back(SPellet(&c, 6, g_sEntities.g_sChar.m_iPlayerDamage, g_sEntities.g_sChar.m_dVelocity, true));
				g_bHasShot = true;
				return;
			}
			else if (!g_abKeyPressed[K_SHOOTLEFT] && g_abKeyPressed[K_SHOOTRIGHT])
			{
				COORD c = g_sEntities.g_sChar.m_cLocation;
				c.Y++;
				g_sEntities.m_vPellets.push_back(SPellet(&c, 2, g_sEntities.g_sChar.m_iPlayerDamage, g_sEntities.g_sChar.m_dVelocity, true));
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

	for (int row = r_cRenderOffset.X; row < r_cRenderOffset.X + ROOM_X + 2; row++)
	{
		for (int column = r_cRenderOffset.Y; column < r_cRenderOffset.Y + ROOM_Y + 2; column++)
		{
			c.X = 1 + ((column - r_cRenderOffset.Y) << 2);
			switch (g_sLevel.level[row][column])
			{
			case '#':
				switch (g_sLevel.floor)
				{
				case 1:
					render(c, "    ", "    ", 0x80);
					break;
				case 2:
					render(c, "    ", "    ", 0x20);
					break;
				}
				break;
			case '$':
				if (g_sEntities.g_sChar.m_bInBattle)
				{
					render(c, "    ", "    ", 0x40);
				}
				else
				{
					render(c, "    ", "    ", 0x90);
				}
				break;
			case '*':
				render(c, "    ", "    ", 0x70);
				break;
			case '&':
				render(c, "#&  ", "##&_", 0x09);
				break;
			case '%':
				render(c, "    ", "    ", 0x60);
				break;
			case '1':
				render(c, " oo ", " oo ", 0x02);
				break;
			case '2':
				render(c, " OO ", " OO ", 0x02);
				break;
			case '3':
				render(c, " ss ", " ss ", 0x02);
				break;
			case '4':
				render(c, " SS ", " SS ", 0x02);
				break;
			}
		}
		c.Y += 2;
	}
}

void renderMiniMap()
{
	COORD c;
	c.X = g_Console.getConsoleSize().X - ((1 + (GRID_Y << 1)) << 1);
	c.Y = g_Console.getConsoleSize().Y - (1 + (GRID_X << 1));
	if (g_mEvent.bMinimap)
	{
		for (int row = 0; row < (GRID_X << 1) + 1; row++)
		{
			for (int column = 0; column < (GRID_Y << 1) + 1; column++)
			{
				switch (g_sLevel.miniMap->map[row][column])
				{
				case '#':
					g_Console.writeToBuffer(c, "  ", 0x70);
					break;
				case '$':
					g_Console.writeToBuffer(c, "  ", 0x80);
					break;
				case '@':
					g_Console.writeToBuffer(c, "  ", 0x40);
					break;
				case '!':
					g_Console.writeToBuffer(c, "  ", 0x20);
					break;
				case '&':
					g_Console.writeToBuffer(c, "  ", 0x30);
					break;
				}
				c.X += 2;
			}
			c.Y++;
			c.X = g_Console.getConsoleSize().X - ((1 + (GRID_Y << 1)) << 1);
		}
	}
}

void renderPellets()
{
	for (auto& pellet : g_sEntities.m_vPellets)
	{
		if (!pellet.m_bFriendly) continue;
		if (pellet.m_bHit)
		{
			switch (pellet.m_bHitReason)
			{
			case pellet::P_WALL:
				render(pellet.getRealCoords(), PELLET_CHARACTER_HIT_TOP, PELLET_CHARACTER_HIT_BOTTOM, 0x89);
				break;
			case pellet::P_DOOR:
				if (g_sEntities.g_sChar.m_bInBattle)
				{
					render(pellet.getRealCoords(), PELLET_CHARACTER_HIT_TOP, PELLET_CHARACTER_HIT_BOTTOM, 0x49);
				}
				else
				{
					render(pellet.getRealCoords(), PELLET_CHARACTER_HIT_TOP, PELLET_CHARACTER_HIT_BOTTOM, 0x99);
				}
				break;
			case pellet::P_ENEMY:
			case pellet::P_FLOOR:
				render(pellet.getRealCoords(), PELLET_CHARACTER_HIT_TOP, PELLET_CHARACTER_HIT_BOTTOM, 0x09);
				break;
			case pellet::P_ROCK:
				render(pellet.getRealCoords(), PELLET_CHARACTER_HIT_TOP, PELLET_CHARACTER_HIT_BOTTOM, 0x79);
				break;
			}
		}
		else
		{
			render(pellet.getRealCoords(), PELLET_CHARACTER_TOP, PELLET_CHARACTER_BOTTOM, 0x03);
		}
	}
	for (auto& pellet : g_sEntities.m_vPellets)
	{
		if (pellet.m_bFriendly) continue;
		if (pellet.m_bHit)
		{
			switch (pellet.m_bHitReason)
			{
			case pellet::P_WALL:
				render(pellet.getRealCoords(), PELLET_CHARACTER_HIT_TOP, PELLET_CHARACTER_HIT_BOTTOM, 0x84);
				break;
			case pellet::P_DOOR:
				if (g_sEntities.g_sChar.m_bInBattle)
				{
					render(pellet.getRealCoords(), PELLET_CHARACTER_HIT_TOP, PELLET_CHARACTER_HIT_BOTTOM, 0x44);
				}
				else
				{
					render(pellet.getRealCoords(), PELLET_CHARACTER_HIT_TOP, PELLET_CHARACTER_HIT_BOTTOM, 0x94);
				}
				break;
			case pellet::P_PLAYER:
			case pellet::P_FLOOR:
				render(pellet.getRealCoords(), PELLET_CHARACTER_HIT_TOP, PELLET_CHARACTER_HIT_BOTTOM, 0x04);
				break;
			case pellet::P_ROCK:
				render(pellet.getRealCoords(), PELLET_CHARACTER_HIT_TOP, PELLET_CHARACTER_HIT_BOTTOM, 0x74);
				break;
			}
		}
		else
		{
			render(pellet.getRealCoords(), PELLET_CHARACTER_TOP, PELLET_CHARACTER_BOTTOM, 0x0C);
		}
	}
}

void renderEnemy()
{
	for (auto& enemy : g_sEntities.m_vEnemy)
	{
		render(enemy->getRealLocation(), enemy->getIdentifier()[0], enemy->getIdentifier()[1], enemy->getColor());
	}
}

void renderStat()
{
	//Rendering player's HP
	COORD c;
	std::ostringstream ss;
	ss.str("");
	ss << "HP: " << g_sEntities.g_sChar.m_iPlayerHealth << " / " << g_sEntities.g_sChar.m_iMaxHealth;
	c.X = g_Console.getConsoleSize().X - 15;
	c.Y = 2;
	g_Console.writeToBuffer(c, ss.str());

	//Rendering player's damage
	ss.str("");
	ss << "Damage: " << g_sEntities.g_sChar.m_iPlayerDamage;
	c.Y = 3;
	g_Console.writeToBuffer(c, ss.str());

	//Rendering player's item count
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

	//Rendering player's last item
	ss.str("");
	ss << "Last Item: " << g_sEntities.g_sChar.m_sLastItem;
	c.X = g_Console.getConsoleSize().X - 83;
	c.Y = 27;
	g_Console.writeToBuffer(c, ss.str());
}

void checkHitPellets()
{
	for (std::vector<SPellet>::iterator pellet = g_sEntities.m_vPellets.begin(); pellet != g_sEntities.m_vPellets.end(); )
	{
		// Check for erasal
		if (pellet->m_bHit)
		{
			if (pellet->m_dTime >= 0.15)
			{
				pellet = g_sEntities.m_vPellets.erase(pellet);
				continue;
			}
			pellet++;
			continue;
		}


		// Check for exceed lifespan
		if (g_sEntities.g_sChar.m_sPlayerItems.m_vItemsList[0].m_bHasWeapon) //Index 1 (Heaven Cracker): Doubles the pellet lifespan to 5 seconds.
		{
			g_sEntities.g_sChar.m_dRange *= 2; //!Current issue!: if player has weapon, both player and enemy receives the range increase
			if (pellet->m_dLifespan >= g_sEntities.g_sChar.m_dRange)  //Check if the pellet has reached its lifespan of 5 seconds, if it does, clear the pellet and show the "><" hit effect.
			{
				pellet->m_bHit = true;
				pellet->m_bHitReason = pellet::P_FLOOR;
				continue;
			}
		}
		else
		{
			if (pellet->m_dLifespan >= g_sEntities.g_sChar.m_dRange)
			{
				pellet->m_bHit = true;
				pellet->m_bHitReason = pellet::P_FLOOR;
				continue;
			}
		}

		// Check collision with wall
		if ((pellet->m_cLocation.X - 1) % (ROOM_X + 2) == 0 ||
			pellet->m_cLocation.X % (ROOM_X + 2) == 0 ||
			(pellet->m_cLocation.Y - 1) % (ROOM_Y + 2) == 0 ||
			pellet->m_cLocation.Y % (ROOM_Y + 2) == 0)
		{
			if (g_sLevel.getTile(pellet->m_cLocation) == '$')
			{
				pellet->m_bHit = true;
				pellet->m_bHitReason = pellet::P_DOOR;
			}
			else
			{
				pellet->m_bHit = true;
				pellet->m_bHitReason = pellet::P_WALL;
			}
			pellet++;
			continue;
		}

		// Check collision with rock
		if (g_sLevel.getTile(pellet->m_cLocation) == '*')
		{
			pellet->m_bHit = true;
			pellet->m_bHitReason = pellet::P_ROCK;
			pellet++;
			continue;
		}

		// Check collision with player, if enemy pellet
		if (!pellet->m_bFriendly && pellet->m_cLocation.X == g_sEntities.g_sChar.m_cLocation.X && pellet->m_cLocation.Y == g_sEntities.g_sChar.m_cLocation.Y)
		{
			pellet->m_bHit = true;
			pellet->m_bHitReason = pellet::P_PLAYER;
			
			if (g_sEntities.g_sChar.m_sPlayerItems.m_vItemsList[3].m_bHasWeapon) //Index 4 (Glass Canon): All Enemies deal 2/3/4/5 more damage to players.
			{
				switch (g_sEntities.g_sChar.m_sPlayerItems.m_vItemsList[3].m_iWeaponLevel)
				{
					case 1: //Glass Canon Level 1: All Enemies deal 2 more damage to the player
						{
							g_sEntities.g_sChar.m_iPlayerHealth -= (pellet->m_iDamage + 2);
							break;
						}
					case 2: //Glass Canon Level 2: All Enemies deal 3 more damage to the player
						{
							g_sEntities.g_sChar.m_iPlayerHealth -= (pellet->m_iDamage + 3);
							break;
						}
					case 3: //Glass Canon Level 3: All Enemies deal 4 more damage to the player
						{
							g_sEntities.g_sChar.m_iPlayerHealth -= (pellet->m_iDamage + 4);
							break;
						}
					case 4: //Glass Canon Level 4: All Enemies deal 5 more damage to the player
						{
							g_sEntities.g_sChar.m_iPlayerHealth -= (pellet->m_iDamage + 5);
							break;
						}
				}
			}
			else
			{
				g_sEntities.g_sChar.m_iPlayerHealth -= pellet->m_iDamage;
			}
			// TODO: Check for death

			pellet++;
			continue;
		}

		// Check collision with enemy, if player pellet
		if (pellet->m_bFriendly)
		{
			for (auto& enemy : g_sEntities.m_vEnemy)
			{
				if (!enemy->isDying() && !enemy->isDead() && pellet->m_cLocation.X == enemy->getLocation().X && pellet->m_cLocation.Y == enemy->getLocation().Y)
				{
					pellet->m_bHit = true;
					pellet->m_bHitReason = pellet::P_ENEMY;

					enemy->takeDamage(pellet->m_iDamage);

					break;
				}
			}
		}

		pellet++;
	}
}

void render(COORD c, LPCSTR text, LPCSTR text2, WORD color)
{
	g_Console.writeToBuffer(c, text, color);
	c.Y++;
	g_Console.writeToBuffer(c, text2, color);
}

void render(COORD c, std::string& text, std::string& text2, WORD color)
{
	g_Console.writeToBuffer(c, text.c_str(), color);
	c.Y++;
	g_Console.writeToBuffer(c, text2.c_str(), color);
}

bool loadEnemiesFromRoom()
{
	bool roomHasEnemies = false;
	for (int row = r_cRenderOffset.X; row < r_cRenderOffset.X + ROOM_X + 2; row++)
	{
		for (int column = r_cRenderOffset.Y; column < r_cRenderOffset.Y + ROOM_Y + 2; column++)
		{
			COORD c = fastCoord(row, column);
			switch (g_sLevel.level[row][column])
			{
			case 'b':
				addEnemy(UNIQUE_ENEMY_BANDIT);
				roomHasEnemies = true;
				g_sLevel.level[row][column] = ' ';
				break;
			case 'm':
				addEnemy(UNIQUE_ENEMY_MAGE);
				roomHasEnemies = true;
				g_sLevel.level[row][column] = ' ';
				break;
			}
		}
	}
	return roomHasEnemies;
}

void addEnemy(EnemyMelee * enemy)
{
	g_sEntities.m_vEnemy.push_back(std::move(std::unique_ptr<EnemyMelee>(enemy)));
}
void addEnemy(EnemyRanged * enemy)
{
	g_sEntities.m_vEnemy.push_back(std::move(std::unique_ptr<EnemyRanged>(enemy)));
}