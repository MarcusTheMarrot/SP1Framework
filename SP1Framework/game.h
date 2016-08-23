#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include "extract.h"

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

// Enumeration to store the control keys that your game will have
enum EKEYS
{
	PLAYER_1_K_UP,
	PLAYER_1_K_DOWN,
	PLAYER_1_K_LEFT,
	PLAYER_1_K_RIGHT,
	PLAYER_2_K_UP,
	PLAYER_2_K_DOWN,
	PLAYER_2_K_LEFT,
	PLAYER_2_K_RIGHT,
	K_ESCAPE,
	K_SPACE,
	K_RETURN,
	K_ONE,
	K_TWO,
	K_THREE,
	K_FOUR,
	K_FIVE,
	K_E,
	K_R,
	K_COUNT
};

// Enumeration for the different screen states
enum EGAMESTATES
{
	S_SPLASHSCREEN,
	S_GAME,
	S_MAINMENU,
	S_MAINMENU2,
	S_MAINMENU3,
	S_MAINMENU4,
	S_MAINMENU5,
	S_LEVELONE,
	S_LEVELTWO,
	S_LEVELTHREE,
	S_LEVELFOUR,
	S_LEVELFIVE,
	S_GAMEOVER,
	S_COUNT
};

// struct for the game character
struct SGameChar
{
    COORD m_cLocation;
    bool  m_bActive;
};
struct SGameChar2
{
	COORD m_cLocation;
	bool  m_bActive;
};

void init        ( void );      // initialize your variables, allocate memory, etc
void getInput    ( void );      // get input from player
void update      ( double dt ); // update the game and the state of the game
void render      ( void );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory

void splashScreenWait();    // waits for time to pass in splash screen
void gameplay();            // gameplay logic
void moveCharacter_1();
void moveCharacter_2();// moves the character, collision detection, physics, etc
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 
void renderSplashScreen();  // renders the splash screen
void renderGame();          // renders the game stuff
int load_game(int level);
void renderMap();           // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderCharacter_2();
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void mainmenuchoice();
void renderToMainMenu();
void renderToMainMenu2();
void renderToMainMenu3();
void renderToMainMenu4();
void renderToMainMenu5();
void renderhealth();
void renderGameOver();

#endif // _GAME_H