#include "CHomeObject.h"
#include <algorithm>
#include <utility>
#include <map>
#include <iostream>
#include <conio.h>

using std::string;
using std::vector;
using std::pair;
using std::map;
using std::make_pair;
using std::back_inserter;
using std::copy;
using std::cout;
using std::endl;


// Utility function: distance, compare and operator <
// Used to calculate distance between point and the coord while sorting
double CPointDistance(CPoint a, CPoint b)
{
	return sqrt((double)((a.X() - b.X()) * (a.X() - b.X()) + (a.Y() - b.Y()) * (a.Y() - b.Y())));
}

// Used to compare two CPoints depending on their distance from coord
bool Compare(pair<CPoint, double> a, pair<CPoint, double> b)
{
	//check > or <
	return (a.second < b.second);
}

// Used to compare two points for the map data strucutre automatic sorting
bool operator < (CPoint a, CPoint b)
{
	return (a.X() == b.X()) ? (a.Y() < b.Y()): (a.X() < b.X());
}

// Takes the vector of all adversary points' locations
vector<CPoint> CHomeObject::MoveObject(vector<CPoint> points)
{
	// Remove those Elements from the vector that have been passed
/*	vector<CPoint>::size_type i = 0; 
	while(i != points.size())
	{
		if(points[i].X() <= coord.X() && points[i].Y() <= coord.Y())
			points.erase(points.begin() + i);
		else
			i++;
	}
*/
	// Data strucutre for our convenience: size same as points
	vector<pair<CPoint, double> > distance;

	// Calulate the corresponding distance to coord for every point, make a pair and store it
	for(vector<CPoint>::size_type i = 0; i != points.size(); i++)
		distance.push_back(make_pair(points[i], CPointDistance(points[i], coord)));
	
	// Sort according to distance from coord
	sort(distance.begin(), distance.end(), Compare);

	// Clear points vector
	points.clear();

	// Get sorted points from pair structure
	for(vector<pair<CPoint, double> >::size_type i = 0; i != distance.size(); i++)
		points.push_back(distance[i].first);

	// After sorting call, compute relevant nodes and calculate Path Nodes(Vornoi Nodes) using this relevant nodes
	// Select the Min weight Node and move to it
	return MoveToNode(ComputeNodes(ComputeRelevant(points)));	
}

// Compute relevant set of adversaries
vector<CPoint> CHomeObject::ComputeRelevant(vector<CPoint> points)
{
	// The vector to store all rlevent nodes
	vector<CPoint> releventNodes;

	// Radius is given by distance of second farthest element + buffer
	double radius = CPointDistance(points[1], coord) + RADIUS_BUFFER;

	// Add all points to relevant nodes vector whose distance to coord is less than Radius or until we reach the end (all points within radius)
	for(vector<CPoint>::const_iterator i = points.begin(); i != points.end() && (CPointDistance((*i), coord)) <= radius; i++)
		releventNodes.push_back(*i);

	return releventNodes;
}

