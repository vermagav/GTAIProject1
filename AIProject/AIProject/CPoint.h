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
	CPoint(int x, int y):iX(x), iY(y){} // TODO: int to int
	CPoint(void):iX(0), iY(0){}

	//get and set functions
	void X(int x){ iX = x; }
	void Y(int y){ iY = y; }
	int X(void){ return iX; }
	int Y(void){ return iY; }
	
	
	void inline Move(int x1, int y1)
	{
		iX += x1;
		iY += y1;
		
		if(iX < MIN_X)
			iX = MIN_X;

		if(iX > MAX_X)
			iX = MAX_X;

		if(iY < MIN_Y)
			iY = MIN_Y;

		if(iY > MAX_Y)
			iY = MAX_Y;

	}
	
	void Up(void)
	{
		Move(0, -1);
	}
	
	void Down(void)
	{
		Move(0, 1);
	}

	void Left(void)
	{ 
		Move(-1, 0); 
	}

	void Right(void)
	{
		Move(1, 0); 
	}

	void Up(int n)
	{
		Move(0, -n); 
	}

	void Down(int n)
	{
		Move(0, n); 
	}

	void Left(int n)
	{
		Move(-n, 0);
	}

	void Right(int n)
	{
		Move(n, 0);
	}
};

#endif