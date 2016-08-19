// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include "mapInteract.h"
#include "extract.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

using namespace std; 

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT], teleporter = false;

char	map[61][21];
unsigned char wall = 178;
unsigned char direction;
unsigned char ground = 176;
unsigned char destination = 177;
string	teleport;
string	null = { '\0', };
int stage;
int teledel = 0;

// Game specific variables here
SGameChar	g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

// Console object
Console g_Console(80, 25, "SP1 Framework");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
    // Set precision for floating point output
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

    g_sChar.m_cLocation.X = 7;
    g_sChar.m_cLocation.Y = 6;
    g_sChar.m_bActive = true;
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
	g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
	g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
	g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_ONE] = isKeyPressed(0x31); // assign the one key
	g_abKeyPressed[K_TWO] = isKeyPressed(0x32); // assign the two key
	g_abKeyPressed[K_THREE] = isKeyPressed(0x33); // assign the three key
	g_abKeyPressed[K_FOUR] = isKeyPressed(0x34); // assign the four key
	g_abKeyPressed[K_FIVE] = isKeyPressed(0x35); // assign the five key
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

void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: renderSplashScreen();
		break;
	case S_MAINMENU: renderToMainMenu();
		break;
	case S_GAME: renderGame();
		break;
	}
    renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
	if (g_abKeyPressed[K_SPACE]) // press enter to start game
	{
		g_eGameState = S_MAINMENU;
	}
}

void renderToMainMenu()
{
	int i = 0;
	int j = 0;
	char main[73][12];
	ifstream file("PickALevel.txt"); // read file from PickALevel.txt to print the ascii art
	COORD c;
	if (file.is_open())
	{
		while (j <= 11)
		{
			while (i <= 72)
			{
				file >> main[i][j];
				i++;
			}
			i = 0;
			j++;
		}
		file.close();
	}
	for (int y = 0; y <= 11; y++)
	{
		c.Y = y + 4;
		for (int x = 0; x <= 72; x++)
		{
			c.X = x + 3;
			if (main[x][y] != '~')
			{
				g_Console.writeToBuffer(c, main[x][y], 0x09);
			}
		}
	}
	c = g_Console.getConsoleSize();
	c.Y /= 3 + 5;
	c.X = c.X / 2 - 35;
	c.Y += 15;
	c.X = g_Console.getConsoleSize().X / 2 - 27;
	g_Console.writeToBuffer(c, "Enter a number from 1-5 to choose your level (1-5).", 0x03);

	if (g_abKeyPressed[K_ONE]) // press one to go to game
	{
		g_eGameState = S_GAME;
	}

	if (g_abKeyPressed[K_ESCAPE])
		g_bQuitGame = true;
}

void gameplay()            // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
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
	if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 0 )
	{
		//Beep(1440, 30);	
		//only move if player is facing in the direction he wants to move
		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 2] != 'x' && direction == 'u')
		{
			g_sChar.m_cLocation.Y--;
			bSomethingHappened = true;
		}
		direction = 'u';
	}
	if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0)
	{
		//Beep(1440, 30);
		if (map[g_sChar.m_cLocation.X - 1][g_sChar.m_cLocation.Y - 1] != 'x' && direction == 'l')
		{
			g_sChar.m_cLocation.X--;
			bSomethingHappened = true;
		}
		direction = 'l';
	}
	if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		//Beep(1440, 30);
		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] != 'x' && direction == 'd')
		{
			g_sChar.m_cLocation.Y++;
			bSomethingHappened = true;
		}
		direction = 'd';
	}
	if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		//Beep(1440, 30);
		if (map[g_sChar.m_cLocation.X + 1][g_sChar.m_cLocation.Y - 1] != 'x' && direction == 'r')
		{
			g_sChar.m_cLocation.X++;
			bSomethingHappened = true;
		}
		direction = 'r';
	}

	if (bSomethingHappened)
	{
		//check if playr moved into a telporter
		xy = teleportation(teleport, g_sChar.m_cLocation.X, g_sChar.m_cLocation.Y);
		if (xy.X != 0 && xy.Y != 0)
		{
			// move player to other teleporter
			g_sChar.m_cLocation = xy;
		}
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime; // 125ms should not be enough
		// 125ms should be enough
	}
	//if player reaches exit for stage 0, move to next map
	if (g_sChar.m_cLocation.X == 59 && g_sChar.m_cLocation.Y == 19 && stage == 0)
	{
		teleport.erase(0, teledel);
		teledel = 0;
		stage++;
		g_sChar.m_cLocation.X = 0;
		g_sChar.m_cLocation.Y = 19;
	}
	if (g_sChar.m_cLocation.X == 59 && g_sChar.m_cLocation.Y == 2 && stage == 1)
	{
		teleport.erase(0, teledel);
		teledel = 0;
		stage++;
		g_sChar.m_cLocation.X = 0;
		g_sChar.m_cLocation.Y = 2;
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
	int i = 0;
	int j = 0;
	char splash[74][8];
	ifstream file("title.txt"); // read from title.txt to print the ascii art
	COORD c;
	if (file.is_open())
	{
		while (j <= 7)
		{
			while (i <= 73)
			{
				file >> splash[i][j];
				i++;
			}
			i = 0;
			j++;
		}
		file.close();
	}
	for (int y = 0; y <= 7; y++)
	{
		c.Y = y + 4;
		for (int x = 0; x <= 73; x++)
		{
			c.X = x + 3;
			if (splash[x][y] != '~')
			{
				g_Console.writeToBuffer(c, splash[x][y], 0x09);
			}
		}
	}
	c = g_Console.getConsoleSize();
	c.Y /= 3;
	c.X = c.X / 2 - 35;
	c.Y += 5;
	c.X = g_Console.getConsoleSize().X / 2 - 15;
	g_Console.writeToBuffer(c, "Press <Space> to continue", 0x03);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 13;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x07);
}

