// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include "mapInteract.h"
#include "extract.h"
#include "colour.h"
#include "extractscreen.h"
#include "extractfirework.h"
#include "extractfireworks2.h"
#include "levelTransition.h"
#include "Portalgun-teleporting.h"
#include "textBuffer.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT], teleporter = false, gateOpen = false, shotPortal = false, shotPortal2 = false, PortActive1 = false, PortActive2 = false;
bool transisted, shotPortal3 = false, shotPortal4 = false, PortActive3 = false, PortActive4, removeportal = false;

int exscreen;
char over[63][6];
char instruct[58][6];
char fireart[56][12];
char fireart2[56][12];
char clearscreen[60][20];
char splash[59][21];
char mainmenuart[73][12];
char main[63][6];
int splashscreen;
int lvl;
char	healthbar = 219;
char	map[61][21];
char something = '1', thingthing = '1';
int level;
int healthcount = 10;
unsigned char wall = 178;
unsigned char direction, direction2;
unsigned char ground = 176;
unsigned char destination = 177;
unsigned char box = 254;
string	teleport;
string	null = { '\0', };

int teledel = 0;
COORD door;
COORD lever1;
COORD lever2;
COORD portal1;
COORD portal2;
COORD portal3;
COORD portal4;
COORD boxx;


// Game specific variables here
SGameChar	g_sChar;
SGameChar2   g_sChar2;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
portalgun RenderPortal;
Direction Character;
double  g_dBounceTime, g_dBounceTime2;// this is to prevent key bouncing, so we won't trigger keypresses more than once

									  // Console object
