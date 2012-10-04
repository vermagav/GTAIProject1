#ifndef CWORLD
#define CWORLD

//CWorld.h
#include"CAdversary.h"
#include"CHomeObject.h"

class CWorld
{

public:

private:
	// Our home agent
	CHomeObject robot;
	// The enemies that oppose our home agent
	std::vector<CAdversary> enemies;
	

};


#endif