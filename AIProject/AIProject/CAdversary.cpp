#include "CAdversary.h"
#include <stdlib.h>
#include <time.h>


void CAdversary::MoveRandom(DifficultyMode m)
{
	srand(time(NULL));
	int move = rand() % 4;
	/// TODO:Wall cases
	switch(m)
	{
		case RANDOM_EASY:
			{
				switch(move)
				{
				case 0: coord.Right();
						break;

				case 1: coord.Left();
						break;

				case 2: coord.Up();
						break;

				case 3: coord.Down();
						break;
				}
				break;

			case RANDOM_NORMAL:
				break;

			case RANDOM_INTELLIGENT:
				break; 
	 
		}
	}

}

