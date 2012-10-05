#include "CHomeObject.h"


using std::string;
using std::vector;

//takes the vector of all adversary points
void CHomeObject::MoveObject(vector<CPoint> points)
{
	//sort the points vector according to distance from robot coord


	//After sorting call, compute relevant nodes and calculate Path Nodes(Vornoi Nodes) using this relevant nodes
	//Select the Nin weight Node and move to it
	MoveToNode(ComputeNodes(ComputeRelevant(points)));
	
	
}

priority_queue<CPoint, vector<CPoint>, gt1> CHomeObject::ComputeRelevant(vector<CPoint> points)
{
	//the prirority queue to store all rlevent nodes
	priority_queue<CPoint, vector<CPoint>, gt1> releventNodes;

	//radius is given by distance of second farthest element + buffer
	double radius = Distance(points[1], coord) + RADIUS_BUFFER;

	//add all points to priority queue whose distance to coord is less than Radius or until we reach the end(all points within radius)
	for(vector<CPoint>::const_iterator i = points.begin(); i != points.end() && (Distance((*i), coord)) <= radius; i++)
		releventNodes.push(*i);

	return releventNodes; 
}

vector<CPoint> CHomeObject::ComputeNodes(priority_queue<CPoint, vector<CPoint>, gt1> relPoints)
{	
	return voronoi.ComputeVoronoi(relPoints);
}

void CHomeObject::MoveToNode(vector<CPoint> pathNodes)
{
	//Better solution club Cpoint and Weights into one data strucutre
	vector<double> weights(pathNodes.size());
	
	//calculate weights for all the nodes
	for(vector<CPoint>::size_type i = 0; i != pathNodes.size(); i++)
		weights[i] = (0.3 *  Distance(pathNodes[i], coord)) + (0.7 * Distance(pathNodes[i], goalCoord));

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