Console g_Console(80, 25, "SP1 Framework");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init(void)
{
	// Set precision for floating point output
	g_dElapsedTime = 0.0;
	g_dBounceTime = 0.0;
	g_dBounceTime2 = 0.0;

	// sets the initial state for the game
	g_eGameState = S_SPLASHSCREEN;

	g_sChar.m_cLocation.X = 7;
	g_sChar.m_cLocation.Y = 6;
	g_sChar.m_bActive = true;
	g_sChar2.m_cLocation.X = 7;
	g_sChar2.m_cLocation.Y = 6;
	g_sChar2.m_bActive = true;
	// sets the width, height and the font name to use in the console
	g_Console.setConsoleFont(0, 24, L"Consolas");
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------

void shutdown(void)
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

void getInput(void)
{
	//g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
	//g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
	//g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	//g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[PLAYER_1_K_UP] = isKeyPressed(0x57); //player 1 control
	g_abKeyPressed[PLAYER_1_K_DOWN] = isKeyPressed(0x53);
	g_abKeyPressed[PLAYER_1_K_LEFT] = isKeyPressed(0x41);
	g_abKeyPressed[PLAYER_1_K_RIGHT] = isKeyPressed(0x44);
	g_abKeyPressed[PLAYER_2_K_UP] = isKeyPressed(VK_UP); //PLAYER 2 CONTROL
	g_abKeyPressed[PLAYER_2_K_DOWN] = isKeyPressed(VK_DOWN);
	g_abKeyPressed[PLAYER_2_K_LEFT] = isKeyPressed(VK_LEFT);
	g_abKeyPressed[PLAYER_2_K_RIGHT] = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_RETURN] = isKeyPressed(VK_RETURN);
	g_abKeyPressed[K_BACK] = isKeyPressed(VK_BACK);
	g_abKeyPressed[K_ONE] = isKeyPressed(0x31); // assign the one key
	g_abKeyPressed[K_TWO] = isKeyPressed(0x32); // assign the two key
	g_abKeyPressed[K_THREE] = isKeyPressed(0x33); // assign the three key
	g_abKeyPressed[K_FOUR] = isKeyPressed(0x34); // assign the four key
	g_abKeyPressed[K_FIVE] = isKeyPressed(0x35); // assign the five key
	g_abKeyPressed[K_E] = isKeyPressed(0x45); // assign 'E' key for Player 1 first portal
	g_abKeyPressed[K_R] = isKeyPressed(0x52); // assign 'R' key for Player 1 second portal
	g_abKeyPressed[K_K] = isKeyPressed(0x4B); // assign 'K' key for Player 2 first portal
	g_abKeyPressed[K_L] = isKeyPressed(0x4C); // assign 'L' key for player 2 second portal

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

void update(double dt)
{
	// get the delta time
	g_dElapsedTime += dt;
	g_dDeltaTime = dt;

	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: splashScreenWait(); // game logic for the splash screen
		break;
	case S_INSTRUCT: instructwait();
		break;
	case S_MAINMENU: mainmenuchoice();
		break;
	case S_GAME: gameplay(); // gameplay logic when we are in the game
		break;
	case S_GAMEOVER: gameoverwait();
		break;
	case S_CLEARGAME: cleargamewait();
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

void render()
{
	clearScreen();      // clears the current screen and draw from scratch 
	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: renderSplashScreen();
		break;
	case S_INSTRUCT: renderinstruct();
		break;
	case S_MAINMENU: renderToMainMenu();
		break;
	case S_GAME: renderGame();
		break;
	case S_GAMEOVER: renderGameOver();
		break;
	case S_CLEARGAME: rendercleargame();
		break;
	}
	renderFramerate();  // renders debug information, frame rate, elapsed time, etc
	renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
	if (splashscreen == 0)
	{
		if (g_abKeyPressed[K_RETURN])
		{
			g_eGameState = S_MAINMENU;
		}
	}
	if (splashscreen == 1)
	{
		if (g_abKeyPressed[K_RETURN])
		{
			g_eGameState = S_INSTRUCT;
		}
	}

	if (g_abKeyPressed[K_ESCAPE])
		g_bQuitGame = true;
}

void gameplay()            // gameplay logic
{
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
	moveCharacter();
	// moves the character, collision detection, physics, etc
					  // sound can be played here too.
}

void moveCharacter()
{
	COORD xy;
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
	if (g_abKeyPressed[PLAYER_1_K_UP] && g_sChar.m_cLocation.Y > 0)
	{
		//Beep(1440, 30);	
		//only move if player is facing in the direction he wants to move
		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 2] != 'x' && map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 2] != 'd' && direction == 'u')
		{
			if (g_sChar2.m_cLocation.X != g_sChar.m_cLocation.X || g_sChar.m_cLocation.Y - 1 != g_sChar2.m_cLocation.Y)
			{
				if (g_sChar.m_cLocation.X == boxx.X && g_sChar.m_cLocation.Y - 2 == boxx.Y && map[boxx.X][boxx.Y - 1] != 'x' && boxx.Y && map[boxx.X][boxx.Y - 1] != 'd' && boxx.Y && map[boxx.X][boxx.Y - 1] != 'f')
				{
					boxx.Y--;
					thingthing = something;
					something = map[boxx.X][boxx.Y];
					map[boxx.X][boxx.Y] = 'n';
					if (thingthing != '1')
					{
						map[boxx.X][boxx.Y + 1] = thingthing;
					}
					else
					{
						map[boxx.X][boxx.Y + 1] = '-';
					}
					g_sChar.m_cLocation.Y--;
				}
				else
				{
					g_sChar.m_cLocation.Y--;
					bSomethingHappened = true;
				}
			}
		}
		direction = 'u';
	}
	if (g_abKeyPressed[PLAYER_1_K_LEFT] && g_sChar.m_cLocation.X > 0)
	{
		//Beep(1440, 30);
		if (map[g_sChar.m_cLocation.X - 1][g_sChar.m_cLocation.Y - 1] != 'x' && map[g_sChar.m_cLocation.X - 1][g_sChar.m_cLocation.Y - 1] != 'd' && direction == 'l')
		{
			if (g_sChar2.m_cLocation.X != g_sChar.m_cLocation.X - 1 || g_sChar.m_cLocation.Y != g_sChar2.m_cLocation.Y)
			{
				if (g_sChar.m_cLocation.X - 1 == boxx.X && g_sChar.m_cLocation.Y - 1 == boxx.Y && map[boxx.X - 1][boxx.Y] != 'x' && boxx.Y && map[boxx.X - 1][boxx.Y] != 'd' && boxx.Y && map[boxx.X - 1][boxx.Y] != 'f')
				{

					boxx.X--;
					thingthing = something;
					something = map[boxx.X][boxx.Y];
					map[boxx.X][boxx.Y] = 'n';
					if (thingthing != '1')
					{
						map[boxx.X + 1][boxx.Y] = thingthing;
					}
					else
					{
						map[boxx.X + 1][boxx.Y] = '-';
					}
					g_sChar.m_cLocation.X--;
				}
				else
				{
					g_sChar.m_cLocation.X--;
					bSomethingHappened = true;
				}
			}
		}
		direction = 'l';
	}
	if (g_abKeyPressed[PLAYER_1_K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		//Beep(1440, 30);
		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] != 'x' && map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] != 'd' && direction == 'd')
		{
			if (g_sChar2.m_cLocation.X != g_sChar.m_cLocation.X || g_sChar.m_cLocation.Y + 1 != g_sChar2.m_cLocation.Y)
			{
				if (g_sChar.m_cLocation.X == boxx.X && g_sChar.m_cLocation.Y == boxx.Y && map[boxx.X][boxx.Y + 1] != 'x' && boxx.Y && map[boxx.X][boxx.Y + 1] != 'd' && boxx.Y && map[boxx.X][boxx.Y + 1] != 'f')
				{

					boxx.Y++;
					thingthing = something;
					something = map[boxx.X][boxx.Y];
					map[boxx.X][boxx.Y] = 'n';
					if (thingthing != '1')
					{
						map[boxx.X][boxx.Y - 1] = thingthing;
					}
					else
					{
						map[boxx.X][boxx.Y - 1] = '-';
					}
					g_sChar.m_cLocation.Y++;
				}
				else
				{
					g_sChar.m_cLocation.Y++;
					bSomethingHappened = true;
				}
			}
		}
		direction = 'd';
	}
	if (g_abKeyPressed[PLAYER_1_K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		//Beep(1440, 30);
		if (map[g_sChar.m_cLocation.X + 1][g_sChar.m_cLocation.Y - 1] != 'x' && map[g_sChar.m_cLocation.X + 1][g_sChar.m_cLocation.Y - 1] != 'd' && direction == 'r')
		{
			if (g_sChar2.m_cLocation.X != g_sChar.m_cLocation.X + 1 || g_sChar.m_cLocation.Y != g_sChar2.m_cLocation.Y)
			{
				if (g_sChar.m_cLocation.X + 1 == boxx.X && g_sChar.m_cLocation.Y - 1 == boxx.Y && map[boxx.X + 1][boxx.Y] != 'x' && boxx.Y && map[boxx.X + 1][boxx.Y] != 'd' && boxx.Y && map[boxx.X + 1][boxx.Y] != 'f')
				{

					boxx.X++;
					thingthing = something;
					something = map[boxx.X][boxx.Y];
					map[boxx.X][boxx.Y] = 'n';
					if (thingthing != '1')
					{
						map[boxx.X - 1][boxx.Y] = thingthing;
					}
					else
					{
						map[boxx.X - 1][boxx.Y] = '-';
					}
					g_sChar.m_cLocation.X++;
				}
				else
				{
					g_sChar.m_cLocation.X++;
					bSomethingHappened = true;
				}
			}
		}
		direction = 'r';
	}

	if (bSomethingHappened == true)
	{	
		//reduces the players health if player 1 walks into the fire
		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == 'f')
		{
			direction = 'u';
			healthcount--;
		}

		//check if playr moved into a telporter
		xy = teleportation(teleport, g_sChar.m_cLocation.X, g_sChar.m_cLocation.Y);
		if (xy.X != 0 && xy.Y != 0)
		{
			// move player to other teleporter
			g_sChar.m_cLocation = xy;
		}
		gateOpen = dooring(lever1, lever2, g_sChar.m_cLocation.X, g_sChar.m_cLocation.Y - 1, g_sChar2.m_cLocation.X, g_sChar2.m_cLocation.Y - 1, boxx.X, boxx.Y);
		if (gateOpen == true)
		{
			map[door.X][door.Y] = '-';
		}
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.010;// 125ms should be enough
		//if player reaches exit for stage 0, move to next map
		g_sChar.m_cLocation = mapTransition(g_sChar.m_cLocation, g_sChar.m_cLocation.X, g_sChar.m_cLocation.Y, &level, &transisted);
		if (transisted == true)
		{
			if (level == 0)
			{
				g_eGameState = S_CLEARGAME;
			}
			else
			{
				load_game(level);
				g_sChar2.m_cLocation.X = g_sChar.m_cLocation.X + 1;
				g_sChar2.m_cLocation.Y = g_sChar.m_cLocation.Y;
				transisted = false;
				removeportal = true;
				something = '-';
			}
		}
		teleport.erase(0, teledel);
		teledel = 0;

		g_sChar.m_cLocation = PlayerPositionTeleport(g_sChar.m_cLocation, portal1, portal2, portal3, portal4, PortActive1, PortActive2, PortActive3, PortActive4); // allow g_sChar to teleport between portals
	}
	bool bSomethingHappened_2 = false;
	if (g_dBounceTime2 > g_dElapsedTime)
		return;
	if (g_abKeyPressed[PLAYER_2_K_UP] && g_sChar2.m_cLocation.Y > 0)
	{
		//Beep(1440, 30);
		//only move if player is facing in the direction he wants to move
		if (map[g_sChar2.m_cLocation.X][g_sChar2.m_cLocation.Y - 2] != 'x' && map[g_sChar2.m_cLocation.X][g_sChar2.m_cLocation.Y - 2] != 'd' && direction2 == 'u')
		{
			if (g_sChar.m_cLocation.X != g_sChar2.m_cLocation.X || g_sChar2.m_cLocation.Y - 1 != g_sChar.m_cLocation.Y)
			{
				if (g_sChar2.m_cLocation.X == boxx.X && g_sChar2.m_cLocation.Y - 2 == boxx.Y && map[boxx.X][boxx.Y - 1] != 'x' && boxx.Y && map[boxx.X][boxx.Y - 1] != 'd' && boxx.Y && map[boxx.X][boxx.Y - 1] != 'f')
				{

					boxx.Y--;
					thingthing = something;
					something = map[boxx.X][boxx.Y];
					map[boxx.X][boxx.Y] = 'n';
					if (thingthing != '1')
					{
						map[boxx.X][boxx.Y + 1] = thingthing;
					}
					else
					{
						map[boxx.X][boxx.Y + 1] = '-';
					}
					g_sChar2.m_cLocation.Y--;
				}
				else
				{
					g_sChar2.m_cLocation.Y--;
					bSomethingHappened_2 = true;
				}
			}
		}
		direction2 = 'u';
	}
	if (g_abKeyPressed[PLAYER_2_K_LEFT] && g_sChar2.m_cLocation.X > 0)
	{
		//Beep(1440, 30);
		if (map[g_sChar2.m_cLocation.X - 1][g_sChar2.m_cLocation.Y - 1] != 'x' && map[g_sChar2.m_cLocation.X - 1][g_sChar2.m_cLocation.Y - 1] != 'd' && direction2 == 'l')
		{
			if (g_sChar.m_cLocation.X != g_sChar2.m_cLocation.X - 1 || g_sChar2.m_cLocation.Y != g_sChar.m_cLocation.Y)
			{
				if (g_sChar2.m_cLocation.X - 1 == boxx.X && g_sChar2.m_cLocation.Y - 1 == boxx.Y && map[boxx.X - 1][boxx.Y] != 'x' && boxx.Y && map[boxx.X - 1][boxx.Y] != 'd' && boxx.Y && map[boxx.X - 1][boxx.Y] != 'f')
				{

					boxx.X--;
					thingthing = something;
					something = map[boxx.X][boxx.Y];
					map[boxx.X][boxx.Y] = 'n';
					if (thingthing != '1')
					{
						map[boxx.X + 1][boxx.Y] = thingthing;
					}
					else
					{
						map[boxx.X + 1][boxx.Y] = '-';
					}
					g_sChar2.m_cLocation.X--;
				}
				else
				{
					g_sChar2.m_cLocation.X--;
					bSomethingHappened_2 = true;
				}
			}
		}
		direction2 = 'l';
	}
	if (g_abKeyPressed[PLAYER_2_K_DOWN] && g_sChar2.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		//Beep(1440, 30);
		if (map[g_sChar2.m_cLocation.X][g_sChar2.m_cLocation.Y] != 'x' && map[g_sChar2.m_cLocation.X][g_sChar2.m_cLocation.Y] != 'd' && direction2 == 'd')
		{
			if (g_sChar.m_cLocation.X != g_sChar2.m_cLocation.X || g_sChar2.m_cLocation.Y + 1 != g_sChar.m_cLocation.Y)
			{
				if (g_sChar2.m_cLocation.X == boxx.X && g_sChar2.m_cLocation.Y == boxx.Y && map[boxx.X][boxx.Y + 1] != 'x' && boxx.Y && map[boxx.X][boxx.Y + 1] != 'd' && boxx.Y && map[boxx.X][boxx.Y + 1] != 'f')
				{

					boxx.Y++;
					thingthing = something;
					something = map[boxx.X][boxx.Y];
					map[boxx.X][boxx.Y] = 'n';
					if (thingthing != '1')
					{
						map[boxx.X][boxx.Y - 1] = thingthing;
					}
					else
					{
						map[boxx.X][boxx.Y - 1] = '-';
					}
					g_sChar2.m_cLocation.Y++;
				}
				else
				{
					g_sChar2.m_cLocation.Y++;
					bSomethingHappened_2 = true;
				}
			}
		}
		direction2 = 'd';
	}
	if (g_abKeyPressed[PLAYER_2_K_RIGHT] && g_sChar2.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		//Beep(1440, 30);
		if (map[g_sChar2.m_cLocation.X + 1][g_sChar2.m_cLocation.Y - 1] != 'x' && map[g_sChar2.m_cLocation.X + 1][g_sChar2.m_cLocation.Y - 1] != 'd' && direction2 == 'r')
		{
			if (g_sChar.m_cLocation.X != g_sChar2.m_cLocation.X + 1 || g_sChar2.m_cLocation.Y != g_sChar.m_cLocation.Y)
			{
				if (g_sChar2.m_cLocation.X + 1 == boxx.X && g_sChar2.m_cLocation.Y - 1 == boxx.Y && map[boxx.X + 1][boxx.Y] != 'x' && boxx.Y && map[boxx.X + 1][boxx.Y] != 'd' && boxx.Y && map[boxx.X + 1][boxx.Y] != 'f')
				{

					boxx.X++;
					thingthing = something;
					something = map[boxx.X][boxx.Y];
					map[boxx.X][boxx.Y] = 'n';
					if (thingthing != '1')
					{
						map[boxx.X - 1][boxx.Y] = thingthing;
					}
					else
					{
						map[boxx.X - 1][boxx.Y] = '-';
					}
					g_sChar2.m_cLocation.X++;
				}
				else
				{
					g_sChar2.m_cLocation.X++;
					bSomethingHappened_2 = true;
				}

			}

		}
		direction2 = 'r';
	}


	if (bSomethingHappened_2 == true)
	{	
		//reduces the health of the players if player 2 walks into the fire
		if (map[g_sChar2.m_cLocation.X][g_sChar2.m_cLocation.Y - 1] == 'f')
		{
			direction2 = 'u';
			healthcount--;
		}
		//check if playr moved into a telporter
		xy = teleportation(teleport, g_sChar2.m_cLocation.X, g_sChar2.m_cLocation.Y);
		if (xy.X != 0 && xy.Y != 0)
		{
			// move player to other teleporter
			g_sChar2.m_cLocation = xy;
		}
		// set the bounce time to some time in the future to prevent accidental triggers
		gateOpen = dooring(lever1, lever2, g_sChar.m_cLocation.X, g_sChar.m_cLocation.Y - 1, g_sChar2.m_cLocation.X, g_sChar2.m_cLocation.Y - 1, boxx.X, boxx.Y);
		if (gateOpen == true)
		{
			map[door.X][door.Y] = '-';
		}
		g_dBounceTime2 = g_dElapsedTime + 0.005; // 125ms should be enough
		//if player reaches exit for stage 0, move to next map
		g_sChar2.m_cLocation = mapTransition(g_sChar2.m_cLocation, g_sChar2.m_cLocation.X, g_sChar2.m_cLocation.Y, &level, &transisted);
		if (transisted == true)
		{
			if (level == 0)
			{
				g_eGameState = S_CLEARGAME;
			}
			else
			{
				load_game(level);
				g_sChar.m_cLocation.X = g_sChar2.m_cLocation.X + 1;
				g_sChar.m_cLocation.Y = g_sChar2.m_cLocation.Y;
				transisted = false;
				removeportal = true;
			}
		}
		teleport.erase(0, teledel);
		teledel = 0;

		g_sChar2.m_cLocation = PlayerPositionTeleport(g_sChar2.m_cLocation, portal1, portal2, portal3, portal4, PortActive1, PortActive2, PortActive3, PortActive4);
	}
}

