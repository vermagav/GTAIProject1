#ifndef CHOME_OBJECT
#define CHOME_OBJECT

//CHomeObject v1.0
#include "_config.h"
#include "CPoint.h"
#include "VoronoiDiagramGenerator.h"
#include<string>
#include<vector>
/*
	Main algorithm:
		1. Compute Radius
			a. Compute distance between home agent and FIRST TWO adversaries in priority queue
			b. Radius = distance to second farthest agent + radius buffer
				Radius = Dist(HomeAgent, 2nd Adversary) + RADIUS_BUFFER
		2. Calculate which objects fall within new final radius = RELEVANT OBJECTS
		3. Calculate <PATH NODES> using Voronoi diagram on these RELEVANT OBJECTS
		4. Assign weightage to each <PATH NODE> based on:
			a. Distance from goal (NODE_WEIGHTAGE_D1)
			b. Distance from closest objects (NODE_WEIGHTAGE_D2)
			// c. Clutter-density factor
				Weightage = (NODE_WEIGHTAGE_D1 * Distance to Home Agent) + (NODE_WEIGHTAGE_D2 * Distance to Goal)
				Take the LOWEST weightage and use that as the <FAVORABLE NODE> to move to
		5. Move one step towards <FAVORABLE NODE>
*/



class CHomeObject
{
public:
	//COnstructor...//vdg???
	CHomeObject(int x, int y): coord(CPoint(x, y)), strName("Robot"), iStepSize(STEP_SIZE_HOMEAGENT) {}  

	/*
	 * Main function for moving the home agent.
	 * This function calls all other private functions the various steps in our algorithm.
	 */
	void MoveObject(std::vector<CPoint> points); // Calls private functions for steps 1-5
	
	CPoint GetCoord() const
	{
		return coord;
	}

	void SetCoord(CPoint p)
	{
		//check point within boundaries
		coord = p;
	}

private:
	std::vector<CPoint> ComputeRelevant(std::vector<CPoint> points); // 1, 2
	std::vector<CPoint> ComputeNodes(std::vector<CPoint> relNodes); // 3
	void MoveToNode(std::vector<CPoint> points); // 4, 5
	
	
	CPoint coord;
	std::string strName;
	int iStepSize;
	VoronoiDiagramGenerator vdg;
};

#endif