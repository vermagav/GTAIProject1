/*
 * @Purpose: Home of the main() function
 * 
 */
#include "_config.h"
#include "CWorld.h"
#include <conio.h>
#include <iostream>

using std::cout;

int main()
{
	long double winCount = 0;
	long double loseCount = 0;

	for(long double i = 1; i <= 1.7e307; i++)
	{
		// Create a World State object and run the main game loop
		CWorld world;
		
		// Increment Win and Loss Count
		if(world.Run() == GAMESTATE_WIN)
			winCount++;
		else
			loseCount++;
		system("CLS");
		cout<<"Running simulation for "<<NUM_ENEMIES<<" enemies...\n";
		cout<<"\nWin Count:\t"<<winCount;
		cout<<"\nLose Count:\t"<<loseCount;
	}

	getch();
	return 0;
}