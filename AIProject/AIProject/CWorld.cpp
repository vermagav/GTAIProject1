#include "CWorld.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <conio.h>
#include <stdio.h>

using std::cout;
using std::endl;

using std::vector;

void CWorld::InitEnemies()
{
	srand(time(0));
	for(vector<CAdversary>::size_type i = 0; i != NUM_ENEMIES; i++)
	{
		int x = 0, y = 0;
		// Generate Random Numbers to store into x, y
		// Also add these 10, 20 to config as some constant
		
		x = 10 + rand() % (LEVEL_MAX_X - 20);
		y = 10 + rand() % (LEVEL_MAX_Y - 20);

		//Make sure x, y are within walls and not ontop of another agent

		//Add the CAdversary to Enemies
		enemies.push_back(CAdversary(i, x, y));
	}
}

void CWorld::run()
{
	// Increment counter
	int count = 0;
	
	// Handle to windows console
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	while(count != 50)
	{
		FillBuffer();
		UpdateState();
		DrawState(hConsole);
		++count;
		getch();
	}
	return;
}

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

	// Draw Goal Node on ScreenBuffer
	screenBuffer[goalCoord.Y()][goalCoord.X()] = 'G';

	//set the voronoi Points
	for(vector<CPoint>::size_type i = 0; i != vornoiPoints.size(); i++)
		screenBuffer[vornoiPoints[i].Y()][vornoiPoints[i].X()] = 'O';

	// Set HomeAgent's Coordinate to # on screenBuffer
	screenBuffer[robot.GetCoord().Y()][robot.GetCoord().X()] = '#';
}

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
		i->MoveRandom(RANDOM_EASY);
}


void CWorld::DrawState(HANDLE hConsole)
{
	// Clear the Screen
	system("CLS");
	
	// Display the Screen
	for(int i = LEVEL_MIN_Y; i <= LEVEL_MAX_Y; i++)
	{
		for(int j = LEVEL_MIN_X; j <= LEVEL_MAX_X; j++)
		{
			/* -- Temp Color Hack START (remove for final source) -- */
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
			/* -- Temp Color Hack END -- */
			
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

	
}
 