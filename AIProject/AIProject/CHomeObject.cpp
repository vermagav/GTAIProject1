#include "CHomeObject.h"

using std::string;
using std::vector;

//takes the vector of all adversary points
void CHomeObject::MoveObject(vector<CPoint> points)
{
	MoveToNode(ComputeNodes(ComputeRelevant(points)));
}

vector<CPoint> CHomeObject::ComputeRelevant(vector<CPoint> points)
{
	/// TODO: change name of arg points to something relevant
	return points; // temp
}

vector<CPoint> CHomeObject::ComputeNodes(vector<CPoint> points)
{	
	/// TODO: change name of arg points to something relevant
	return voronoi.ComputeVoronoi(points);
}

void CHomeObject::MoveToNode(vector<CPoint> points)
{

}