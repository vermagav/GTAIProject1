#ifndef C_HOME_OBJECT
#ifndef CHOME_OBJECT
#define CHOME_OBJECT

//CHomeObject v1.0
#include<string>
#include<queue>
#include<vector>
#include "Voronoi.h"

using std::priority_queue;
using std::string;
using std::vector;

class CHomeObject
{
public:
	vector<Point> CalcVoronoi(priority_queue<Point> points);

protected:
	Point coord;
	string strName;
};


#endif