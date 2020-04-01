/*
Written by Mathazzar
Last modified: 04/1/20
Purpose: update direction the micromouse is facing in relation to its original position.
Status: UNFINISHED, PARTIALLY TESTED
*/

//#include<stdio.h>

/*int changeDirection(short int direction, short int type)
INPUTS: direction, type
	direction: current orientation of micromouse in relation to original position.
	type: change in orientation relative to previous orientation.
	Both are read as 0=UP, 1=DOWN, 2=RIGHT, 3=LEFT, and all other cases are ignored.
RETURNS: dire
	dire: a new variable for the new direction, which is returned.
NOTES: implemented to be called as:
	direction = changeDirection(direction, type);
	to set direction to new orientation.
*/
int changeDirection(short int direction, short int type) //Records changes in direction
{
	short int dire;
	switch (type)
	{
	case 0: //no change in direction
		break;
	case 1: //about-face
		switch (direction)
		{
		case 0:
			dire = 1;
			break;
		case 1:
			dire = 0;
			break;
		case 2:
			dire = 3;
			break;
		case 3:
			dire = 2;
			break;
		}
		break;
	case 2: //turned right
		switch (direction)
		{
		case 0:
			dire = 2;
			break;
		case 1:
			dire = 3;
			break;
		case 2:
			dire = 1;
			break;
		case 3:
			dire = 0;
			break;
		}
		break;
	case 3: //turned left
		switch (direction)
		{
		case 0:
			dire = 3;
			break;
		case 1:
			dire = 2;
			break;
		case 2:
			dire = 0;
			break;
		case 3:
			dire = 1;
			break;
		}
		break;
	}
	/*if (direction >= 4)
		direction -= 4;
	else if (direction <= -1)
		direction += 4;
	/*fprintf(stderr, "%d \n", direction);
	fflush(stderr); (direction);*/
	return dire;
}
