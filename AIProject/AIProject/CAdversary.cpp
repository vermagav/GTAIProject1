#include "CAdversary.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

// temp
using namespace std;



void CAdversary::MoveRandom(DifficultyMode m)
{
	switch(m)
	{
		// rand()%3 -1 generates either -1, 0, 1...
		case RANDOM_EASY: coord.Move(rand() % 3 - 1, rand() % 3 - 1);
			break;
		
		// All players will home in on the robot - Use Only on Some
		case RANDOM_NORMAL:
			{
				
				float x = goalCoord.X() - coord.X();
				float y = goalCoord.Y() - coord.Y();
			
				float magnitude = sqrt((x * x + y * y));
				x /= magnitude;
				y /= magnitude;
				
				if(x <= -0.5)
					coord.Left(STEP_SIZE_ADVERSARY);
				else
					if(x >= 0.5)
						coord.Right(STEP_SIZE_ADVERSARY);

				if(y <= -0.5)
					coord.Up(STEP_SIZE_ADVERSARY);
				else
					if(y >= 0.5)
						coord.Down(STEP_SIZE_ADVERSARY);

			}
			break;

		case RANDOM_INTELLIGENT:
			break;
	}
}
