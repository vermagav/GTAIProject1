#include "CHomeObject.h"

vector<Point> CHomeObject::CalcVoronoi(priority_queue<Point> points)
{
	return voronoi.calcVoronoi(points);
}