void rendermap()
{
	/*// Set up sample colours, and output shadings
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
	}*/
	//write everything in txt to stupid
	string stupid = extractMap(stage);
	int c = 0;
	for (int a = 0; a < 20; a++)
	{
		for (int b = 0; b < 60; b++)
		{
			//transfer it to an array
			map[b][a] = stupid[c];
			//record where is the teleporter to the 
			if (map[b][a] == 'p')
			{
				teledel += 2;
				teleport += b;
				teleport += a + 1;
			}
			c++;
		}
		c = (a + 1) * 60;
	}
	//buffer the shit
	COORD coord;
	for (int y = 0; y <= 19; y++)
	{
		coord.Y = y + 1;
		for (int x = 0; x <= 59; x++)
		{
			coord.X = x;
			//buffer ground
			if (map[x][y] == '-')
			{
				g_Console.writeToBuffer(coord, ground, 0x1A);
			}
			//buffer wall
			if (map[x][y] == 'x')
			{
				g_Console.writeToBuffer(coord, wall);
			}
			//buffer portal
			if (map[x][y] == 'p')
			{
				g_Console.writeToBuffer(coord, wall, 0x2B);
			}
			//buffer exit
			if (map[x][y] == 'e')
			{
				g_Console.writeToBuffer(coord, destination, 0x4C);
			}
		}
	}
}

void renderGame()
{
	rendermap();// renders the map to the buffer first	
	renderCharacter();  // renders the character into the buffer
}

void renderCharacter()
{
	WORD charColor = 0x0C;
    // Draw the location of the character
	//change player direction
	if (direction == 'u')
	{
		if (g_sChar.m_bActive)
		{
			charColor = 0x0A;
		}
		g_Console.writeToBuffer(g_sChar.m_cLocation, '^', charColor);
	}
	else if (direction == 'd')
	{
		if (g_sChar.m_bActive)
		{
			charColor = 0x0A;
		}
		g_Console.writeToBuffer(g_sChar.m_cLocation, 'v', charColor);
	}
	else if (direction == 'l')
	{
		if (g_sChar.m_bActive)
		{
			charColor = 0x0A;
		}
		g_Console.writeToBuffer(g_sChar.m_cLocation, '<', charColor);
	}
	else if (direction == 'r')
	{
		if (g_sChar.m_bActive)
		{
			charColor = 0x0A;
		}
		g_Console.writeToBuffer(g_sChar.m_cLocation, '>', charColor);
	}
	else
	{
		if (g_sChar.m_bActive)
		{
			charColor = 0x0A;
		}
		g_Console.writeToBuffer(g_sChar.m_cLocation, '^', charColor);
	}
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

    // displays the elapsed time
    ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());
}

void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}
