#include <stdbool.h>
#include <stdio.h>
#include "API.h" //only needed for simulator use

#define INFINITY 1024
#define DATA 7

void simLog(char* text); //modified from main.c in mms example (https://github.com/mackorone/mms-c)
int nodeCheck();
void updatePos(int position[2], short int direction, short int dist);
short int updateDir(short int direction, short int relativeChange);
int getID(int position[2]);
short int choosePath(int nodeCurrent[6], int paths, short int direction, int position[2]);
bool stackInsert(int nodeList[256][DATA], int nodeCurrent[DATA]);

void scan(int nodeList[256][DATA])
{
	int position[2] = { 0, 0 };
	int distTotal = 0;
	short int distLastNode = 0;
	short int dist = 0;
	bool encounteredNode = false;
	short int direction = 0; //stores current orientation, 0 is starting direction (assumed to be upwards): 0 = up, 1 = right, 2 = down, 3 = left
	int nodePrevious = nodeList[0][0];
	int stack = 0;

	simLog("Begining maze scan...");
	while (1 == 1)
	{
		//reset distances traveled since last node
		if (encounteredNode)
		{
			short int distLastNode = 2;
			short int dist = 1;
			encounteredNode = false;
		}
		else
		{
			short int distLastNode = 0;
			short int dist = 0;
		}

		//continue till next node
		while (nodeCheck() == 0)
		{
			if (!API_wallFront())
			{
				API_moveForward();
				dist++;
			}
			else if (!API_wallRight())
			{
				updatePos(position, direction, dist);
				simLog("\t\tEncountered corner...\n");
				API_setColor(position[0], position[1], 'G');
				API_turnRight();
				direction = updateDir(direction, 1);
				distLastNode += dist + 1;
				distTotal += dist;
				API_moveForward();
				dist = 1;
			}
			else if (!API_wallLeft())
			{
				updatePos(position, direction, dist);
				simLog("\t\tEncountered corner...\n");
				API_setColor(position[0], position[1], 'G');
				API_turnLeft();
				direction = updateDir(direction, 3);
				distLastNode += dist + 1;
				distTotal += dist;
				API_moveForward();
				dist = 1;
			}
		}
		simLog("\tEncountered node:");
		updatePos(position, direction, dist);

		distLastNode += dist;
		distTotal += dist;
		int nodeID = getID(position);

		/*switch (nodeCheck())
		{
		case -1: //if deadend
		{
		simLog("\t\tNode class: Dead-end\n\t\tReturning to previous node...");
		API_setColor(position[0], position[1], 'R');

		API_turnRight();
		API_turnRight();
		direction = updateDir(direction, 2);
		break;
		}*/
		if (nodeCheck() == 1) //if maze node
		{
			simLog("\t\tNode class: Path node\n\t\tRecording node information...");
			API_setColor(position[0], position[1], 'B');

			//create node
			int paths = 0;
			int nodeCurrent[DATA]; //stores all information on current node
			nodeCurrent[0] = nodeID; //node ID
			nodeCurrent[1] = distTotal; //distance traveled
			nodeCurrent[2] = nodePrevious; //backpath
			if (!API_wallLeft())
			{
				nodeCurrent[3] = -1; //if no wall, set distance to next path on left to 0
				paths++;
			}
			else
				nodeCurrent[3] = INFINITY - 1;
			if (!API_wallFront())
			{
				nodeCurrent[4] = -1; //if no wall, set distance to next path to front to 0
				paths++;
			}
			else
				nodeCurrent[4] = INFINITY - 1;
			if (!API_wallRight())
			{
				nodeCurrent[5] = -1; //if no wall, set distance to next path on right to 0
				paths++;
			}
			else
				nodeCurrent[5] = INFINITY - 1;
			nodeCurrent[6] = paths + nodeList[stack][6];
			/*switch (direction)
			{
			case 0: //facing up
			nodeCurrent[6] = nodePrevious;
			if (API_wallFront())
			nodeCurrent[4] = 0;
			if (API_wallRight())
			nodeCurrent[5] = 0;
			if (API_wallLeft())
			nodeCurrent[7] = 0;
			break;
			case 1: //facing right
			nodeCurrent[7] = nodePrevious;
			if (API_wallFront())
			nodeCurrent[5] = 0;
			if (API_wallRight())
			nodeCurrent[6] = 0;
			if (API_wallLeft())
			nodeCurrent[4] = 0;
			break;
			case 2: //facing down
			nodeCurrent[4] = nodePrevious;
			if (API_wallFront())
			nodeCurrent[6] = 0;
			if (API_wallRight())
			nodeCurrent[7] = 0;
			if (API_wallLeft())
			nodeCurrent[5] = 0;
			break;
			case 3: //facing left
			nodeCurrent[5] = nodePrevious;
			if (API_wallFront())
			nodeCurrent[7] = 0;
			if (API_wallRight())
			nodeCurrent[4] = 0;
			if (API_wallLeft())
			nodeCurrent[6] = 0;
			break;
			}*/

			//choose path
			fprintf(stderr, "%d, %d, %d \n", nodeCurrent[3], nodeCurrent[4], nodeCurrent[5]);
			fflush(stderr);
			direction = choosePath(nodeCurrent, paths, direction, position);

			//add node to stack
			stackInsert(nodeList, nodeCurrent);

			nodePrevious = nodeID; //current node will be the next one's backpath
			API_moveForward();
			encounteredNode = true;
			//break;
		}
		//}

		//vvvv debug code vvvv
		if (position[0] < 0 || position[0] >= 16)
		{
			simLog("X position ERROR");
			break;
		}
		if (position[1] < 0 || position[1] >= 16)
		{
			simLog("Y position ERROR");
			break;
		}
	}
}