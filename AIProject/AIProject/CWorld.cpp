#include "CWorld.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <conio.h>
#include <stdio.h>

using std::cout;
using std::endl;
using std::vector;

/* Initialize enemies and spawn them randomly in our environment */
void CWorld::InitEnemies()
{
	int x, y;
	for(vector<CAdversary>::size_type i = 0; i != NUM_ENEMIES/5; i++)
	{
		x = 0;
		y = 0;
		// Generate Random Numbers to store into x, y
		// Also add these 10, 20 to config as some constant
		
		x = 10 + rand() % (LEVEL_MAX_X - 10);
		y = 10 + rand() % (LEVEL_MAX_Y - 10);

		// Make sure x, y are within walls and not ontop of another agent

		// Add the CAdversary to Enemies
		enemies.push_back(CAdversary(i, x, y));
	}
	for(vector<CAdversary>::size_type i = 0; i != (3*NUM_ENEMIES)/5; i++)
	{
		x = 0;
		y = 0;
		// Generate Random Numbers to store into x, y
		// Also add these 10, 20 to config as some constant
		
		x = 10 + rand() % (LEVEL_MAX_X - 10);
		y = 10 + rand() % (LEVEL_MAX_Y - 10);

		// Make sure x, y are within walls and not ontop of another agent

		// Add the CAdversary to Enemies
		enemies.push_back(CAdversary(i, x, y));
	}
	for(vector<CAdversary>::size_type i = 0; i != NUM_ENEMIES/5; i++)
	{
		x = 0;
		y = 0;
		// Generate Random Numbers to store into x, y
		// Also add these 10, 20 to config as some constant
		
		x = 10 + rand() % (LEVEL_MAX_X - 10);
		y = 10 + rand() % (LEVEL_MAX_Y - 10);

		// Make sure x, y are within walls and not ontop of another agent

		// Add the CAdversary to Enemies
		enemies.push_back(CAdversary(i, x, y));
	}

}

/* Main game world looping function */
GameState CWorld::Run()
{
	// Handle to windows console, used for changing colors
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	while(RobotGameState == GAMESTATE_RUNNING)
	{
		FillBuffer();
		UpdateState();
		CheckState();
		DrawState(hConsole);
		//getch();
	}
	return RobotGameState;
}

/* Check state of the game world and update based on the Home Agent's coordinates */
void CWorld::CheckState()
{
	// Condition 1: Check if Robot Won
	if(  ((robot.GetCoord().X() >= STARTX_GOAL - WIN_BUFFER) && (robot.GetCoord().X() <= STARTX_GOAL + WIN_BUFFER))
	  && ((robot.GetCoord().Y() >= STARTY_GOAL - WIN_BUFFER) && (robot.GetCoord().Y() <= STARTY_GOAL + WIN_BUFFER)) )
	{
		RobotGameState = GAMESTATE_WIN;
	}else
	// Condition 2: Check if Robot Failed
		for(vector<CPoint>::size_type i = 0; i != enemies.size(); i++)
		{
			if(robot.GetCoord().X() == enemies[i].getCoord().X() && robot.GetCoord().Y() == enemies[i].getCoord().Y())
				RobotGameState = GAMESTATE_FAIL;
		}
}

/* Populate the screen buffer in our textual representation of the game world */
void CWorld::FillBuffer()
{
	// Initialise the Entire Level to '.'
	//Y is outer Loop...X is Inner
	for(int i = LEVEL_MIN_Y; i <= LEVEL_MAX_Y; i++)
		for(int j = LEVEL_MIN_X; j <= LEVEL_MAX_X; j++)
			screenBuffer[i][j] = '.';

	// Cycle through each adversary and set position to 'X'
	for(vector<CAdversary>::const_iterator i = enemies.begin(); i != enemies.end(); i++)
		screenBuffer[i->getCoord().Y()][i->getCoord().X()] = 'X';

	//set the voronoi Points
	for(vector<CPoint>::size_type i = 0; i != vornoiPoints.size(); i++)
		screenBuffer[vornoiPoints[i].Y()][vornoiPoints[i].X()] = 'O';

	// Draw Goal Node on ScreenBuffer
	screenBuffer[goalCoord.Y()][goalCoord.X()] = 'G';

	// Set HomeAgent's Coordinate to # on screenBuffer (make sure # is last in this function)
	screenBuffer[robot.GetCoord().Y()][robot.GetCoord().X()] = '#';
}

