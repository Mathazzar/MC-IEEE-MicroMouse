/*
Written by squidKnight
Last modified: 03/15/20
Purpose: hold all of the alorithm-related maze functions (scaning, solving, optimizing, etc.)
Status: UNFINISHED, NOT TESTED

NOTE: will probably need to divide functions into separate C files
NOTE: ONLY COMPATABLE IN SIMULATOR!! Need to translate and incorperate finished movement/sensor functions once algorithm in stable
NOTE: most of the simulator-based functions start with "API_" so any that have this prefix need to be replaced for the physical bot
*/

#define SIM_MODE //remove once outside of sim environment
#define INFINITY 1024 //highly unlikely to ever have this value for a distance, so can be "infinity"

//need to put these declarations in a separate header file...
void nodeInit(); //initialize nodeList
void scan(); //scans the maze
int nodeCheck(); //checks if current position is a node or not
int getID(int direction, int dist, int position[2]); //gets the ID of the current node
void stackInsert(int nodeCurrent[1][4]); //inserts new node into correct rank in stack based on distance

//NOTE: if multithreading, remove from global scope and pass via pointers instead
int nodeList[256][4] = {}; //first dimension is ranking in stack (second dimension: 0 = nodeID, 1= distance traveled from last node, 2 = backpath (previous node), 3 = node type (explorable or not))

#ifdef SIM_MODE
	#include "API.h"
	#include <stdio.h>
	void simLog(char* text) //modified from main.c in mms example (https://github.com/mackorone/mms-c)
	{
		fprintf(stderr, "%s\n", text);
		fflush(stderr);
	}

	int translate(int x, int y) //translates values from cartesian system used in simulator to 16x16 matrix node IDs
	{
		int nodeID = (x + (y * 16) + 1); //conversion from cartesian to matrixi
		fprintf(stderr, "\t\tNode ID: %d\n", nodeID);
		fflush(stderr);
		return nodeID;
	}

#endif

void nodeInit() //initialize nodeList
{
	simLog("Initializing nodeList...");
	
	//set all distances and backpaths to inifinity
	int i, j;
	for(i=2; i<254; i++) //node ID 0 does not exist and ID 1 is already recorded as start
	{
		for(j=0; j<3; j++)
		{
			nodeList[i][j] = INFINITY;
		}
	}

	//initialize start node (which will be first in the stack)
	nodeList[1][0] = 0; //set node ID to 1
	nodeList[1][1] = 0; //set start point to have a distance of 0
	nodeList[1][2] = 0; //set start point to have a backpath of 1 (to self)
	nodeList[1][3] = 0; //set start point to have a node type of 0 (non-explorable, not a real node)
	API_setColor(0,0,'Y'); //visual mark
	API_setText(0, 0, "start");

	//mark goal position (IDs of 120, 121, 136, 137)
	API_setColor(7,7,'Y');
	API_setColor(7,8,'Y');
	API_setColor(8,8,'Y');
	API_setColor(8,7,'Y');
	API_setText(7, 7, "Goal");
	API_setText(7, 8, "Goal");
	API_setText(8, 8, "Goal");
	API_setText(8, 7, "Goal");

	simLog("Initilization completed\n- - - - -");
	scan(); //using pointer instead of global definition of nodeList (allows for potential to multi-thread)
}

