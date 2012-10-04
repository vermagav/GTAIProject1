#ifndef POINT_H
#define POINT_H

//Point.h

class Point
{
private:
	int iX;
	int iY;

public:
	Point(int x, int y):iX(x), iY(y)
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