void processUserInput()
{
	// quits the game if player hits the escape key
	if (g_abKeyPressed[K_ESCAPE])
		g_bQuitGame = true;
	if (g_abKeyPressed[K_E])	// Player1 shoot portal 1
		shotPortal = true;
	if (g_abKeyPressed[K_R])	// Player1 shoot portal 2
		shotPortal2 = true;
	if (g_abKeyPressed[K_K])	// Player2 shoot portal 1
		shotPortal3 = true;
	if (g_abKeyPressed[K_L])	// Player2 shoot portal 2
		shotPortal4 = true;
}

void clearScreen()
{
	// Clears the buffer with this colour attribute
	g_Console.clearBuffer(0x00);
}

void renderSplashScreen()  // renders the splash screen
{
	int z = 0;
	int z2 = 0;

	COORD c;
	
	if ((int)(g_dElapsedTime) % (2) == 0)
	{
		exscreen = 0;
		string sp = extractscreen(exscreen);
		for (int y = 0; y < 21; y++)
		{
			for (int x = 0; x < 59; x++)
			{
				splash[x][y] = sp[z];
				z++;
			}
			z = (y + 1) * 59;
		}
		for (int y = 0; y < 21; y++)
		{
			c.Y = y + 4;
			for (int x = 0; x < 59; x++)
			{
				c.X = x + 10;
				if (splash[x][y] != '~' && x < 11)
				{
					g_Console.writeToBuffer(c, splash[x][y], 0x0B);
				}
				else if (splash[x][y] != '~' && x > 47)
				{
					g_Console.writeToBuffer(c, splash[x][y], 0x0B);
				}
				else if (splash[x][y] != '~' && y > 5)
				{
					g_Console.writeToBuffer(c, splash[x][y], 0x0B);
				}
				else if (splash[x][y] != '~' && y > 10)
				{
					g_Console.writeToBuffer(c, splash[x][y], 0x0B);
				}
				else if (splash[x][y] != '~')
				{
					g_Console.writeToBuffer(c, splash[x][y], 0x07);
				}
			}
		
		}
	}
	else
	{
		exscreen = 1;
		string sp2 = extractscreen(exscreen);
		for (int y = 0; y < 21; y++)
		{
			for (int x = 0; x < 59; x++)
			{
				splash[x][y] = sp2[z2];
				z2++;
			}
			z2 = (y + 1) * 59;
		}
		for (int y = 0; y <= 20; y++)
		{
			c.Y = y + 4;
			for (int x = 0; x <= 58; x++)
			{
				c.X = x + 10;
				if (splash[x][y] != '~' && x < 11)
				{
					g_Console.writeToBuffer(c, splash[x][y], 0x0B);
				}
				else if (splash[x][y] != '~' && x > 47)
				{
					g_Console.writeToBuffer(c, splash[x][y], 0x0B);
				}
				else if (splash[x][y] != '~' && y > 5)
				{
					g_Console.writeToBuffer(c, splash[x][y], 0x0B);
				}
				else if (splash[x][y] != '~')
				{
					g_Console.writeToBuffer(c, splash[x][y], 0x07);
				}
			}
		}
	}
	
	c = g_Console.getConsoleSize();
	c.Y /= 3;
	c.X = c.X / 2 - 35;
	c.Y += 3;

	c.X = g_Console.getConsoleSize().X / 2 - 8;
	g_Console.writeToBuffer(c, "Start Game", getColour(splashscreen, 0));
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 9;
	g_Console.writeToBuffer(c, "Instructions", getColour(splashscreen,1));
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 13;
	g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x07);

	if (splashscreen > 1)
	{
		splashscreen = 0;
	}
	else if (splashscreen < 0)
	{
		splashscreen = 1;
	}
	if (g_dElapsedTime < g_dBounceTime)
	{
		return;
	}

	bool presskey = false;
	if (g_abKeyPressed[PLAYER_2_K_DOWN])
	{
		splashscreen++;
		presskey = true;
	}
	else if (g_abKeyPressed[PLAYER_2_K_UP])
	{
		splashscreen--;
		presskey = true;
	}

	if (presskey == true)
	{
		g_dBounceTime = g_dElapsedTime + 0.125;
	}
}

