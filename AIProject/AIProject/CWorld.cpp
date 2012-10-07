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
	InitState();
	DrawState();

	return;
}

void CWorld::InitState()
{
	// Initialise the Entire Level to '.'
	//Y is outer Loop...X is Inner
	for(int i = LEVEL_MIN_Y; i <= LEVEL_MAX_Y; i++)
		for(int j = LEVEL_MIN_X; j <= LEVEL_MAX_X; j++)
			screenBuffer[i][j] = '.';

	// Set HomeAgent's Coordinate to # on screenBuffer
	screenBuffer[robot.GetCoord().Y()][robot.GetCoord().X()] = '#';

	// Cycle through each adversary and set position to 'X'
	for(vector<CAdversary>::const_iterator i = enemies.begin(); i != enemies.end(); i++)
		screenBuffer[i->getCoord().Y()][i->getCoord().X()] = 'X';

	// Draw Goal Node on ScreenBuffer
	screenBuffer[goalCoord.Y()][goalCoord.X()] = 'G';
}

void CWorld::UpdateState()
{
	//
}


void CWorld::DrawState()
{
	// Clear the Screen
	system("CLS");
	
	// Display the Screen
	for(int i = LEVEL_MIN_Y; i <= LEVEL_MAX_Y; i++)
	{
		for(int j = LEVEL_MIN_X; j <= LEVEL_MAX_X; j++)
			cout<< screenBuffer[i][j] ;
		cout<<endl;
	}
}
