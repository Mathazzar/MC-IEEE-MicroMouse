#include <stdio.h>

void simLog(char* text); //modified from main.c in mms example (https://github.com/mackorone/mms-c)

void updatePos(int position[2], short int direction, short int dist)
{
	fprintf(stderr, "moving from (%d, %d, %d) %d units to ", position[0], position[1], direction, dist);
	fflush(stderr);
	switch (direction)
	{
	case 0: //if facing up
		position[1] += dist;
		break;
	case 1: //if facing right
		position[0] += dist;
		break;
	case 2: //if facing down
		position[1] -= dist;
		break;
	case 3: //if facing left
		position[0] -= dist;
		break;
	default:
		break;
	}
	fprintf(stderr, "(%d, %d, %d) \n", position[0], position[1], direction);
	fflush(stderr);
	if (position[0] < 0 || position[0] >= 16)
	{
		simLog("X position ERROR");
	}
	if (position[1] < 0 || position[1] >= 16)
	{
		simLog("Y position ERROR");
	}
}