void instructwait()		
{

	if (g_abKeyPressed[K_BACK])
	{
		g_eGameState = S_SPLASHSCREEN;
	}
	if (g_abKeyPressed[K_ESCAPE])
	{
		g_bQuitGame = true;
	}
}

void renderinstruct()	//renders the instruction screen
{
	int z = 0;
	exscreen = 2;
	string instruction = extractscreen(exscreen);

	COORD c;

	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 58; x++)
		{
			instruct[x][y] = instruction[z];
			z++;
		}
		z = (y + 1) * 58;
	}
	for (int y = 0; y < 6; y++)
	{
		c.Y = y + 4;
		for (int x = 0; x < 58; x++)
		{
			c.X = x + 10;
			if (instruct[x][y] != '~')
			{
				g_Console.writeToBuffer(c, instruct[x][y], 0x07);
			}
		}
	}
	c = g_Console.getConsoleSize();
	c.Y /= 3 + 10;
	c.X = c.X / 2 - 35;
	c.Y += 10;
	c.X = g_Console.getConsoleSize().X / 2 - 20;
	g_Console.writeToBuffer(c, "Player 1 Controls:", 0x03);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 20;
	g_Console.writeToBuffer(c, "W, A, S, D - Direction", 0x03);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 20;
	g_Console.writeToBuffer(c, "E, R - Portal Gun", 0x03);
	c.Y += 3;
	c.X = g_Console.getConsoleSize().X / 2 - 20;
	g_Console.writeToBuffer(c, "Player 2 Controls:", 0x02);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 20;
	g_Console.writeToBuffer(c, "Direction Keys - Direction", 0x02);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 20;
	g_Console.writeToBuffer(c, "K, L - Portal Gun", 0x02);
	c.Y += 3;
	c.X = g_Console.getConsoleSize().X / 2 - 20;
	g_Console.writeToBuffer(c, "Press backspace to go back to homescreen.", 0x07);
	

}

