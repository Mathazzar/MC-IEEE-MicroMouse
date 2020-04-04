#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1024
#define NOPATHS 255
#define WALL 9
#define MAXDIST 14

int nodeClassification(int NIN, int PathList[/*NIN*/256][3], int orientation);
void choseForward(int orientation, int NINoid);
void choseRight(int orientation, int NIN);
void choseLeft(int orientation, int NIN);
int choice(int NIN, int PathList[256][3], int orientation);
void returnToNode(int nodeClass, int NIN, int PathList[256][3], int orientation);
void simLog(char* text);

//Initializes node list
void scan(int PathList[256][3], int NIN, int nodeClass, int orientation)
{
	/*S*/
	nodeClass = nodeClassification(1, PathList/*[1]*/, orientation);

	//while (NIN != 120 && NIN != 121 && NIN != 136 && NIN != 137)
	int i = 0;
	//for (int i = 0; i < 4, i++;)
	while (i < 4)
	{
		switch (nodeClass)
		{
		case 0:
		{
			choseForward(orientation, NIN);
			nodeClass = nodeClassification(NIN, PathList/*[NIN]*/, orientation);
		}
		case 2:
		{
			if (PathList[NIN][3] != 0)
			{
				choseRight(orientation, NIN);
				nodeClass = nodeClassification(NIN, PathList/*[NIN]*/, orientation);
			}
			else if (PathList[NIN][2] != 0)
			{
				choseLeft(orientation, NIN);
				nodeClass = nodeClassification(NIN, PathList/*[NIN]*/, orientation);
			}
		}
			
		case 1:
		{
			simLog("This is a node.\n");
			choice(NIN, PathList/*[256][3]*/, orientation);
		}
			
		case -1:
		{
			//what about /*explore all options
			returnToNode(nodeClass, NIN, PathList, orientation);
		}
		}
		i++;
	}
}//end scan