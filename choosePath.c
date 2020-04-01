/*
Written by Mathazzar
Last modified: 04/1/20
Purpose: choose what direction to go after placing a node.
Status: FINISHED?, NOT TESTED
*/

#include <stdbool.h>	
#include <stdio.h>
//#include "API.h" //only needed for simulator use

int changeDirection(short int direction, short int type);

void choosePath(short int direction, short int x, short int y) //Check possible directions, then choose most likely to advance towards goal
{
	short int position[2] = {x, y};
	

	switch (direction)
	{
	case 0: //up from original orientation
	{
		if ((position[0] >= position[1]) && position[0] <= 9) //x coord is more traveled and before center
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
		else if (position[0] >= position[1]) //x coord is more traveled and after center
		{
			if (!API_wallLeft())
			{
				fprintf(stderr, "0/2: left \n");
				fflush(stderr);
				API_turnLeft();
				direction = changeDirection(direction, 3);
			}
			else if (!API_wallFront())
			{
				fprintf(stderr, "0/2: straight \n");
				fflush(stderr);
				break;
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
		else if ((position[0] <= position[1]) && position[1] <= 9) //y coord is more traveled and before center
		{
			if (!API_wallFront())
			{
				fprintf(stderr, "0/3: straight \n");
				fflush(stderr);
				break;
			}
			else if (!API_wallRight())
			{
				fprintf(stderr, "0/3: right \n");
				fflush(stderr);
				API_turnRight();
				direction = changeDirection(direction, 2);
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
		else if (position[0] <= position[1]) //y coord is more traveled and after center
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
		if ((position[0] >= position[1]) && position[0] <= 9) //x coord is more traveled and before center
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
		else if (position[0] >= position[1]) //x coord is more traveled and after center
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
		else if ((position[0] <= position[1]) && position[1] <= 9) //y coord is more traveled and before center
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
		else if (position[0] <= position[1]) //y coord is more traveled and after center
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
		if ((position[0] >= position[1]) && position[0] <= 9) //x coord is more traveled and before center
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
				fprintf(stderr, "2/1: right, direction: %d \n", direction);
				fflush(stderr);
				API_turnRight();
				direction = changeDirection(direction, 2);
			}
			break;
		}
		else if (position[0] >= position[1]) //x coord is more traveled and after center
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
		else if ((position[0] <= position[1]) && position[1] <= 9) //y coord is more traveled and before center
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
		else if (position[0] <= position[1]) //y coord is more traveled and after center
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
		if ((position[0] >= position[1]) && position[0] <= 9) //x coord is more traveled and before center
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
		else if (position[0] >= position[1]) //x coord is more traveled and after center
		{
			if (!API_wallRight())
			{
				fprintf(stderr, "3/2: straight \n");
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
		else if ((position[0] <= position[1]) && position[1] <= 9) //y coord is more traveled and before center
		{
			if (!API_wallRight())
			{
				API_turnRight();
				direction = changeDirection(direction, 2);
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
		else if (position[0] <= position[1]) //y coord is more traveled and after center
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