void gameoverwait()	
{
	if (g_abKeyPressed[K_RETURN])
	{
		g_eGameState = S_SPLASHSCREEN;
	}
	if (g_abKeyPressed[K_ESCAPE])
	{
		g_bQuitGame = true;
	}
}

void renderGameOver()
{
	int z = 0;
	exscreen = 4;
	string gover = extractscreen(exscreen);

	COORD c;

	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 63; x++)
		{
			over[x][y] = gover[z];
			z++;
		}
		z = (y + 1) * 63;
	}
	for (int y = 0; y < 6; y++)
	{
		c.Y = y + 4;
		for (int x = 0; x < 63; x++)
		{
			c.X = x + 10;
			if (over[x][y] != '~')
			{
				g_Console.writeToBuffer(c, over[x][y], 0x0C);
			}
		}
	}
	c = g_Console.getConsoleSize();
	c.Y /= 3 + 10;
	c.X = c.X / 2 - 35;
	c.Y += 10;
	c.X = g_Console.getConsoleSize().X / 2 - 20;
	g_Console.writeToBuffer(c, "Press enter to go back to Starting Screen.", 0x03);
}

void renderhealth()		// renders the health bar of the players
{
	COORD c;
	c = g_Console.getConsoleSize();
	c.Y /= 3 + 10;
	c.X = c.X / 2;
	c.Y += 5;
	c.X = g_Console.getConsoleSize().X / 2 + 25;
	g_Console.writeToBuffer(c, "Health", 0x07);
	if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == 'f' || map[g_sChar2.m_cLocation.X][g_sChar2.m_cLocation.Y - 1] == 'f')
	{
		g_Console.writeToBuffer(c, "Health", 0xFC);
	}
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 + 25;
	/*c.X = g_Console.getConsoleSize().X / 2 + 30;
	g_Console.writeToBuffer(c, health, 0x07);*/
	g_Console.writeToBuffer(c.X - 1, c.Y, '[', 0x0F);
	g_Console.writeToBuffer(c.X + 10, c.Y, ']', 0x0F);
	for (int i = 0; i < healthcount; i++)
	{
		g_Console.writeToBuffer(c, healthbar, 0x0C);
		c.X += 1;
		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == 'f' || map[g_sChar2.m_cLocation.X][g_sChar2.m_cLocation.Y - 1] == 'f')
		{
			g_Console.writeToBuffer(c, healthbar, 0x07);
		}
	}
	if (healthcount < 4)
	{
		if ((int)(g_dElapsedTime) % 2 == 0)
		{
			c.Y += 5;
			c.X = g_Console.getConsoleSize().X / 2 + 25;
			g_Console.writeToBuffer(c, "WARNING", 0x0C);
			c.Y += 1;
			c.X = g_Console.getConsoleSize().X / 2 + 25;
			g_Console.writeToBuffer(c, "HP LOW", 0x0C);
		}
		else
		{
			c.Y += 5;
			c.X = g_Console.getConsoleSize().X / 2 + 25;
			g_Console.writeToBuffer(c, "WARNING", 0x07);
			c.Y += 1;
			c.X = g_Console.getConsoleSize().X / 2 + 25;
			g_Console.writeToBuffer(c, "HP LOW", 0x07);
		}
	}
	if (healthcount == 0)
	{
		g_eGameState = S_GAMEOVER;
		healthcount = 10;
	}
	

}

