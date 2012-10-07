/*
 * @Purpose: Home of the main() function
 * 
 */
#include "_config.h"
#include "CWorld.h"
#include <conio.h>

int main()
{
	//Ceate the World and Run It
	CWorld world;

	world.run();

	getch();
	return 0;
}