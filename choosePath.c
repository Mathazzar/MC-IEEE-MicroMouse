#include "API.h"
#include <stdio.h>
#include <stdbool.h>

#define INFINITY 1024
#define DATA 7

int backpath_classful(int position[2], short int direction);
int nodeCheck();
short int updateDir(short int direction, short int relativeChange);
void simLog(char* text); //modified from main.c in mms example (https://github.com/mackorone/mms-c)
void updatePos(int position[2], short int direction, short int dist);

int checkPath(int position[2], short int dire, int paths);

short int choosePath(int nodeCurrent[DATA], int paths, short int direction, int position[2])
{
	//Initialize variables for internal use
	short int dire = direction;
	bool deadend = false;

	//Check each path
	if (nodeCurrent[3] == -1)
		{
			simLog("Checking left path...");
			API_turnLeft();
			dire = updateDir(dire, 3);

			int distLastNode = checkPath(position, dire, paths);
			
			if (nodeCheck() == 1)
				nodeCurrent[3] = distLastNode;
			else if (nodeCheck() == -1)
			{
				nodeCurrent[3] = INFINITY - 1;
				nodeCurrent[6]--;
			}
			//same for each check
			paths--;
			fprintf(stderr, "distance: %d, paths left: %d\n", distLastNode, paths);
			fflush(stderr);

			//reset
			if (paths > 0)
			{
				dire = backpath_classful(position, dire);
				API_turnLeft();
				dire = updateDir(dire, 3);
			}
			else
				return dire;
		}
	if (nodeCurrent[4] == -1)
	{
		simLog("Checking front path...");

		int distLastNode = checkPath(position, dire, paths);

		if (nodeCheck() == 1)
			nodeCurrent[4] = distLastNode;
		else if (nodeCheck() == -1)
		{
			nodeCurrent[4] = INFINITY - 1;
			nodeCurrent[6]--;
		}
		//same for each check
		paths--;
		fprintf(stderr, "distance: %d, paths left: %d\n", distLastNode, paths);
		fflush(stderr);

		//reset
		if (paths > 0)
		{
			dire = backpath_classful(position, dire);
			API_turnRight();
			API_turnRight();
			dire = updateDir(dire, 2);
		}
		else
		{
			if (nodeCurrent[3] < nodeCurrent[4])
			{
				API_turnLeft();
				dire = updateDir(dire, 3);
				return dire;
			}
			else
			{
				dire = backpath_classful(position, dire);
				API_turnRight();
				API_turnRight();
				dire = updateDir(dire, 2);
				return dire;
			}
		}
	}
	if (nodeCurrent[5] == -1)
	{
		simLog("Checking right path...");
		API_turnRight();
		dire = updateDir(dire, 1);

		int distLastNode = checkPath(position, dire, paths);

		if (nodeCheck() == 1)
			nodeCurrent[5] = distLastNode;
		else if (nodeCheck() == -1)
		{
			nodeCurrent[5] = INFINITY - 1;
			nodeCurrent[6]--;
		}
		//same for each check
		paths--;
		fprintf(stderr, "distance: %d, paths left: %d\n", distLastNode, paths);
		fflush(stderr);

		/*if (paths > 0)
		{
			dire = backpath_classful(position, dire);
			API_turnRight();
			dire = updateDir(dire, 1);
		}
		else
		{
			
		}*/
	}

	//Choose path
	if (nodeCurrent[3] < nodeCurrent[4])
	{
		dire = backpath_classful(position, dire);
		API_turnRight();
		dire = updateDir(dire, 1);

		API_turnLeft();
		dire = updateDir(dire, 3);
		return dire;
	}
	else if (nodeCurrent[4] <= nodeCurrent[5])
	{
		dire = backpath_classful(position, dire);
		API_turnRight();
		dire = updateDir(dire, 1);

		dire = updateDir(dire, 0);
		return dire;
	}
	else
	{
		/*API_turnRight();
		dire = updateDir(dire, 1);*/
		return dire;
	}

	/*if (nodeCurrent[3] < nodeCurrent[4])
	{
		API_turnLeft();
		dire = updateDir(dire, 3);
		return dire;
	}
	else if (nodeCurrent[4] <= nodeCurrent[5])
	{
		dire = updateDir(dire, 0);
		return dire;
	}
	else
	{
		API_turnRight();
		dire = updateDir(dire, 1);
		return dire;
	}*/
}

//Same for each check
int checkPath(int position[2], short int dire, int paths)
{
	API_moveForward();
	int dist = 1;
	int distLastNode = 1;
	while (nodeCheck() == 0)
	{
		if (!API_wallFront())
		{
			
		}
		else if (!API_wallRight())
		{
			updatePos(position, dire, distLastNode);
			API_turnRight();
			distLastNode += dist + 1;
			dire = updateDir(dire, 1);
			dist = 0;
		}
		else if (!API_wallLeft())
		{
			updatePos(position, dire, distLastNode);
			API_turnLeft();
			distLastNode += dist + 1;
			dire = updateDir(dire, 3);
			dist = 0;
		}
		API_moveForward();
		dist++;
	}
	updatePos(position, dire, dist);
	return distLastNode;
}