void rendermap()
{
	/*// Set up sample colours, and output shadings
	const WORD colors[] = {
	0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
	0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	};*/

	int c = 0;
	for (int a = 0; a < 20; a++)
	{
		for (int b = 0; b < 60; b++)
		{
			//transfer it to an array
			//map[b][a] = stupid[c];
			//record where is the teleporter to the 
			if (map[b][a] == 'p')
			{
				teledel += 2;
				teleport += b;
				teleport += a + 1;
			}
			if (map[b][a] == 'd')
			{
				door.X = b;
				door.Y = a;
			}
			if (map[b][a] == 'l')
			{
				lever1.X = b;
				lever1.Y = a;
			}
			if (map[b][a] == 'L')
			{
				lever2.X = b;
				lever2.Y = a;
			}
			if (map[b][a] == 'n')
			{
				boxx.X = b;
				boxx.Y = a;
			}

			c++;
		}
		c = (a + 1) * 60;
	}
	//buffer the map
	COORD coord;
	for (int y = 0; y <= 19; y++)
	{
		coord.Y = y + 1;
		for (int x = 0; x <= 59; x++)
		{
			coord.X = x;
			//if player is within range, buffers the ground if the map array is '-' in the txt files
			if (map[x][y] == '-')
			{
				if ((g_sChar.m_cLocation.X + 6) >= x && x >= (g_sChar.m_cLocation.X - 6) && (g_sChar.m_cLocation.Y - 6) <= (y - 1) && (g_sChar.m_cLocation.Y + 6) >= (y + 3))
				{
					g_Console.writeToBuffer(coord, ground, 0x88);
				}
				if ((g_sChar2.m_cLocation.X + 6) >= x && x >= (g_sChar2.m_cLocation.X - 6) && (g_sChar2.m_cLocation.Y - 6) <= (y - 1) && (g_sChar2.m_cLocation.Y + 6) >= (y + 3))
				{
					g_Console.writeToBuffer(coord, ground, 0x88);
				}
			}
			//if player is within range, buffers the walls if the map array is 'x' in the txt files
			if (map[x][y] == 'x')
			{
				if ((g_sChar.m_cLocation.X + 4) >= x && x >= (g_sChar.m_cLocation.X - 4) && (g_sChar.m_cLocation.Y - 3) <= (y + 1) && (g_sChar.m_cLocation.Y + 3) >= (y + 1))
				{
					g_Console.writeToBuffer(coord, wall, 0x80);
				}
				if ((g_sChar2.m_cLocation.X + 4) >= x && x >= (g_sChar2.m_cLocation.X - 4) && (g_sChar2.m_cLocation.Y - 3) <= (y + 1) && (g_sChar2.m_cLocation.Y + 3) >= (y + 1))
				{
					g_Console.writeToBuffer(coord, wall, 0x80);
				}
			}
			//buffers a stationary teleporter if the map array is 'p' in the txt files
			if (map[x][y] == 'p')
			{
				if ((g_sChar.m_cLocation.X + 4) >= x && x >= (g_sChar.m_cLocation.X - 4) && (g_sChar.m_cLocation.Y - 3) <= (y + 1) && (g_sChar.m_cLocation.Y + 3) >= (y + 1))
				{
					g_Console.writeToBuffer(coord, wall, 0x2B);
				}
				if ((g_sChar2.m_cLocation.X + 4) >= x && x >= (g_sChar2.m_cLocation.X - 4) && (g_sChar2.m_cLocation.Y - 3) <= (y + 1) && (g_sChar2.m_cLocation.Y + 3) >= (y + 1))
				{
					g_Console.writeToBuffer(coord, wall, 0x2B);
				}
			}
			//buffer exit if the map array is 'e' in the txt files
			if (map[x][y] == 'e')
			{
				g_Console.writeToBuffer(coord, destination, 0xA0);
			}
			//if player is within range, buffers a door if the map array is 'd' in the txt files
			if (map[x][y] == 'd')
			{
				if ((g_sChar.m_cLocation.X + 4) >= x && x >= (g_sChar.m_cLocation.X - 4) && (g_sChar.m_cLocation.Y - 3) <= (y + 1) && (g_sChar.m_cLocation.Y + 3) >= (y + 1))
				{
					g_Console.writeToBuffer(coord, wall, 0x11);
				}
				if ((g_sChar2.m_cLocation.X + 4) >= x && x >= (g_sChar2.m_cLocation.X - 4) && (g_sChar2.m_cLocation.Y - 3) <= (y + 1) && (g_sChar2.m_cLocation.Y + 3) >= (y + 1))
				{
					g_Console.writeToBuffer(coord, wall, 0x11);
				}
			}
			//if player is within range, buffers lever if the map array is 'l' or 'L' in the txt files
			if (map[x][y] == 'l' || map[x][y] == 'L')
			{
				if ((g_sChar.m_cLocation.X + 4) >= x && x >= (g_sChar.m_cLocation.X - 4) && (g_sChar.m_cLocation.Y - 3) <= (y + 1) && (g_sChar.m_cLocation.Y + 3) >= (y + 1))
				{
					g_Console.writeToBuffer(coord, destination, 0x1F);
				}
				if ((g_sChar2.m_cLocation.X + 4) >= x && x >= (g_sChar2.m_cLocation.X - 4) && (g_sChar2.m_cLocation.Y - 3) <= (y + 1) && (g_sChar2.m_cLocation.Y + 3) >= (y + 1))
				{
					g_Console.writeToBuffer(coord, destination, 0x1F);
				}
			}
			//buffers fire(lava) if the map array is 'f' in the txt files
			if (map[x][y] == 'f')
			{
					g_Console.writeToBuffer(coord, ground, 0xCE);
			}
			//if player is within range, buffers box(es) if the map array is 'n' in the txt files
			if (map[x][y] == 'n')
			{
				if ((g_sChar.m_cLocation.X + 4) >= x && x >= (g_sChar.m_cLocation.X - 4) && (g_sChar.m_cLocation.Y - 3) <= (y + 1) && (g_sChar.m_cLocation.Y + 3) >= (y + 1))
				{
					g_Console.writeToBuffer(coord, box, 0x8E);
				}
				if ((g_sChar2.m_cLocation.X + 4) >= x && x >= (g_sChar2.m_cLocation.X - 4) && (g_sChar2.m_cLocation.Y - 3) <= (y + 1) && (g_sChar2.m_cLocation.Y + 3) >= (y + 1))
				{
					g_Console.writeToBuffer(coord, box, 0x8E);
				}
			}
			// checks if portal was shot and buffers it at where the line of projectile ends 
			if (PortActive1 == true)											
			{
				g_Console.writeToBuffer(portal1, RenderPortal.portal, 0x8C);
			}
			if (PortActive2 == true)
			{
				g_Console.writeToBuffer(portal2, RenderPortal.portal, 0x81);
			}
			if (PortActive3 == true)
			{
				g_Console.writeToBuffer(portal3, RenderPortal.portal, 0x8D);
			}
			if (PortActive4 == true)
			{
				g_Console.writeToBuffer(portal4, RenderPortal.portal, 0x8B);

			}
			// if level changes, set the bool PortActive to be false , which stops the portal from buffering
			if (removeportal)			
			{
				PortActive1 = false;
				PortActive2 = false;
				PortActive3 = false;
				PortActive4 = false;
				removeportal = false;
			}
		}
		g_Console.writeToBuffer(0, 21, text(level), 0x0D);
	}
}

