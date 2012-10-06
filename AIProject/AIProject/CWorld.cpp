#include "CWorld.h"
#include <stdlib.h>
#include <time.h>

using std::vector;

void CWorld::InitEnemies()
{
	srand(time(0));
	for(vector<CAdversary>::size_type i = 0; i != NUM_ENEMIES; i++)
	{
		int x = 0, y = 0;
		//Generate Random Numbers to store into x, y
		//Also add these 10, 20 to config as some constant
		
		x = 10 + rand() % (MAX_X - 20);
		y = 10 + rand() % (MAX_Y - 20);

		//Make sure x, y are within walls and not ontop of another agent

		//Add the CAdversary to Enemies
		enemies.push_back(CAdversary(i, x, y));
	}
}

void CWorld::run()
{
	return;
}