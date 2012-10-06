#include "CHomeObject.h";
#include <algorithm>
#include <utility>
#include <map>

using std::string;
using std::vector;
using std::pair;
using std::map;
using std::make_pair;


//utility functions : Distance, Compare and operator <
//Used to calculate Distance Between Point and the Coord while sorting
double CPointDistance(CPoint a, CPoint b)
{
	return sqrt((double)((a.X() - b.X()) * (a.X() - b.X()) + (a.Y() - b.Y()) * (a.Y() - b.Y())));
}

//Use to compare two two Cpoints depending on their distance from coord
bool Compare(pair<CPoint, double> a, pair<CPoint, double> b)
{
	//check > or <
	return (a.second < b.second);
}

//Used to Compare two Points for the Map data strucutre automatic sorting
bool operator < (CPoint a, CPoint b)
{
	return (a.X() == b.X()) ? (a.Y() < b.Y()): (a.X() < b.X());
}


//takes the vector of all adversary points locations
void CHomeObject::MoveObject(vector<CPoint> points)
{
	//data strucutre for our convenience: size same as points 
	vector<pair<CPoint, double> > distance(points.size());

	//calulate the corresponding distance to coord for every point, make a pair and store it
	for(vector<CPoint>::size_type i = 0; i != points.size(); i++)
		distance[i] = make_pair(points[i], CPointDistance(points[i], coord));
	
	//sort according to distance from coord 
	sort(distance.begin(), distance.end(), Compare);	

	//clear points vector
	points.clear();

	//get sorted points from pair structure
	for(vector<pair<CPoint, double> >::size_type i = 0; i != distance.size(); i++)
		points[i] = distance[i].first; 

	//After sorting call, compute relevant nodes and calculate Path Nodes(Vornoi Nodes) using this relevant nodes
	//Select the Min weight Node and move to it
	MoveToNode(ComputeNodes(ComputeRelevant(points)));	
}

vector<CPoint> CHomeObject::ComputeRelevant(vector<CPoint> points)
{
	//the vector to store all rlevent nodes
	vector<CPoint> releventNodes;

	//radius is given by distance of second farthest element + buffer
	double radius = CPointDistance(points[1], coord) + RADIUS_BUFFER;

	//add all points to relNodes vector whose distance to coord is less than Radius or until we reach the end(all points within radius)
	for(vector<CPoint>::const_iterator i = points.begin(); i != points.end() && (CPointDistance((*i), coord)) <= radius; i++)
		releventNodes.push_back(*i);

	return releventNodes; 
}

vector<CPoint> CHomeObject::ComputeNodes(vector<CPoint> relPoints)
{
	//Get the number of relevant Nodes and Store it in size
	const size_t size = relPoints.size();

	//Create to arrays to hold the X and Y coordinates. Largest size = NUM_ENEMIES
	float x[NUM_ENEMIES];
	float y[NUM_ENEMIES];
	
	//Store X and Y values in the arrays
	for(size_t i = 0; i != size; i++)
	{
		x[i] = (float)relPoints[i].X();
		y[i] = (float)relPoints[i].Y();
	}

	//Generate the Voronoi and reset the Iterators
	vdg.generateVoronoi(x, y, size, (float)-MAX_X, (float)MAX_X, (float)-MAX_Y, (float)MAX_Y, 3);
	vdg.resetIterator();

	//store all the lines to be drawn: Graphics purposes
	//vector< pair<CPoint, CPoint> > voronoiLines;
	
	vector<CPoint> pathNodes;
	//Intermediate data strucute used to get all PathNodes
	map<CPoint, int> relNodes;

	float x1,y1,x2,y2;
	while(vdg.getNext(x1,y1,x2,y2))
	{
		//voronoiLines.push_back(make_pair(CPoint((int)x1, (int)y1), CPoint((int)x2, (int)y2)));
		
		//if x1, y1 are within the boundary, increment their count
		if(x1 >= MIN_X && x1 <= MAX_X && y1 >= MIN_Y && y1 <= MAX_Y)
			++relNodes[CPoint(x1, y1)];
		
		//if x2, y2 are within the boundary, increment their count
		if(x2 >= MIN_X && x2 <= MAX_X && y2>= MIN_Y && y2 <= MAX_Y)
			++relNodes[CPoint(x2, y2)];
	}

	for(map<CPoint, int>::const_iterator i = relNodes.begin(); i != relNodes.end(); i++)	
		if(i->second > 1)
			pathNodes.push_back(i->first);

	//return the Voronoi PathNodes
	return pathNodes;		
}

void CHomeObject::MoveToNode(vector<CPoint> pathNodes)
{
	
	if(!pathNodes.empty())
	{
		//Better solution club Cpoint and Weights into one data strucutre
		vector<double> weights(pathNodes.size());
	
		//calculate weights for all the nodes
		for(vector<CPoint>::size_type i = 0; i != pathNodes.size(); i++)
			weights[i] = (NODE_WEIGHTAGE_D1 *  CPointDistance(pathNodes[i], coord))
			+ (NODE_WEIGHTAGE_D2 * CPointDistance(pathNodes[i], CPoint(STARTX_GOALCOORD, STARTY_GOALCOORD)));

		//mind the index of smallest weight
		//Assume first element as Minimum
		double min = weights[0];
		int select_index = 0;

		for(vector<double>::size_type i = 0; i != weights.size(); i++)
			if(weights[i] < min)
			{
				min = weights[i];
				select_index = i;
			}
			
		//Move the Robot to actual Coord in pathNodes indexed by select_index
	
	}

	//No PathNodes: What To DO???
	//Also Near the Goal? What to do??
	//Add StartNode and GoalNode in Voronoi Calulation??
}