#ifndef CWORLD_H
#define CWORLD_H

//CWorld.h
#include "CAdversary.h"

class CWorld
{

public:
	//Constructor: Need for Init() function???
	CWorld(): robot(CHomeObject(STARTX_HOMEAGENT, STARTY_HOMEAGENT)), goalCoord(CPoint(STARTX_GOALCOORD, STARTY_GOALCOORD))
	{
		//Initialise vector of adversaries
		InitEnemies();
	}

	//MAIN GAME LOOP FUNCTION
	void run();
	
	//Used to cap the Frame Rate
	static const int GAME_SPEED = 50;

private:
	// Our home agent
	CHomeObject robot;

	// The enemies that oppose our home agent
	std::vector<CAdversary> enemies;

	//The coordinate of the Robot's Goal
	CPoint goalCoord;
	
	//intialise the Cadversary Vector
	void InitEnemies();

	//Required Functions for Game Loop
	void ClearScreen();
	void Update();
	void display();
	void timerUpdate();
	
	//Used to control FrameCOunt along with GAMESPEED
	double frameCount;
	double startTime;
	double endTime;
};

#endif
