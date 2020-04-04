/*
Written by Mathazzar
Last modified: 04/3/20
Purpose: return to previous non-corner node.
Status: FINISHED, TESTED
*/

#include <stdbool.h>	
#include <stdio.h>

int changeDirection(short int direction, short int type);

/*int backpath(int backpath(int startNode, int position[2], short int direction)
INPUTS: int position[2], direction
	int position[2]: the current position of the micromouse. Implemented for use with position in algo.c
	direction: the current direction of the micromouse in relation to its original orientation.
RETURNS: dire
	dire: a new variable for the new direction, which is returned.
NOTES:
	implemented to be called as:
		direction = backpath(int startNode, short int direction);
		to set direction to new orientation once it has returned.
	Assumes the micromouse is facing the opposite direction it needs to backtrace to.
CAUTION:
	Manipulates the position array passed to it directly via getID.
*/
int backpath(int position[2], short int direction)
{
	//Initialize variables for internal use
	short int dire = direction;
	int dist = 0;
	
	//about face
	API_turnRight();
	API_turnRight();
	dire = changeDirection(direction, 1);

	//backtrace to last node visited
	short int nodeClass = nodeCheck(); //temporarily stores a node's class: path node, corner, or deadend
	while (nodeClass != 1) //waits until there is a node detected
	{
		API_moveForward();
		nodeClass = nodeCheck();
		dist++;

		//Assumes straight, not corner
		if (nodeClass == 2)
		{
			fprintf(stderr, "Corner Encountered: turning \n");
			fflush(stderr);
			getID(dire, dist, position);
			dist = 0;
			if (!API_wallRight())
			{
				API_turnRight();
				dire = changeDirection(direction, 2);
			}
			else if (!API_wallLeft())
			{
				API_turnLeft();
				dire = changeDirection(direction, 3);
			}
		}
		/*else
		{
			fprintf(stderr, "%d, %d, %d, %d \n",position[0], position[1], dist, nodeClass);
			fflush(stderr);
		}*/
	}
	getID(dire, dist, position);

	return dire;
}
