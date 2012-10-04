#ifndef CADVERSARY_H
#define CADVERSARY_H

//Cadversary.h v1.0
#include "CPoint.h"
#include "_config.h"


class CAdversary
{

public:

	void MoveRandom(DifficultyMode m);

	CAdversary(int x, int y):iId(0), iStepSize(STEP_SIZE_ADVERSARY), coord(CPoint(x, y))
	{}

private:
	int iId;
	int iStepSize;
	CPoint coord;
};

#endif