void renderGame()
{
	rendermap();// renders the map to the buffer first	
	renderCharacter();	// renders the character into the buffer
	renderhealth();		//renders the players health 
	renderPortalgun();	//renders the Portalgun's projectile and the portal

}


void Portalgun(COORD playerLocation, char playerDirection, COORD& portal, bool& portalActive)
{
	int colour;
	COORD nextLocation = playerLocation;

	if (shotPortal)			//checks which portal was shot and changes its colour accordingly
		colour = 140;
	else if (shotPortal2)
		colour = 129;
	else if (shotPortal3)
		colour = 141;
	else if (shotPortal4)
		colour = 139;

	switch (playerDirection)	//checks current player direction and buffers a line of projectile toawrds where the player is facing
	{
	case 'u':
		while ((map[nextLocation.X][nextLocation.Y - 2] != 'x') && (map[nextLocation.X][nextLocation.Y-2] != 'e') && (map[nextLocation.X][nextLocation.Y-2] != 'd'))
		{
			nextLocation.Y--;
			g_Console.writeToBuffer(nextLocation, RenderPortal.UpDownProjectile, colour);
		}
		break;

	case 'd':
		while ((map[nextLocation.X][nextLocation.Y] != 'x') && (map[nextLocation.X][nextLocation.Y] != 'e') && (map[nextLocation.X][nextLocation.Y] != 'd'))
		{
			nextLocation.Y++;
			g_Console.writeToBuffer(nextLocation, RenderPortal.UpDownProjectile, colour);
		}
		break;

	case 'l':
		while ((map[nextLocation.X-1][nextLocation.Y - 1] != 'x') && (map[nextLocation.X-1][nextLocation.Y-1] != 'e') && (map[nextLocation.X-1][nextLocation.Y-1] != 'd'))
		{
			nextLocation.X--;
			g_Console.writeToBuffer(nextLocation, RenderPortal.LeftRightProjectile, colour);
		}
		break;

	case'r':
		while ((map[nextLocation.X + 1][nextLocation.Y - 1] != 'x' && (map[nextLocation.X + 1][nextLocation.Y - 1] != 'e' && (map[nextLocation.X + 1][nextLocation.Y - 1]))))
		{
			nextLocation.X++;
			g_Console.writeToBuffer(nextLocation, RenderPortal.LeftRightProjectile, colour);
		}
		break;
	}

	// update the parameters that were passed in
	portal.X = nextLocation.X;
	portal.Y = nextLocation.Y;
	portalActive = true;
}

void renderPortalgun()		
{	
	if (shotPortal)
	{
		Portalgun(g_sChar.m_cLocation, direction, portal1, PortActive1);	
		shotPortal = false;
	}
	if (shotPortal2)
	{
		Portalgun(g_sChar.m_cLocation, direction, portal2, PortActive2);
		shotPortal2 = false;
	}
	if (shotPortal3)
	{
		Portalgun(g_sChar2.m_cLocation, direction2, portal3, PortActive3);
		shotPortal3 = false;
	}
	if (shotPortal4)
	{
		Portalgun(g_sChar2.m_cLocation, direction2, portal4, PortActive4);
		shotPortal4 = false;
	}
}

void renderCharacter()
{
	WORD charColor = 0x89;
	// Draw the location of the character
	//change player direction
	if (direction == 'u')
	{
		g_Console.writeToBuffer(g_sChar.m_cLocation, Character.Up, charColor);
	}
	else if (direction == 'd')
	{
		g_Console.writeToBuffer(g_sChar.m_cLocation, Character.Down, charColor);
	}
	else if (direction == 'l')
	{
		g_Console.writeToBuffer(g_sChar.m_cLocation, Character.Left, charColor);
	}
	else if (direction == 'r')
	{
		g_Console.writeToBuffer(g_sChar.m_cLocation, Character.Right, charColor);
	}
	else
	{
		g_Console.writeToBuffer(g_sChar.m_cLocation, Character.Up, charColor);
	}
	WORD charColor2 = 0x8C;
	// Draw the location of the character
	//change player direction
	
	if (direction2 == 'u')
	{
		g_Console.writeToBuffer(g_sChar2.m_cLocation, Character.Up, charColor2);
	}
	else if (direction2 == 'd')
	{
		g_Console.writeToBuffer(g_sChar2.m_cLocation, Character.Down, charColor2);
	}
	else if (direction2 == 'l')
	{
		g_Console.writeToBuffer(g_sChar2.m_cLocation, Character.Left, charColor2);
	}
	else if (direction2 == 'r')
	{
		g_Console.writeToBuffer(g_sChar2.m_cLocation, Character.Right, charColor2);
	}
	else
	{
		g_Console.writeToBuffer(g_sChar2.m_cLocation, Character.Up, charColor2);
	}
}

void renderFramerate()
{
	//COORD c;
	//// displays the framerate
	//std::ostringstream ss;
	//ss << std::fixed << std::setprecision(3);
	//ss << 1.0 / g_dDeltaTime << "fps";
	//c.X = g_Console.getConsoleSize().X - 9;
	//c.Y = 0;
	//g_Console.writeToBuffer(c, ss.str());

	//// displays the elapsed time
	//ss.str("");
	//ss << g_dElapsedTime << "secs";
	//c.X = 0;
	//c.Y = 0;
	//g_Console.writeToBuffer(c, ss.str());
}

