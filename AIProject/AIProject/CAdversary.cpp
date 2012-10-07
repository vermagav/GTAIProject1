#include "CAdversary.h"
#include <stdlib.h>
#include <time.h>


void CAdversary::MoveRandom(DifficultyMode m)
{
	srand(time(0));
	int move = rand() % 4;
	/// TODO:Wall cases
	switch(m)
	{
		// rand()%3 -1 generates either -1, 0, 1...
		case RANDOM_EASY: coord.Move(rand() % 3 - 1, rand() % 3 - 1);
			break;
		
		// All players will home in on the robot - Use Only on Some
		case RANDOM_NORMAL:
			{
				/*
				float x = homeCoord.X() - coord.X();
				float y = homeCoord.Y() - coord.Y();
			
				float magnitude = sqrt((x * x + y * y));
				x /= magnitude;
				y /= magnitude;

				coord.Move((int)x, (int)y);
				*/
			}
			break;

		case RANDOM_INTELLIGENT:
			break;
	}
}