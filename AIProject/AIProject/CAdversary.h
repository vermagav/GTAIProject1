#ifndef CADVERSARY_H
#define CADVERSARY_H

//Cadversary.h v1.0
#include "Point.h"


enum Mode{
RANDOM_EASY,
RANDOM_NORMAL,
RANDOM_INTELLIGENT,
NUM_OF_MODES
};

class CAdversary
{

public:
	const int STEP_SIZE = 1;

	void MoveRandom(Mode m);

	CAdversary(int x, int y):iId(0), iStepSize(STEP_SIZE), coord(Point(x, y))
	{}

protected:
	int iId;
	int iStepSize;
	Point coord;
};

#endif
