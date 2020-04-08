//#include "API.h"

#define INFINITY 1024
#define DATA 7

void simLog(char* text); //modified from main.c in mms example (https://github.com/mackorone/mms-c)

void nodeInit(int nodeList[256][DATA]) //initialize nodeList
{
	simLog("Initializing nodeList...");

	//set all distances and backpaths to inifinity
	int i, j;
	for (i = 0; i<256; i++)
	{
		for (j = 0; j < DATA; j++)
		{
			nodeList[i][j] = INFINITY;
		}
	}

	//initialize start node (which will be first in the stack)
	nodeList[0][0] = 1; //set node ID to 1
	nodeList[0][1] = 0; //set start point to have a distance of 0
	nodeList[0][2] = 1; //set start point to have a backpath of 1 (to self)
	if (!API_wallLeft())
		nodeList[0][3] = 0; //if no wall, set distance to next path on left to 0
	if (!API_wallFront())
		nodeList[0][4] = 0; //if no wall, set distance to next path to front to 0
	if (!API_wallRight())
		nodeList[0][5] = 0; //if no wall, set distance to next path on right to 0
	nodeList[0][6] = 0; //set start point to have no unexplored paths

	API_setColor(0, 0, 'Y'); //visual mark
	API_setText(0, 0, "start");

	//mark goal position (IDs of 120, 121, 136, 137)
	API_setColor(7, 7, 'Y');
	API_setColor(7, 8, 'Y');
	API_setColor(8, 8, 'Y');
	API_setColor(8, 7, 'Y');
	API_setText(7, 7, "Goal");
	API_setText(7, 8, "Goal");
	API_setText(8, 8, "Goal");
	API_setText(8, 7, "Goal");

	simLog("Initilization completed\n- - - - -");
}