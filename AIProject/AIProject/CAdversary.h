#ifndef CADVERSARY_H
#define CADVERSARY_H

//Cadversary.h v1.0

#include "CHomeObject.h"

class CAdversary
{

public:
	//Movement for the Adversaries, Mode sets Difficulty Level
	void MoveRandom(DifficultyMode m);

	//Constructors
	CAdversary(int id, int x, int y, CPoint h = CPoint()):iId(id), iStepSize(STEP_SIZE_ADVERSARY),
															coord(CPoint(x, y)), homeCoord(h){}

	CPoint getCoord() const
	{
		return coord;
	}

	void SetCoord(CPoint p)
	{
		//check point within boundaries
		coord = p;
	}

	//used to set the HomeCoord for every time Robot Moves: Intelligent AI
	void SetHomeCoord(CPoint g)
	{
		homeCoord = g;
	}

private:
	int iId;
	int iStepSize;
	CPoint coord;
	CPoint homeCoord;  //  homeCoord will be robots coord for Intelligent AI and for distance
};

#endif