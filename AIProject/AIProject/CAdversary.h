#ifndef CADVERSARY_H
#define CADVERSARY_H

//Cadversary.h v1.0

#include "CHomeObject.h"

class CAdversary
{

public:
	// Movement for the Adversaries, Mode sets Difficulty Level
	void MoveRandom(DifficultyMode m);

	// Constructors
	CAdversary(int id, int x, int y):iId(id), iStepSize(STEP_SIZE_ADVERSARY), coord(CPoint(x, y)){}

	CPoint getCoord() const
	{
		return coord;
	}

	void SetCoord(CPoint p)
	{
		// check point within boundaries
		coord = p;
	}

private:
	int iId;
	int iStepSize;
	CPoint coord;
};

#endif