void scan() //will A* be incorperated into this step?
{
	int position[2] = {0, 0}; //current x and y position
	int dist = 0; //0 = up, 1 = down, 2 = right, 3 = left
	int direction = 0; //stores current orentation, 0 is starting orientation
	int nodePrevious = 1; //stores the ID of the previous node

	simLog("Begining maze scan...");
	int nodeClass = nodeCheck(); //temporarily stores a node's class: path node, corner, or deadend
	while(nodeClass == 0) //waits until there is a node detected
	{
		API_moveForward();
		dist ++; //this needs to be replaced with motor functions to determie wall lengths traveled
		nodeClass = nodeCheck();
	}
	simLog("\tEncountered node:");
	int nodeID = getID(direction, dist, position);
	
	//do what needs to be done, depending on case
	if(nodeClass == -1) //if deadend
	{
		simLog("\t\tNode class: Dead-end\n\t\tReturning to previous node...");
		API_setColor(position[0], position[1], 'R');
	}
	if(nodeClass == 1) //if maze node
	{
		simLog("\t\tNode class: Path node\n\t\tRecording node information...");
		API_setColor(position[0], position[1], 'B');
	
		int nodeCurrent[1][4] = {}; //stores all information on current node
		nodeCurrent[0][0] = nodeID; //node ID
		nodeCurrent[0][1] = dist; //distance traveled
		nodeCurrent[0][2] = nodePrevious; //backpath
		nodeCurrent[0][3] = 1; //is an explorable node
		nodePrevious = nodeID; //current node will be the next one's backpath
		stackInsert(nodeCurrent);
	}
	if(nodeClass == 2) //if corner
	{
		simLog("\t\tNode class: Corner\n\t\tRecording node information...");
		API_setColor(position[0], position[1], 'G');
		int nodeCurrent[1][4] = {}; //stores all information on current node
		nodeCurrent[0][0] = nodeID; //node ID
		nodeCurrent[0][1] = dist; //distance traveled
		nodeCurrent[0][2] = nodePrevious; //backpath
		nodeCurrent[0][3] = 0; //is NOT an explorable node
		nodePrevious = nodeID; //current node will be the next one's backpath
		stackInsert(nodeCurrent);
	}
}

void stackInsert(int nodeCurrent[1][4]) //adds new node into correct rank in stack based on distance
{
	simLog("\t\tInserting node to stack...");
	int i, j;
	int tempArr[1][4] = {};
	for(i=1; i<257; i++)
	{
		if(nodeList[i-1][1] < nodeCurrent[0][1] && nodeList[i][1] > nodeCurrent[0][1]) //if node higher in stack is less in distance and node lower in stack is greater in distance  than current now (ie, distance of current node lies inbetween those two values)
		{
			//move information of node in ranking below current node to temporary array
			tempArr[0][0] = nodeList[i][0];
			tempArr[0][1] = nodeList[i][1];
			tempArr[0][2] = nodeList[i][2];
			tempArr[0][3] = nodeList[i][3];

			//insert information of current node where lesser-ranked node was
			nodeList[i][0] = nodeCurrent[0][0];
			nodeList[i][1] = nodeCurrent[0][1];
			nodeList[i][2] = nodeCurrent[0][2];
			nodeList[i][3] = nodeCurrent[0][3];
			break;
		}
	}

	//demote all nodes in lesser rankings
	for(j=i+1; j<256; j++)
	{
		//move next node to be replaced into temporary storage
		tempArr[0][0] = nodeList[j][0];
		tempArr[0][1] = nodeList[j][1];
		tempArr[0][2] = nodeList[j][2];
		tempArr[0][3] = nodeList[j][3];

		//insert information into one rank lower than previous position
		nodeList[j+1][0] = tempArr[0][0];
		nodeList[j+1][1] = tempArr[0][1];
		nodeList[j+1][2] = tempArr[0][2];
		nodeList[j+1][3] = tempArr[0][3];
	}
	fprintf(stderr, "\t\tRank of new node: %d \n",i);
	fflush(stderr);
}

int getID(int direction, int dist, int position[2]) //gets the ID of the current node
{
	//determine change based on direction
	if(direction == 0) //if facing up
		position[1] += dist; //y position increased (normally, this would be incremented in accordance to the matrix by recorded traveled distance)
	if(direction == 1) //if facing down
		position[1] -= dist;
	if(direction == 2) //if facing right
		position[0] += dist; //x position increased
	if(direction == 3) //if facing left
		position[0] -= dist;

	//translate to matrix format, this can be removed once outside of simulator
	return translate(position[0], position[1]);
}

int nodeCheck() //checks if current position is a node or not
{
	//count number of avalible paths
	int status, paths = 3;
	if(API_wallFront()) //NOTE: the simulator cannot detect walls that are not next to it (this implementation will need to change for physical bot)
		paths--;
	if(API_wallRight())
		paths--;
	if(API_wallLeft())
		paths--;

	//determine status
	switch (paths)
	{
		case 0: //deadend
			status = -1;
			break;
		case 1: //not a normal node: is it a corner or a clear path?
			status = 0; //assume it will be a clear path
			if(API_wallFront()) //corner condition
				status = 2;
			break;
		case 2: //is a node, add to stack
			status = 1;
			break;
		default:
			status = -2; //should not happen...
	}
	return status;
}

void solve() //not sure if needed, may be able to do in scan() by nature of dijkstras
{
}

void optimize() //optimizes path by utilizing diagonals
{
}
