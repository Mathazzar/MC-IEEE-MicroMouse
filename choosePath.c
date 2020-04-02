/*
Written by Mathazzar
Last modified: 04/2/20
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
	x: current x coordinate of micromouse on a 16x16 grid where the start is at x=0.
	y: current y coordinate of micromouse on a 16x16 grid where the start is at y=0.
	Direction is read as 0=UP, 1=DOWN, 2=RIGHT, 3=LEFT, and all other cases are ignored.
RETURNS: NONE
NOTES:
	Selects what order to check for walls among 16 cases, 1 for each possible orientation and "quadrant" in the grid in relation to the center.
	Modifies direction internally, so no aditional functions need to be called before or after this algorithm runs to update the micromouse's orientation.
*/
void choosePath(short int direction, short int x, short int y) //Check possible directions, then choose most likely to advance towards goal
{
	short int position[2] = {x, y};
	

	switch (direction)
	{
	case 0: //up from original orientation
	{
		if ((position[0] >= position[1]) && position[0] <= 8) //x coord is more traveled and before center: try straight, right, then left
		{
			if (!API_wallFront())
			{
				fprintf(stderr, "0/1: straight \n");
				fflush(stderr);
				break;
			}
			else if (!API_wallRight())
			{
				fprintf(stderr, "0/1: right \n");
				fflush(stderr);
				API_turnRight();
				direction = changeDirection(direction, 2);
			}
			else if (!API_wallLeft())
			{
				fprintf(stderr, "0/1: left \n");
				fflush(stderr);
				API_turnLeft();
				direction = changeDirection(direction, 3);
			}
			break;
		}
		else if (position[0] >= position[1]) //x coord is more traveled and after center: try sraight, left, then right
		{
			if (!API_wallFront())
			{
				fprintf(stderr, "0/2: straight \n");
				fflush(stderr);
				break;
			}
			else if (!API_wallLeft())
			{
				fprintf(stderr, "0/2: left \n");
				fflush(stderr);
				API_turnLeft();
				direction = changeDirection(direction, 3);
			}
			else if (!API_wallRight())
			{
				fprintf(stderr, "0/2: right \n");
				fflush(stderr);
				API_turnRight();
				direction = changeDirection(direction, 2);
			}
			break;
		}
		else if ((position[0] <= position[1]) && position[1] <= 8) //y coord is more traveled and before center: try right, straight, then left
		{
			if (!API_wallRight())
			{
				fprintf(stderr, "0/3: right \n");
				fflush(stderr);
				API_turnRight();
				direction = changeDirection(direction, 2);
			}
			else if (!API_wallFront())
			{
				fprintf(stderr, "0/3: straight \n");
				fflush(stderr);
				break;
			}
			else if (!API_wallLeft())
			{
				fprintf(stderr, "0/3: left \n");
				fflush(stderr);
				API_turnLeft();
				direction = changeDirection(direction, 3);
			}
			break;
		}
		else if (position[0] <= position[1]) //y coord is more traveled and after center: try right, straight, then left
		{
			if (!API_wallRight())
			{
				fprintf(stderr, "0/4: right \n");
				fflush(stderr);
				API_turnRight();
				direction = changeDirection(direction, 2);
			}
			else if (!API_wallFront())
			{
				fprintf(stderr, "0/4: straight \n");
				fflush(stderr);
				break;
			}
			else if (!API_wallLeft())
			{
				fprintf(stderr, "0/4: left \n");
				fflush(stderr);
				API_turnLeft();
				direction = changeDirection(direction, 3);
			}
			break;
		}
	}
	case 1: //down from original position
	{
		if ((position[0] >= position[1]) && position[0] <= 8) //x coord is more traveled and before center: try left, right, then down
		{
			
			if (!API_wallLeft())
			{
				fprintf(stderr, "1/1: left \n");
				fflush(stderr);
				API_turnLeft();
				direction = changeDirection(direction, 3);
			}
			else if (!API_wallRight())
			{
				fprintf(stderr, "1/1: right \n");
				fflush(stderr);
				API_turnRight();
				direction = changeDirection(direction, 2);
			}
			else if (!API_wallFront())
			{
				fprintf(stderr, "1/1: straight \n");
				fflush(stderr);
				break;
			}
			break;
		}
		else if (position[0] >= position[1]) //x coord is more traveled and after center: try right, left, then straight
		{
			if (!API_wallRight())
			{
				fprintf(stderr, "1/2: right \n");
				fflush(stderr);
				API_turnRight();
				direction = changeDirection(direction, 2);
			}
			else if (!API_wallLeft())
			{
				fprintf(stderr, "1/2: left \n");
				fflush(stderr);
				API_turnLeft();
				direction = changeDirection(direction, 3);
			}
			else if (!API_wallFront())
			{
				fprintf(stderr, "1/2: straight \n");
				fflush(stderr);
				break;
			}
			break;
		}
		else if ((position[0] <= position[1]) && position[1] <= 8) //y coord is more traveled and before center: try left, right, then straight
		{
			if (!API_wallLeft())
			{
				fprintf(stderr, "1/3: left \n");
				fflush(stderr);
				API_turnLeft();
				direction = changeDirection(direction, 3);
			}
			else if (!API_wallRight())
			{
				fprintf(stderr, "1/3: right \n");
				fflush(stderr);
				API_turnRight();
				direction = changeDirection(direction, 2);
			}
			else if (!API_wallFront())
			{
				fprintf(stderr, "1/3: straight \n");
				fflush(stderr);
				break;
			}
			break;
		}
		else if (position[0] <= position[1]) //y coord is more traveled and after center: try left, straight, then right
		{
			if (!API_wallLeft())
			{
				fprintf(stderr, "1/4: left \n");
				fflush(stderr);
				API_turnLeft();
				direction = changeDirection(direction, 3);
			}
			else if (!API_wallFront())
			{
				fprintf(stderr, "1/4: straight \n");
				fflush(stderr);
				break;
			}
			else if (!API_wallRight())
			{
				fprintf(stderr, "1/4: right \n");
				fflush(stderr);
				API_turnRight();
				direction = changeDirection(direction, 2);
			}
			break;
		}
	}
	case 2: //right from original position
	{
		if ((position[0] >= position[1]) && position[0] <= 8) //x coord is more traveled and before center: try straight, left, then right
		{

			if (!API_wallFront())
			{
				fprintf(stderr, "2/1: straight, direction: %d \n", direction);
				fflush(stderr);
				break;
			}
			else if (!API_wallLeft())
			{
				API_turnLeft();
				direction = changeDirection(direction, 3);
				fprintf(stderr, "2/1: left, direction: %d \n", direction);
				fflush(stderr);
			}
			else if (!API_wallRight())
			{
				API_turnRight();
				direction = changeDirection(direction, 2);
				fprintf(stderr, "2/1: right, direction: %d \n", direction);
				fflush(stderr);
			}
			break;
		}
		else if (position[0] >= position[1]) //x coord is more traveled and after center: try left, straight, then right
		{
			if (!API_wallLeft())
			{
				fprintf(stderr, "2/2: left \n");
				fflush(stderr);
				API_turnLeft();
				direction = changeDirection(direction, 3);
			}
			else if (!API_wallFront())
			{
				fprintf(stderr, "2/2: straight \n");
				fflush(stderr);
				break;
			}
			else if (!API_wallRight())
			{
				fprintf(stderr, "2/2: right \n");
				fflush(stderr);
				API_turnRight();
				direction = changeDirection(direction, 2);
			}
			break;
		}
		else if ((position[0] <= position[1]) && position[1] <= 8) //y coord is more traveled and before center: try straight, left, then right
		{
			if (!API_wallFront())
			{
				break;
				fprintf(stderr, "2/3: straight, direction: %d \n", direction);
				fflush(stderr);
			}
			else if (!API_wallLeft())
			{
				fprintf(stderr, "2/3: left \n");
				fflush(stderr);
				API_turnLeft();
				direction = changeDirection(direction, 3);
			}
			else if (!API_wallRight())
			{
				fprintf(stderr, "2/3: right \n");
				fflush(stderr);
				API_turnRight();
				direction = changeDirection(direction, 2);
			}
			break;
		}
		else if (position[0] <= position[1]) //y coord is more traveled and after center: try straight, right, then left
		{
			if (!API_wallFront())
			{
				fprintf(stderr, "2/4: straight \n");
				fflush(stderr);
				break;
			}
			else if (!API_wallRight())
			{
				fprintf(stderr, "2/4: right \n");
				fflush(stderr);
				API_turnRight();
				direction = changeDirection(direction, 2);
			}
			else if (!API_wallLeft())
			{
				fprintf(stderr, "2/4: left \n");
				fflush(stderr);
				API_turnLeft();
				direction = changeDirection(direction, 3);
			}
			break;
		}
	}
	case 3: //left from original position
	{
		if ((position[0] >= position[1]) && position[0] <= 8) //x coord is more traveled and before center: try right, left, then straight
		{

			if (!API_wallRight())
			{
				fprintf(stderr, "3/1: right \n");
				fflush(stderr);
				API_turnRight();
				direction = changeDirection(direction, 2);
			}
			else if (!API_wallLeft())
			{
				fprintf(stderr, "3/1: left \n");
				fflush(stderr);
				API_turnLeft();
				direction = changeDirection(direction, 3);
			}
			else if (!API_wallFront())
			{
				fprintf(stderr, "3/1: straight \n");
				fflush(stderr);
				break;
			}
			break;
		}
		else if (position[0] >= position[1]) //x coord is more traveled and after center: try right, straight, then left
		{
			if (!API_wallRight())
			{
				fprintf(stderr, "3/2: right \n");
				fflush(stderr);
				API_turnRight();
				direction = changeDirection(direction, 2);
			}
			else if (!API_wallFront())
			{
				fprintf(stderr, "3/2: straight \n");
				fflush(stderr);
				break;
			}
			else if (!API_wallLeft())
			{
				fprintf(stderr, "3/2: left \n");
				fflush(stderr);
				API_turnLeft();
				direction = changeDirection(direction, 3);
			}
			break;
		}
		else if ((position[0] <= position[1]) && position[1] <= 8) //y coord is more traveled and before center: try right, straight, then left
		{
			if (!API_wallRight())
			{
				API_turnRight();
				direction = changeDirection(direction, 2);
				fprintf(stderr, "3/3: right \n");
				fflush(stderr);
			}
			else if (!API_wallFront())
			{
				fprintf(stderr, "3/3: straight \n");
				fflush(stderr);
				break;
			}
			else if (!API_wallLeft())
			{
				fprintf(stderr, "3/3: left \n");
				fflush(stderr);
				API_turnLeft();
				direction = changeDirection(direction, 3);
			}
			break;
		}
		else if (position[0] <= position[1]) //y coord is more traveled and after center: try left, straight, then right
		{
			if (!API_wallLeft())
			{
				fprintf(stderr, "3/4: left \n");
				fflush(stderr);
				API_turnLeft();
				direction = changeDirection(direction, 3);
			}
			else if (!API_wallFront())
			{
				fprintf(stderr, "3/4: straight \n");
				fflush(stderr);
				break;
			}
			else if (!API_wallRight())
			{
				fprintf(stderr, "3/4: right \n");
				fflush(stderr);
				API_turnRight();
				direction = changeDirection(direction, 2);
			}
			break;
		}
	}
	}
	//return direction;
}
