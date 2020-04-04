#include "API.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nodeClassification(int NIN, int PathList[/*NIN*/256][3], int orientation);
void turnRight();
void turnLeft();
void simLog(char* text);

//Movement

void choseForward(int orientation, int NIN);

void returnToNode(int nodeClass, int NIN, int PathList/*[]*/[256][3], int orientation)
{
	API_turnRight();
	API_turnRight();

	while (nodeClass != 1)
	{
		choseForward(orientation, NIN);
		nodeClass = nodeClassification(NIN, PathList/*[NIN]*/, orientation);
	}
}

void choseForward(int orientation, int NIN)
{
	simLog("Moving forward\n");
	if (orientation == 0)
	{
		NIN += 16;
	}
	else if (orientation == 1)
	{
		NIN -= 16;
	}
	else if (orientation == 2)
	{
		NIN += 1;
	}
	else if (orientation == 3)
	{
		NIN -= 1;
	}
	API_moveForward();

	//while node
	//motorR(1), motorL(1);
	//turnleft
	//turnright
	//distancefromS++;

}//end forward movement

void choseRight(int orientation, int NIN)
{
	simLog("Turning right\n");
	turnRight(); //add a weight to dist
	if (orientation == 0) //Maintain orientation
	{
		orientation = 2;
	}
	else if (orientation == 1)
	{
		orientation = 3;
	}
	else if (orientation == 2)
	{
		orientation = 1;
	}
	else if (orientation == 3)
	{
		orientation = 0;
	}
	choseForward(orientation, NIN);
}
void turnRight() //int deg for diagonals. void for now
{
	API_turnRight();

	//if (deg == 45)
	//motorR(-.5), motorL(.5); //#define HALF .5
	//if (deg == 90)
	//motorR(-1), motorL(1); //#define FULL 1
	//distancefromS++ sqrt2

}//end right turn

void choseLeft(int orientation, int NIN)
{
	simLog("Turning left\n");
	turnLeft();
	if (orientation == 0) //Maintain orientation
	{
		orientation = 3;
	}
	else if (orientation == 1)
	{
		orientation = 2;
	}
	else if (orientation == 2)
	{
		orientation = 0;
	}
	else if (orientation == 3)
	{
		orientation = 1;
	}
	choseForward(orientation, NIN);

}

void turnLeft() //int deg for diagonals. void for now
{
	API_turnLeft();
	//if (deg == 45)
	//motorR(.5), motorL(-.5); //#define HALF .5
	//if (deg == 90)
	//motorR(-1), motorL(1); //#define FULL 1
	//distancefromS++ sqrt2
}//end left turn