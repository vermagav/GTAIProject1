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
	// Create a World State object and run the main game loop
	CWorld world;
		
	//Call Run 
	world.Run();

	getch();
	return 0;
}