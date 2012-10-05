#ifndef CPOINT_H
#define CPOINT_H

//CPoint.h


class CPoint
{
private:
	double iX;
	double iY;

public:
	// Constructors
	CPoint(int x, int y):iX(x), iY(y){} // TODO: int to double
	CPoint(void):iX(0), iY(0){}

	void X(double x){ iX = x; }
	void Y(double y){ iY = y; }
	double X(void){ return iX; }
	double Y(void){ return iY; }
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