vector<CPoint> CHomeObject::ComputeNodes(vector<CPoint> relPoints)
{
	// Clear pathNodes for fresh computation of Voronoi nodes
	pathNodes.clear();
	
	vector<CPoint> boundaryNodes; 

	// Get the number of relevant Nodes and Store it in size
	for(vector<CPoint>::size_type i = 0; i != relPoints.size(); i++)
	{
		if(relPoints[i].X() < LEVEL_MAX_X/2 && relPoints[i].Y() < LEVEL_MAX_Y/2)
		{
			boundaryNodes.push_back(CPoint(relPoints[i].X(), 0));
			boundaryNodes.push_back(CPoint(0, relPoints[i].Y()));
		}
		else
			if(relPoints[i].X() >= LEVEL_MAX_X/2 && relPoints[i].Y() < LEVEL_MAX_Y/2)
			{
				boundaryNodes.push_back(CPoint(relPoints[i].X(), 0));
				boundaryNodes.push_back(CPoint(LEVEL_MAX_X, relPoints[i].Y()));
			}
			else
				if(relPoints[i].X() < LEVEL_MAX_X/2 && relPoints[i].Y() >= LEVEL_MAX_Y/2)
				{
					boundaryNodes.push_back(CPoint(relPoints[i].X(), LEVEL_MAX_Y));
					boundaryNodes.push_back(CPoint(0, relPoints[i].Y()));
				}
				else
					if(relPoints[i].X() >= LEVEL_MAX_X/2 && relPoints[i].Y() >= LEVEL_MAX_Y/2)
					{
						boundaryNodes.push_back(CPoint(relPoints[i].X(),LEVEL_MAX_Y));
						boundaryNodes.push_back(CPoint(LEVEL_MAX_X, relPoints[i].Y()));
					}
	}
	
	// Append boundaryNodes at the end of RelPoints
	copy(boundaryNodes.begin(), boundaryNodes.end(), back_inserter(relPoints));
/*
	vector<CPoint>::size_type i = 0; 
	while(i != relPoints.size())
	{
		if(relPoints[i].X() <= coord.X() && relPoints[i].Y() <= coord.Y())
			relPoints.erase(relPoints.begin() + i);
		else
			i++;
	}
*/
	const size_t size = relPoints.size();

	// Create to arrays to hold the X and Y coordinates. Largest size = NUM_ENEMIES
	float x[NUM_ENEMIES * 3];
	float y[NUM_ENEMIES * 3];
	
	// Store X and Y values in the arrays
	for(size_t i = 0; i != size; i++)
	{
		x[i] = (float)relPoints[i].X();
		y[i] = (float)relPoints[i].Y();
	}

	// Generate the Voronoi and reset the Iterators
	vdg.generateVoronoi(x, y, size, (float)-LEVEL_MAX_X, (float)LEVEL_MAX_X, (float)-LEVEL_MAX_Y, (float)LEVEL_MAX_Y, 3);
	vdg.resetIterator();

	//store all the lines to be drawn: Graphics purposes
	//vector< pair<CPoint, CPoint> > voronoiLines;
	
	//Intermediate data strucute used to get all PathNodes
	map<CPoint, int> relNodes;

	float x1,y1,x2,y2;
	while(vdg.getNext(x1,y1,x2,y2))
	{
		//voronoiLines.push_back(make_pair(CPoint((int)x1, (int)y1), CPoint((int)x2, (int)y2)));
		
		// If x1, y1 are within the boundary, increment their count
		if(x1 >= LEVEL_MIN_X && x1 <= LEVEL_MAX_X && y1 >= LEVEL_MIN_Y && y1 <= LEVEL_MAX_Y)
			++relNodes[CPoint((int)x1, (int)y1)];
		            
		// If x2, y2 are within the boundary, increment their count
		if(x2 >= LEVEL_MIN_X && x2 <= LEVEL_MAX_X && y2>= LEVEL_MIN_Y && y2 <= LEVEL_MAX_Y)
			++relNodes[CPoint((int)x2, (int)y2)];
	}

	for(map<CPoint, int>::const_iterator i = relNodes.begin(); i != relNodes.end(); i++)
		if(i->second > 1)
			pathNodes.push_back(i->first);

	// Return the Voronoi PathNodes
	return pathNodes;

}

vector<CPoint> CHomeObject::MoveToNode(vector<CPoint> pathNodes)
{
	
	if(!pathNodes.empty())
	{
		// Better solution: club Cpoint and Weights into one data strucutre
		vector<double> weights;
	
		// Calculate weights for all the nodes
		// Weightage = (NODE_WEIGHTAGE_D1 * Distance to Home Agent) + (NODE_WEIGHTAGE_D2 * Distance to Goal)
		for(vector<CPoint>::size_type i = 0; i != pathNodes.size(); i++)
			weights.push_back(((NODE_WEIGHTAGE_D1 *  CPointDistance(pathNodes[i], coord)) 
				   + (NODE_WEIGHTAGE_D2 * CPointDistance(pathNodes[i], CPoint(STARTX_GOAL, STARTY_GOAL)))));
		
		// Mind the index of smallest weight
		// Assume first element as Minimum
		double min = weights[0];
		int select_index = 0;

		for(vector<double>::size_type i = 0; i != weights.size(); i++)
			if(weights[i] < min)
			{
				min = weights[i];
				select_index = i;
			}
			
		// Move the Robot to actual Coord in pathNodes indexed by select_index
		targetNode = CPoint(pathNodes[select_index].X(), pathNodes[select_index].Y());

		// Output target Node
		std::cout<<"Target Node:"<<targetNode.X()<<", "<<targetNode.Y()<<endl;

		// Check for Free path to goal
		if(CPointDistance(coord, CPoint(STARTX_GOAL, STARTY_GOAL)) <= CPointDistance(targetNode, CPoint(STARTX_GOAL, STARTY_GOAL)))
			targetNode = CPoint(STARTX_GOAL, STARTY_GOAL);

		for(int i=0; i != STEP_SIZE_HOMEAGENT; i++)
		{
			
			if( targetNode.X() > coord.X() )
			{
				if( targetNode.Y() > coord.Y() )
				{
					coord.Down();
					coord.Right();
				}
				else
				{
					coord.Up();
					coord.Right();
				}
			}
			if( targetNode.X() < coord.X() )
			{
				if( targetNode.Y() > coord.Y() )
				{
					coord.Down();
					coord.Left();
				}
				else
				{
					coord.Up();
					coord.Left();
				}
			}
			
		}

	}

	//No PathNodes: What To DO???
	//Also Near the Goal? What to do??
	//Add StartNode and GoalNode in Voronoi Calulation??
	return pathNodes;
}