/* Update the world state */
void CWorld::UpdateState()
{
	// Get All the Coords of the Enemies
	vector<CPoint> points;

	for(vector<CAdversary>::iterator i = enemies.begin(); i != enemies.end(); i++)
		points.push_back(i->getCoord());
	
	// Compute Voronoi for Robot and Move the Robot Step Size in Its Direction
	vornoiPoints = robot.MoveObject(points);

	//Call Random Motion on the Robots
	for(vector<CAdversary>::iterator i = enemies.begin(); i != enemies.end(); i++)
	{
		i->SetGoalCoord(robot.GetCoord());
		i->MoveRandom(RANDOM_NORMAL);
	}     
}

/* Output world state and several debug console messages */
void CWorld::DrawState(HANDLE hConsole)
{
	SetConsoleTextAttribute(hConsole, 7);

	// Clear the Screen
	system("CLS");

	// Display the Screen
	for(int i = LEVEL_MIN_Y; i <= LEVEL_MAX_Y; i++)
	{
		for(int j = LEVEL_MIN_X; j <= LEVEL_MAX_X; j++)
		{
			// Temp Color Hack START (remove for final source)
			if(screenBuffer[i][j] == '.')
				SetConsoleTextAttribute(hConsole, 8);
			if(screenBuffer[i][j] == 'G')
				SetConsoleTextAttribute(hConsole, 160);
			if(screenBuffer[i][j] == 'X')
				SetConsoleTextAttribute(hConsole, 12);
			if(screenBuffer[i][j] == 'O')
				SetConsoleTextAttribute(hConsole, 11);
			if(screenBuffer[i][j] == '#')
				SetConsoleTextAttribute(hConsole, 224);
			
			cout<<screenBuffer[i][j];
		}
		cout<<endl;
	}

	SetConsoleTextAttribute(hConsole, 15);
	cout<<"\n\n\nNumber of adversaries:\t\t"<<NUM_ENEMIES;
	cout<<"\nGoal Node:\t\t\t"<<STARTX_GOAL<<", "<<STARTY_GOAL;
	cout<<"\n\nSet of Relevant Nodes:\t\t[ ";
	vector<CPoint> relNodes = robot.GetPathNodes();
	for(vector<CPoint>::size_type i = 0; i != relNodes.size(); i++)
	{
		cout<<"{"<<relNodes[i].X()<<", "<<relNodes[i].Y()<<"} ";
	}
	cout<<"]";
	cout<<"\n\nHome Object Coord:\t\t"<<robot.GetCoord().X()<<", "<<robot.GetCoord().Y();
	cout<<"\nTarget Node:\t\t\t"<<robot.GetTargetNode().X()<<", "<<robot.GetTargetNode().Y();

	// Check if the Home Agent won the game
	if(RobotGameState == GAMESTATE_WIN)
	{
		SetConsoleTextAttribute(hConsole, 160);
		cout<<"\n\n\n\t\t\t\tVICTORY CONDITION ACHIEVED! The Home Agent has succesfully reached the Goal Node.";
	}
	// Check if the Home Agent lost the game
	else if(RobotGameState == GAMESTATE_FAIL)
	{
		SetConsoleTextAttribute(hConsole, 192);
		cout<<"\n\n\n\t\t\t\tALGORITHM FAILED! The Home Agent was captured by an adversary.";
	}
}