#ifndef CPOINT_H
#define CPOINT_H

//CPoint.h

class CPoint
{
private:
	int iX;
	int iY;

public:
	CPoint(int x, int y):iX(x), iY(y)
	{}

	int X(){ return iX; }
	int Y(){ return iY; }
	void Up(void){ iY++; }
	void Down(void){ iY--; }
	void Left(void){ iX--; }
	void Right(void){ iX++; }
	void Up(int n){ iY += n; }
	void Down(int n){ iY -= n; }
	void Left(int n){ iX -= n; }
	void Right(int n){ iX += n; }
};

#endif