/*
Written by Mathazzar
Last modified: 04/3/20
Purpose: choose what direction to go after placing a node.
Status: FINISHED?, PARTIALLY TESTED
*/

#include <stdbool.h>	
#include <stdio.h>
//#include "API.h" //only needed for simulator use

int changeDirection(short int direction, short int type);

/*void choosePath(short int direction, short int x, short int y)
INPUTS: direction, x, y
	direction: current orientation of micromouse in relation to original position.
	x: current x coordinate of micromouse on a 16x16 grid where the start is at x = 0. Intended for use with position[0] in algo.c
	y: current y coordinate of micromouse on a 16x16 grid where the start is at y = 0. Intended for use with position[1] in algo.c
	Direction is read as 0=UP, 1=DOWN, 2=RIGHT, 3=LEFT, and all other cases are ignored.
RETURNS: dire
	dire: a new variable for the new direction, which is returned.
NOTES:
	Selects what order to check for walls among 20 cases, 1 for each possible orientation and "quadrant" in the grid in relation to the center.
	implemented to be called as:
		direction = choosePath(short int direction, short int x, short int y);
		to set direction to new orientation once it chooses its path.
*/
int choosePath(short int direction, short int x, short int y) //Check possible directions, then choose most likely to advance towards goal
{
	short int position[2] = {x, y};
	short int dire;
	

	switch (direction)
	{
	case 0: //up from original orientation
	{
		if ((position[0] >= 7) && (position[1] >= 7))// x and y coords are both after center: try left, right, then straight
		{
			
			if (!API_wallLeft())
			{
				API_turnLeft();
				dire = changeDirection(direction, 3);
				fprintf(stderr, "0/0: left (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallRight())
			{
				API_turnRight();
				dire = changeDirection(direction, 2);
				fprintf(stderr, "0/0: right (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallFront())
			{
				dire = changeDirection(direction, 0);
				fprintf(stderr, "0/0: straight (%d) \n", dire);
				fflush(stderr);
				break;
			}
			fprintf(stderr, "DIRECTION ERROR: 0/0 \n");
			fflush(stderr);
			break;
		}
		else if ((position[0] >= position[1]) && position[0] <= 7) //x coord is more traveled and before center: try straight, right, then left
		{
			if (!API_wallFront())
			{
				dire = changeDirection(direction, 0);
				fprintf(stderr, "0/1: straight (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallRight())
			{	
				API_turnRight();
				dire = changeDirection(direction, 2);
				fprintf(stderr, "0/1: right (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallLeft())
			{
				API_turnLeft();
				dire = changeDirection(direction, 3);
				fprintf(stderr, "0/1: left (%d) \n", dire);
				fflush(stderr);
				break;
			}
			fprintf(stderr, "DIRECTION ERROR: 0/1 \n");
			fflush(stderr);
			break;
		}
		else if (position[0] >= position[1]) //x coord is more traveled and after center: try sraight, left, then right
		{
			if (!API_wallFront())
			{
				dire = changeDirection(direction, 0);
				fprintf(stderr, "0/2: straight (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallLeft())
			{
				API_turnLeft();
				dire = changeDirection(direction, 3);
				fprintf(stderr, "0/2: left (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallRight())
			{
				API_turnRight();
				dire = changeDirection(direction, 2);
				fprintf(stderr, "0/2: right (%d) \n", dire);
				fflush(stderr);
				break;
			}
			fprintf(stderr, "DIRECTION ERROR: 0/2 \n");
			fflush(stderr);
			break;
		}
		else if ((position[0] <= position[1]) && position[1] <= 7) //y coord is more traveled and before center: try straight, right, then left
		{
			if (!API_wallFront())
			{
				dire = changeDirection(direction, 0);
				fprintf(stderr, "0/3: straight (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallRight())
			{
				API_turnRight();
				dire = changeDirection(direction, 2);
				fprintf(stderr, "0/3: right (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallLeft())
			{
				API_turnLeft();
				dire = changeDirection(direction, 3);
				fprintf(stderr, "0/3: left (%d) \n", dire);
				fflush(stderr);
				break;
			}
			fprintf(stderr, "DIRECTION ERROR: 0/3 \n");
			fflush(stderr);
			break;
		}
		else if (position[0] <= position[1]) //y coord is more traveled and after center: try right, straight, then left
		{
			if (!API_wallRight())
			{
				API_turnRight();
				dire = changeDirection(direction, 2);
				fprintf(stderr, "0/4: right (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallFront())
			{
				dire = changeDirection(direction, 0);
				fprintf(stderr, "0/4: straight (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallLeft())
			{
				API_turnLeft();
				dire = changeDirection(direction, 3);
				fprintf(stderr, "0/4: left (%d) \n", dire);
				fflush(stderr);
				break;
			}
			fprintf(stderr, "DIRECTION ERROR: 0/4 \n");
			fflush(stderr);
			break;
		}
		fprintf(stderr, "DIRECTION ERROR: 0 \n");
		fflush(stderr);
	}
	case 1: //down from original position
	{
		if ((position[0] >= 7) && (position[1] >= 7))// x and y coords are both after center: try straight, left, then right
		{

			if (!API_wallFront())
			{
				dire = changeDirection(direction, 0);
				fprintf(stderr, "1/0: straight (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallLeft())
			{
				API_turnLeft();
				dire = changeDirection(direction, 3);
				fprintf(stderr, "1/0: left (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallRight())
			{
				API_turnRight();
				dire = changeDirection(direction, 2);
				fprintf(stderr, "1/0: right (%d) \n", dire);
				fflush(stderr);
				break;
			} 
			fprintf(stderr, "DIRECTION ERROR: 1/0 \n");
			fflush(stderr);
			break;
		}
		else if ((position[0] >= position[1]) && position[0] <= 7) //x coord is more traveled and before center: try left, right, then down
		{
			
			if (!API_wallLeft())
			{
				API_turnLeft();
				dire = changeDirection(direction, 3);
				fprintf(stderr, "1/1: left (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallRight())
			{
				API_turnRight();
				dire = changeDirection(direction, 2);
				fprintf(stderr, "1/1: right (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallFront())
			{
				dire = changeDirection(direction, 0);
				fprintf(stderr, "1/1: straight (%d) \n", dire);
				fflush(stderr);
				break;
			}
			fprintf(stderr, "DIRECTION ERROR: 1/1 \n");
			fflush(stderr);
			break;
		}
		else if (position[0] >= position[1]) //x coord is more traveled and after center: try right, left, then straight
		{
			if (!API_wallRight())
			{
				API_turnRight();
				dire = changeDirection(direction, 2);
				fprintf(stderr, "1/2: right (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallLeft())
			{
				API_turnLeft();
				dire = changeDirection(direction, 3);
				fprintf(stderr, "1/2: left (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallFront())
			{
				dire = changeDirection(direction, 0);
				fprintf(stderr, "1/2: straight (%d) \n", dire);
				fflush(stderr);
				break;
			}
			fprintf(stderr, "DIRECTION ERROR: 1/2 \n");
			fflush(stderr);
			break;
		}
		else if ((position[0] <= position[1]) && position[1] <= 7) //y coord is more traveled and before center: try left, right, then straight
		{
			if (!API_wallLeft())
			{
				API_turnLeft();
				dire = changeDirection(direction, 3);
				fprintf(stderr, "1/3: left (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallRight())
			{
				API_turnRight();
				dire = changeDirection(direction, 2);
				fprintf(stderr, "1/3: right (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallFront())
			{
				dire = changeDirection(direction, 0);
				fprintf(stderr, "1/3: straight (%d) \n", dire);
				fflush(stderr);
				break;
			}
			fprintf(stderr, "DIRECTION ERROR: 1/3 \n");
			fflush(stderr);
			break;
		}
		else if (position[0] <= position[1]) //y coord is more traveled and after center: try left, straight, then right
		{
			if (!API_wallLeft())
			{

				API_turnLeft();
				dire = changeDirection(direction, 3);
				fprintf(stderr, "1/4: left (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallFront())
			{
				dire = changeDirection(direction, 0);
				fprintf(stderr, "1/4: straight (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallRight())
			{
				dire = changeDirection(direction, 2);
				fprintf(stderr, "1/4: right (%d) \n", dire);
				fflush(stderr);
				API_turnRight();
				break;
			}
			fprintf(stderr, "DIRECTION ERROR: 1/4 \n");
			fflush(stderr);
			break;
		}
		fprintf(stderr, "DIRECTION ERROR: 1 \n");
		fflush(stderr);
	}
	case 2: //right from original position
	{
		if ((position[0] >= 7) && (position[1] >= 7))// x and y coords are both after center: try right, left, then straight
		{

			if (!API_wallRight())
			{
				API_turnRight();
				dire = changeDirection(direction, 2);
				fprintf(stderr, "2/0: right (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallLeft())
			{
				API_turnLeft();
				dire = changeDirection(direction, 3);
				fprintf(stderr, "2/0: left (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallFront())
			{
				dire = changeDirection(direction, 0);
				fprintf(stderr, "2/0: straight (%d) \n", dire);
				fflush(stderr);
				break;
			}
			fprintf(stderr, "DIRECTION ERROR: 2/0 \n");
			fflush(stderr);
			break;
		}
		else if ((position[0] >= position[1]) && position[0] <= 7) //x coord is more traveled and before center: try straight, left, then right
		{

			if (!API_wallFront())
			{
				dire = changeDirection(direction, 0);
				fprintf(stderr, "2/1: straight (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallLeft())
			{
				API_turnLeft();
				dire = changeDirection(direction, 3);
				fprintf(stderr, "2/1: left (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallRight())
			{
				API_turnRight();
				dire = changeDirection(direction, 2);
				fprintf(stderr, "2/1: right (%d) \n", dire);
				fflush(stderr);
				break;
			}
			fprintf(stderr, "DIRECTION ERROR: 2/1 \n");
			fflush(stderr);
			break;
		}
		else if (position[0] >= position[1]) //x coord is more traveled and after center: try left, straight, then right
		{
			if (!API_wallLeft())
			{
				API_turnLeft();
				dire = changeDirection(direction, 3);
				fprintf(stderr, "2/2: left (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallFront())
			{
				dire = changeDirection(direction, 0);
				fprintf(stderr, "2/2: straight (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallRight())
			{
				API_turnRight();
				dire = changeDirection(direction, 2);
				fprintf(stderr, "2/2: right (%d) \n", dire);
				fflush(stderr);
				break;
			}
			fprintf(stderr, "DIRECTION ERROR: 2/2 \n");
			fflush(stderr);
			break;
		}
		else if ((position[0] <= position[1]) && position[1] <= 7) //y coord is more traveled and before center: try straight, left, then right
		{
			if (!API_wallFront())
			{
				dire = changeDirection(direction, 0);
				fprintf(stderr, "2/3: straight, direction: %d \n", direction);
				fflush(stderr);
				break;
			}
			else if (!API_wallLeft())
			{
				API_turnLeft();
				dire = changeDirection(direction, 3);
				fprintf(stderr, "2/3: left (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallRight())
			{
				API_turnRight();
				dire = changeDirection(direction, 2);
				fprintf(stderr, "2/3: right (%d) \n", dire);
				fflush(stderr);
				break;
			}
			fprintf(stderr, "DIRECTION ERROR: 2/3 \n");
			fflush(stderr);
			break;
		}
		else if (position[0] <= position[1]) //y coord is more traveled and after center: try straight, right, then left
		{
			if (!API_wallFront())
			{
				dire = changeDirection(direction, 0);
				fprintf(stderr, "2/4: straight (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallRight())
			{
				API_turnRight();
				dire = changeDirection(direction, 2);
				fprintf(stderr, "2/4: right (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallLeft())
			{
				API_turnLeft();
				dire = changeDirection(direction, 3);
				fprintf(stderr, "2/4: left (%d) \n", dire);
				fflush(stderr);
				break;
			}
			fprintf(stderr, "DIRECTION ERROR: 2/4 \n");
			fflush(stderr);
			break;
		}
		fprintf(stderr, "DIRECTION ERROR: 2 \n");
		fflush(stderr);
	}
	case 3: //left from original position
	{
		if ((position[0] >= 7) && (position[1] >= 7))// x and y coords are both after center: try left, straight, then right
		{

			if (!API_wallLeft())
			{
				API_turnLeft();
				dire = changeDirection(direction, 3);
				fprintf(stderr, "3/0: left (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallFront())
			{
				dire = changeDirection(direction, 0);
				fprintf(stderr, "3/0: straight (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallRight())
			{
				API_turnRight();
				dire = changeDirection(direction, 2);
				fprintf(stderr, "3/0: right (%d) \n", dire);
				fflush(stderr);
				break;
			}
			fprintf(stderr, "DIRECTION ERROR: 3/0 \n");
			fflush(stderr);
			break;
		}
		else if ((position[0] >= position[1]) && position[0] <= 7) //x coord is more traveled and before center: try right, left, then straight
		{

			if (!API_wallRight())
			{
				API_turnRight();
				dire = changeDirection(direction, 2);
				fprintf(stderr, "3/1: right (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallLeft())
			{
				API_turnLeft();
				dire = changeDirection(direction, 3);
				fprintf(stderr, "3/1: left (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallFront())
			{
				dire = changeDirection(direction, 0);
				fprintf(stderr, "3/1: straight (%d) \n", dire);
				fflush(stderr);
				break;
			}
			fprintf(stderr, "DIRECTION ERROR: 3/1 \n");
			fflush(stderr);
			break;
		}
		else if (position[0] >= position[1]) //x coord is more traveled and after center: try right, straight, then left
		{
			if (!API_wallRight())
			{
				API_turnRight();
				dire = changeDirection(direction, 2);
				fprintf(stderr, "3/2: right (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallFront())
			{
				dire = changeDirection(direction, 0);
				fprintf(stderr, "3/2: straight (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallLeft())
			{
				API_turnLeft();
				dire = changeDirection(direction, 3);
				fprintf(stderr, "3/2: left (%d) \n", dire);
				fflush(stderr);
				break;
			}
			fprintf(stderr, "DIRECTION ERROR: 3/2 \n");
			fflush(stderr);
			break;
		}
		else if ((position[0] <= position[1]) && position[1] <= 7) //y coord is more traveled and before center: try right, straight, then left
		{
			if (!API_wallRight())
			{
				API_turnRight();
				dire = changeDirection(direction, 2);
				fprintf(stderr, "3/3: right (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallFront())
			{
				dire = changeDirection(direction, 0);
				fprintf(stderr, "3/3: straight (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallLeft())
			{
				API_turnLeft();
				dire = changeDirection(direction, 3);
				fprintf(stderr, "3/3: left (%d) \n", dire);
				fflush(stderr);
				break;
			}
			fprintf(stderr, "DIRECTION ERROR: 3/3 \n");
			fflush(stderr);
			break;
		}
		else if (position[0] <= position[1]) //y coord is more traveled and after center: try left, straight, then right
		{
			if (!API_wallLeft())
			{
				API_turnLeft();
				dire = changeDirection(direction, 3);
				fprintf(stderr, "3/4: left (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallFront())
			{
				dire = changeDirection(direction, 0);
				fprintf(stderr, "3/4: straight (%d) \n", dire);
				fflush(stderr);
				break;
			}
			else if (!API_wallRight())
			{
				API_turnRight();
				dire = changeDirection(direction, 2);
				fprintf(stderr, "3/4: right (%d) \n", dire);
				fflush(stderr);
				break;
			}
			fprintf(stderr, "DIRECTION ERROR: 3/4 \n");
			fflush(stderr);
			break;
		}
		fprintf(stderr, "DIRECTION ERROR: 3 \n");
		fflush(stderr);
	}
	default: //invalid direction entered
		fprintf(stderr, "INVALID DIRECTION \n");
		fflush(stderr);
		break;
	}
	return dire;
}
