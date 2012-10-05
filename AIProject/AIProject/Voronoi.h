#ifndef VORONOI_H
#define VORONOI_H

//Voronoi.h
#include <queue>
#include <set>
#include<vector>
#include <math.h>
#include "CPoint.h"

using std::vector;

class Voronoi
{
public:
	vector<CPoint> ComputeVoronoi(vector<CPoint> points);	
};

#endif
 
