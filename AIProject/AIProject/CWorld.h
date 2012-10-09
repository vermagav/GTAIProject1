#ifndef CWORLD_H
#define CWORLD_H

//CWorld.h
#include "CAdversary.h"
#include <Windows.h>

/* Main class for maintaining and running the world state */
class CWorld
{

public:
	// Constructor: Need for Init() function???
	CWorld(): robot(CHomeObject(STARTX_HOMEAGENT, STARTY_HOMEAGENT)), goalCoord(CPoint(STARTX_GOAL, STARTY_GOAL))
	{
		//Initialise vector of adversaries
		InitEnemies();
		RobotGameState = GAMESTATE_RUNNING;
	}

	// Main game loop function
	GameState Run();
	
	//Used to cap the Frame Rate
	static const int GAME_SPEED = 50;

private:
	// Our home agent
	CHomeObject robot;

	// Game State for keeping track of what state the game currently is in
	GameState RobotGameState;

	// The enemies that oppose our home agent
	std::vector<CAdversary> enemies;

	// The coordinate of the Robot's Goal
	CPoint goalCoord;
	
	// Voronoi Points
	std::vector<CPoint> vornoiPoints;

	// Intialise the CAdversary Vector
	void InitEnemies();

	// Required Functions for Game Loop
	void CheckState(void);
	void FillBuffer(void);
	void UpdateState(void);
	void DrawState(HANDLE);

	//Used to control FrameCOunt along with GAMESPEED
	//double frameCount;
	//double startTime;
	//double endTime;

	// Screen Representation Variables
	char screenBuffer[LEVEL_MAX_Y + 1][LEVEL_MAX_X +1];
};

#endif

/*
	Implementation Notes:
		char* screen buffer (use level max X and level max Y), set each value to "."
		Init(): set HomeAgent position to "#" on screen buffer, cycle through each adversary and set position to "X"
		Write Draw function: clear screen, output full screen buffer
		Call init and draw in main function

		Write Update function
		Call voronoi functions
		Set voronoi points as "o" in screen buffer
		Loop to run the Update and Draw function 10 times
*/