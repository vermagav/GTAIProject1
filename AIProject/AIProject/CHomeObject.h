#ifndef CHOME_OBJECT
#define CHOME_OBJECT

//CHomeObject v1.0
#include<string>
#include<queue>
#include<vector>
#include "Voronoi.h"
#include "_config.h"

/*
	Main algorithm:
		1. Compute Radius
		2. Calculate which objects fall within radius
		3. Calculate nodes using Voronoi diagram on these objects
		4. Assign weightage to each node based on:
			a. Distance from goal
			b. Distance from closest objects
			c. Clutter-density factor
		5. Move one step towards favorable node
*/

class CHomeObject
{
public:
	/*
	 * Main function for moving the home agent.
	 * This function calls all other private functions the various steps in our algorithm.
	 */
	void MoveObject(vector<CPoint> points); // Calls private functions for steps 1-5

private:
	std::vector<CPoint> ComputeRelevant(std::vector<CPoint> points); // 1, 2
	std::vector<CPoint> ComputeNodes(std::vector<CPoint> points); // 3
	void MoveToNode(std::vector<CPoint> points); // 4, 5
	
	CPoint coord;
	std::string strName;
	Voronoi voronoi;
};


#endif