#ifndef CPOINT_H
#define CPOINT_H

//CPoint.h
#include <math.h>
#include "_config.h"

class CPoint
{
private:
	int iX;
	int iY;
	
public:
	// Constructors
	CPoint(int x, int y):iX(x), iY(y){}
	CPoint(void):iX(0), iY(0){}

	// Get and Set functions
	void X(int x){ iX = x; }
	void Y(int y){ iY = y; }
	int X(void){ return iX; }
	int Y(void){ return iY; }
	
	// Move function for moving the adversary in a particular direction
	void inline Move(int x1, int y1)
	{
		iX += x1 * STEP_SIZE_ADVERSARY;
		iY += y1 * STEP_SIZE_ADVERSARY;
		
		if(iX < LEVEL_MIN_X)
			iX = LEVEL_MIN_X;

		if(iX > LEVEL_MAX_X)
			iX = LEVEL_MAX_X;

		if(iY < LEVEL_MIN_Y)
			iY = LEVEL_MIN_Y;

		if(iY > LEVEL_MAX_Y)
			iY = LEVEL_MAX_Y;
	}

	// Public directional movement functions by 1 step
	void Up(void){ Move(0, -1); }
	void Down(void){ Move(0, 1); }
	void Left(void){ Move(-1, 0); }
	void Right(void){ Move(1, 0); }

	// Public directional movement functions by n step
	void Up(int n){ Move(0, -n); }
	void Down(int n){ Move(0, n); }
	void Left(int n){ Move(-n, 0); }
	void Right(int n){ Move(n, 0); }
};

#endif