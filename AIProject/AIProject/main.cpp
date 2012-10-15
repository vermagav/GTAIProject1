/*
 * @Purpose: Home of the main() function
 * 
 */
#include "_config.h"
#include "CWorld.h"
#include <conio.h>
#include <iostream>

using std::cout;

/* -- Temp Start -- */
void RunOnce(CWorld *world)
{
	world->Run();
	getch();
}

void RunSimulation(CWorld *world)
{
	// Counters
	long double winCount = 0;
	long double loseCount = 0;

	// Loop multiple simulations
	for(long double i = 1; i <= 1.7e307; i++)
	{
		world = new CWorld;

		// Increment Win and Loss Count
		if(world->Run() == GAMESTATE_WIN)
			winCount++;
		else
			loseCount++;
		
		// Output counter information
		system("CLS");
		cout<<"Running simulation for "<<NUM_ENEMIES<<" enemies...\n";
		cout<<"\nWin Count:\t"<<winCount;
		cout<<"\nLose Count:\t"<<loseCount;
		
		delete world;
	}
}
/* -- Temp End -- */

int main()
{
	// Create a World State object and run the main game loop
	CWorld *world = new CWorld;
		
	// Run once
	RunOnce(world);

	// Run simulation
	//RunSimulation(world);

	return 0;
}