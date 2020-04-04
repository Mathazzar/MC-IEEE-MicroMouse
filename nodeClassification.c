#include <stdbool.h>
#include "API.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1024
#define NOPATHS 255
#define WALL 9
#define MAXDIST 14

bool wallFront();
bool wallRight();
bool wallLeft();
void simLog(char* text);

//-1 = Deadend || 0 = Clear Path || 1 = Explorable Node || 2 = Corner/Unexplorable Node
//Classifies every node
int nodeClassification(int NIN, int PathList/*[NIN]*/[256][3], int orientation)
{
	int pathsAvailable = 3;

	//Classify node by available paths
	if (orientation == 0)
	{
		if (wallFront()) //Front
		{
			pathsAvailable--;
		}
		else
		{
			PathList[NIN][0] = NIN + 16;
		}
		if (wallRight()) //Right
		{
			pathsAvailable--;
		}
		else
		{
			PathList[NIN][1] = NIN + 1;
		}
		if (wallLeft()) //Left
		{
			pathsAvailable--;
		}
		else
		{
			PathList[NIN][2] = NIN - 1;
		}
	}
	else if (orientation == 1)
	{
		if (wallFront()) //Front
		{
			pathsAvailable--;
		}
		else
		{
			PathList[NIN][0] = NIN - 16;
		}
		if (wallRight()) //Right
		{
			pathsAvailable--;
		}
		else
		{
			PathList[NIN][1] = NIN - 1;
		}

		if (wallLeft()) //Left
		{
			pathsAvailable--;
		}
		else
		{
			PathList[NIN][2] = NIN + 1;
		}

	}
	else if (orientation == 2)
	{
		if (wallFront()) //Front
		{
			pathsAvailable--;
		}
		else
		{
			PathList[NIN][0] = NIN + 1;
		}
		if (wallRight()) //Right
		{
			pathsAvailable--;
		}
		else
		{
			PathList[NIN][1] = NIN - 16;
		}

		if (wallLeft()) //Left
		{
			pathsAvailable--;
		}
		else
		{
			PathList[NIN][2] = NIN + 16;
		}
	}
	else if (orientation == 3)
	{
		if (wallFront()) //Front
		{
			pathsAvailable--;
		}
		else
		{
			PathList[NIN][0] = NIN - 1;
		}
		if (wallRight()) //Right
		{
			pathsAvailable--;
		}
		else
		{
			PathList[NIN][1] = NIN + 16;
		}
		if (wallLeft()) //Left
		{
			pathsAvailable--;
		}
		else
		{
			PathList[NIN][2] = NIN - 1;
		}
	}

	switch (pathsAvailable) //Return classification of node
	{
	case 0:
		simLog("Deadend\n");
		return -1; //Deadend
		break;
	case 1: //Path
		if (API_wallFront())
		{
			simLog("Corner\n");
			return 2; //Corner
		}
		else
		{
			simLog("Straight path\n");
			return 0;
		}
		break;
	case 2:
		simLog("Node\n");
		return 1; //Explorable Node
		break;
	case 3:
		simLog("Node\n");
		return 1; //Explorable Node
		break;
	default: return -2;
		break;
	}
}//end classification