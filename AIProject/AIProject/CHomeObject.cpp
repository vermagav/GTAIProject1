#include "CHomeObject.h"

using std::priority_queue;
using std::string;
using std::vector;

//takes the vector of all adversary points
void CHomeObject::MoveObject(vector<CPoint> points)
{
	MoveToNode(ComputeNodes(ComputeRelevant(points)));
}

priority_queue<CPoint> CHomeObject::ComputeRelevant(vector<CPoint> points)
{
	//change name of arg points to sumthing relevant

}

vector<CPoint> CHomeObject::ComputeNodes(priority_queue<CPoint> points)
{	
	//change name of arg points to sumthing relevant
	return voronoi.ComputeVoronoi(points);
}

void CHomeObject::MoveToNode(vector<CPoint> points)
{

}