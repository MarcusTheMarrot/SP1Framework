// This is the main file to hold everthing together

#include <string>

#include "Framework\timer.h"
#include "game.h"

CStopWatch g_Timer;                            // Timer function to keep track of time and the frame rate
bool g_bQuitGame = false;                    // Set to true if you want to quit the game
const unsigned char gc_ucFPS = 10;                // FPS of this game
const unsigned int gc_uFrameTime = 1000 / gc_ucFPS;    // time for each frame

extern char	map[61][21];

//main loop declaration
void mainLoop( void );
int load_game(int);

// TODO:
// Bug in waitUntil. it waits for the time from getElapsedTime to waitUntil, but should be insignificant.

// main function - starting function
// You should not be modifying this unless you know what you are doing
int main( void )
{
    init();      // initialize your variables
	load_game(11);
    mainLoop();  // main loop
    shutdown();  // do clean up, if any. free memory.
    
    return 0;
}

int load_game(int level)
{
	int c = 0;
	std::string stupid = extractMap(&level);
	for (int a = 0; a < 20; a++)
	{
		for (int b = 0; b < 60; b++)
		{
			//transfer it to an array
			map[b][a] = stupid[c];
			c++;
		}
		c = (a + 1) * 60;
	}

	return 1;
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
    while (!g_bQuitGame)      // run this loop until user wants to quit 
    {        
        getInput();                         // get keyboard input
        update(g_Timer.getElapsedTime());   // update the game
        render();                           // render the graphics output to screen
        g_Timer.waitUntil(gc_uFrameTime);   // Frame rate limiter. Limits each frame to a specified time in ms.      
    }    
}
