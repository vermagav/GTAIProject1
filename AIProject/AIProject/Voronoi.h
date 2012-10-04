#ifndef VORONOI_H
#define VORONOI_H

//Voronoi.h
#include <queue>
#include <set>
#include<vector>
#include <math.h>
#include "CPoint.h"

using std::vector;
using std::priority_queue;

class Voronoi
{
public:
	vector<CPoint> ComputeVoronoi(priority_queue<CPoint> points);	
};

#endif
 