void renderToScreen()
{
	// Writes the buffer to the console, hence you will see what you have written
	g_Console.flushBufferToConsole();
}

void mainmenuchoice()
{
	if (lvl == 0)
	{
		if (g_abKeyPressed[K_RETURN])
		{

			g_sChar.m_cLocation.X = 2;
			g_sChar.m_cLocation.Y = 19;
			g_sChar2.m_cLocation.X = 2;
			g_sChar2.m_cLocation.Y = 18;
			level = 11;
			load_game(level);

			g_eGameState = S_GAME;
		}
	}

	if (lvl == 1)
	{
		if (g_abKeyPressed[K_RETURN])
		{

			g_sChar.m_cLocation.X = 0;
			g_sChar.m_cLocation.Y = 4;
			g_sChar2.m_cLocation.X = 1;
			g_sChar2.m_cLocation.Y = 4;
			level = 21;
			load_game(level);

			g_eGameState = S_GAME;
		}
	}
	if (lvl == 2)
	{
		if (g_abKeyPressed[K_RETURN])
		{

			g_sChar.m_cLocation.X = 0;
			g_sChar.m_cLocation.Y = 19;
			g_sChar2.m_cLocation.X = 1;
			g_sChar2.m_cLocation.Y = 19;
			level = 31;
			load_game(level);

			g_eGameState = S_GAME;
		}
	}
	if (lvl == 3)
	{
		if (g_abKeyPressed[K_RETURN])
		{

			g_sChar.m_cLocation.X = 0;
			g_sChar.m_cLocation.Y = 2;
			g_sChar2.m_cLocation.X = 1;
			g_sChar2.m_cLocation.Y = 2;
			level = 41;
			load_game(level);

			g_eGameState = S_GAME;
		}
	}
	if (lvl == 4)
	{
		if (g_abKeyPressed[K_RETURN])
		{

			g_sChar.m_cLocation.X = 0;
			g_sChar.m_cLocation.Y = 19;
			g_sChar2.m_cLocation.X = 1;
			g_sChar2.m_cLocation.Y = 19;
			level = 51;
			load_game(level);

			g_eGameState = S_GAME;
		}
	}

	if (g_abKeyPressed[K_ESCAPE])		
		g_bQuitGame = true;
}

void renderToMainMenu()
{
	int z = 0;
	exscreen = 3;
	string mainex = extractscreen(exscreen);

	COORD c;

	for (int y = 0; y < 12; y++)
	{
		for (int x = 0; x < 73; x++)
		{
			mainmenuart[x][y] = mainex[z];
			z++;
		}
		z = (y + 1) * 73;
	}
	for (int y = 0; y < 12; y++)
	{
		c.Y = y + 4;
		for (int x = 0; x < 73; x++)
		{
			c.X = x + 3;
			if (mainmenuart[x][y] != '~')
			{
				g_Console.writeToBuffer(c, mainmenuart[x][y], 0x09);
			}
		}
	}
	c = g_Console.getConsoleSize();
	c.Y /= 3 + 10;
	c.X = c.X / 2 - 35;
	c.Y += 15;
	c.X = g_Console.getConsoleSize().X / 2 - 20;
	g_Console.writeToBuffer(c, "Press enter to choose your level (1-5).", 0x03);
	
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 5;
	g_Console.writeToBuffer(c.X, c.Y++, "Level 1", getColour(lvl, 0));
	g_Console.writeToBuffer(c.X, c.Y++, "Level 2", getColour(lvl, 1));
	g_Console.writeToBuffer(c.X, c.Y++, "Level 3", getColour(lvl, 2));
	g_Console.writeToBuffer(c.X, c.Y++, "Level 4", getColour(lvl, 3));
	g_Console.writeToBuffer(c.X, c.Y++, "Level 5", getColour(lvl, 4));

	
	if (lvl > 4)
	{
		lvl = 0;
	}
	else if (lvl < 0)
	{
		lvl = 4;
	}
		
	if (g_dElapsedTime < g_dBounceTime)
	{
		return;
	}
	
	bool presskey = false;
	if (g_abKeyPressed[PLAYER_2_K_DOWN])
	{
		lvl++;
		presskey = true;
	}
	else if (g_abKeyPressed[PLAYER_2_K_UP])
	{
		lvl--;
		presskey = true;
	}
	
	if (presskey == true)
	{
		g_dBounceTime = g_dElapsedTime + 0.125;
	}
}

void rendercleargame()
{
	int z = 0;

	COORD c;
	
	if ((int)(g_dElapsedTime) % 2 == 0)
	{
		exscreen = 5;
		for (int y = 0; y < 20; y++)
		{
			c.Y = y + 3;
			for (int x = 0; x < 60; x++)
			{
				c.X = x + 10;
				if (clearscreen[x][y] != '~')
				{
					g_Console.writeToBuffer(c, clearscreen[x][y], 0x07);
				}
			}
		}
	}
	else
	{
		exscreen = 6;
		for (int y = 0; y < 20; y++)
		{
			c.Y = y + 3;
			for (int x = 0; x < 60; x++)
			{
				c.X = x + 10;
				if (clearscreen[x][y] != '~')
				{
					g_Console.writeToBuffer(c, clearscreen[x][y], 0x07);
				}
			}
		}
	}
	string clear = extractscreen(exscreen);
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 60; x++)
		{
			clearscreen[x][y] = clear[z];
			z++;
		}
		z = (y + 1) * 60;
	}
	c = g_Console.getConsoleSize();
	c.Y /= 3 + 10;
	c.X = c.X / 2 - 35;
	c.Y += 10;
	c.X = g_Console.getConsoleSize().X / 2 - 20;
	g_Console.writeToBuffer(c, "Press enter to go back to Starting Screen.", 0x07);
}

void cleargamewait()
{
	if (g_abKeyPressed[K_RETURN])
	{
		g_eGameState = S_SPLASHSCREEN;
	}
	if (g_abKeyPressed[K_ESCAPE])
	{
		g_bQuitGame = true;
	}
}