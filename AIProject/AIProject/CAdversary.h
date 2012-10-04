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
	void MoveRandom(Mode m);

protected:
	int iId;
	int iStepSize;
	Point coord;
};

#endif
