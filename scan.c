/*
Written by squidKnight, Mathazzar
Last modified: 10/15/20
Purpose: scan the maze.
Status: FINISHED, NOT TESTED
*/

#include <stdbool.h>
#include <stdio.h>
#include "API.h" //only needed for simulator use
#include "mouseDefs.h"
#include "nodeDefs.h"

void simLog(char* text); //modified from main.c in mms example (https://github.com/mackorone/mms-c)
void updatePos(short int position[2], short int direction, short int dist); //updates the position of the micromouse
short int updateDir(short int direction, short int relativeChange); //updates the direction the micromouse is facing
short int getID(short int position[2]); //generates unique ID for a node based on it's x-y coords
short int pathChooseAlt(bool nodeList[NODES][DATA], short int nodeCurrent, short int direction, short int position[2]);

/*void scan(bool nodeList[NODES][DATA], short int position[2], short int direction)
INPUTS: bool nodeList[NODES][DATA], short int position[2], short int direction
	nodeList: the nodeList array.
	position: the position array.
	direction: the current orientation of the micromouse.
RETURNS: bool nodeList[NODES][DATA], short int position[2], short int direction
	nodeList: updates the nodeList array directly.
	position: updates the position array directly.
	direction: the new direction of the micromouse.
NOTES:
	implemented to be called from main.c as
		direction = scan(nodeList, position, direction);
	Designed to intentionally crash and return to a higher function when no unexplored paths exist.
	Master function for exploring the maze.
CAUTION:
	Manipulates the nodeList array directly.
	Manipulates the position array directly.
*/
short int scan(bool nodeList[NODES][DATA], short int position[2], short int direction)
{
	simLog("Begining maze scan...");
	while (1 == 1)
	{
		//record node
		short int nodeID = getID(position);

		//set directions for current orientation
		short int wf, wr, wb, wl, ef, er, eb, el;
		switch (direction)
		{
		case 0:
			wf = WAL_T;
			wr = WAL_R;
			wb = WAL_B;
			wl = WAL_L;
			ef = EXP_T;
			er = EXP_R;
			eb = EXP_B;
			el = EXP_L;
			break;
		case 1:
			wf = WAL_R;
			wr = WAL_B;
			wb = WAL_L;
			wl = WAL_T;
			ef = EXP_R;
			er = EXP_B;
			eb = EXP_L;
			el = EXP_T;
			break;
		case 2:
			wf = WAL_B;
			wr = WAL_L;
			wb = WAL_T;
			wl = WAL_R;
			ef = EXP_B;
			er = EXP_L;
			eb = EXP_T;
			el = EXP_R;
			break;
		case 3:
			wf = WAL_L;
			wr = WAL_T;
			wb = WAL_R;
			wl = WAL_B;
			ef = EXP_L;
			er = EXP_T;
			eb = EXP_R;
			el = EXP_B;
			break;
		}
		
		
		if (!nodeCheck(nodeList[node(nodeID - 1)])) //new node
		{
			simLog("recording new node...");

			//create node
			if (!API_wallFront()) //is front a path?
			{
				switch (direction)
				{
				case 0:
					nodeList[node(nodeID - 1)][WAL_T] = true;
					if (!nodeCheck(nodeList[node_T(nodeID - 1)]))
						nodeList[node(nodeID - 1)][EXP_T] = true;
					else
						nodeList[node_T(nodeID - 1)][EXP_B] = false;
					break;
				case 1:
					nodeList[node(nodeID - 1)][WAL_R] = true;
					if (!nodeCheck(nodeList[node_R(nodeID - 1)]))
						nodeList[node(nodeID - 1)][EXP_R] = true;
					else
						nodeList[node_R(nodeID - 1)][EXP_L] = false;
					break;
				case 2:
					nodeList[node(nodeID - 1)][WAL_B] = true;
					if (!nodeCheck(nodeList[node_B(nodeID - 1)]))
						nodeList[node(nodeID - 1)][EXP_B] = true;
					else
						nodeList[node_B(nodeID - 1)][EXP_T] = false;
					break;
				case 3:
					nodeList[node(nodeID - 1)][WAL_L] = true;
					if (!nodeCheck(nodeList[node_L(nodeID - 1)]))
						nodeList[node(nodeID - 1)][EXP_L] = true;
					else
						nodeList[node_L(nodeID - 1)][EXP_R] = false;
					break;
				}
			}
			if (!API_wallRight()) //is right a path?
			{
				switch (direction)
				{
				case 0:
					nodeList[node(nodeID - 1)][WAL_R] = true;
					if (!nodeCheck(nodeList[node_R(nodeID - 1)]))
						nodeList[node(nodeID - 1)][EXP_R] = true;
					else
						nodeList[node_R(nodeID - 1)][EXP_L] = false;
					break;
				case 1:
					nodeList[node(nodeID - 1)][WAL_B] = true;
					if (!nodeCheck(nodeList[node_B(nodeID - 1)]))
						nodeList[node(nodeID - 1)][EXP_B] = true;
					else
						nodeList[node_B(nodeID - 1)][EXP_T] = false;
					break;
				case 2:
					nodeList[node(nodeID - 1)][WAL_L] = true;
					if (!nodeCheck(nodeList[node_L(nodeID - 1)]))
						nodeList[node(nodeID - 1)][EXP_L] = true;
					else
						nodeList[node_L(nodeID - 1)][EXP_R] = false;
					break;
				case 3:
					nodeList[node(nodeID - 1)][WAL_T] = true;
					if (!nodeCheck(nodeList[node_T(nodeID - 1)]))
						nodeList[node(nodeID - 1)][EXP_T] = true;
					else
						nodeList[node_T(nodeID - 1)][EXP_B] = false;
					break;
				}
			}
			switch (direction) //back is not a wall
			{
			case 0:
				nodeList[node(nodeID - 1)][WAL_B] = true;
				break;
			case 1:
				nodeList[node(nodeID - 1)][WAL_L] = true;
				break;
			case 2:
				nodeList[node(nodeID - 1)][WAL_T] = true;
				break;
			case 3:
				nodeList[node(nodeID - 1)][WAL_R] = true;
				break;
			}
			if (!API_wallLeft()) //is left a path?
			{
				switch (direction)
				{
				case 0:
					nodeList[node(nodeID - 1)][WAL_L] = true;
					if (!nodeCheck(nodeList[node_L(nodeID - 1)]))
						nodeList[node(nodeID - 1)][EXP_L] = true;
					else
						nodeList[node_L(nodeID - 1)][EXP_R] = false;
					break;
				case 1:
					nodeList[node(nodeID - 1)][WAL_T] = true;
					if (!nodeCheck(nodeList[node_T(nodeID - 1)]))
						nodeList[node(nodeID - 1)][EXP_T] = true;
					else
						nodeList[node_T(nodeID - 1)][EXP_B] = false;
					break;
				case 2:
					nodeList[node(nodeID - 1)][WAL_R] = true;
					if (!nodeCheck(nodeList[node_R(nodeID - 1)]))
						nodeList[node(nodeID - 1)][EXP_R] = true;
					else
						nodeList[node_R(nodeID - 1)][EXP_L] = false;
					break;
				case 3:
					nodeList[node(nodeID - 1)][WAL_B] = true;
					if (!nodeCheck(nodeList[node_B(nodeID - 1)]))
						nodeList[node(nodeID - 1)][EXP_B] = true;
					else
						nodeList[node_B(nodeID - 1)][EXP_T] = false;
					break;
				}
			}
		}
		//Choose next available route, not previously traveled if possible
		if (!nodeList[node(nodeID - 1)][ef] && !nodeList[node(nodeID - 1)][el] && !nodeList[node(nodeID - 1)][er]) //if no unexplored directions
		{
			simLog("Current node has no unexplored paths, searching for nearest node with unexplored paths...");

			//Verify that there are still explorable nodes in the nodeList array
			short int san = 0;
			for (int i = 0; i < NODES; i++)
			{
				if (nodeList[i][EXP_T] || nodeList[i][EXP_R] || nodeList[i][EXP_B] || nodeList[i][EXP_L])
				{
					break;
				}
				san = i;
			}
			if (san == NODES - 1)
			{
				simLog("All nodes have been fully explored.\n\t\tENDING SCAN");
				return direction;
			}
			else
			{
				fprintf(stderr, "%d\n", san);
				fflush(stderr);
			}

			//travel to next nearest not fully explored node
			direction = pathChooseAlt(nodeList, nodeID, direction, position);
			//reorient directions
			nodeID = getID(position);
			switch (direction)
			{
			case 0:
				wf = WAL_T;
				wr = WAL_R;
				wb = WAL_B;
				wl = WAL_L;
				ef = EXP_T;
				er = EXP_R;
				eb = EXP_B;
				el = EXP_L;
				break;
			case 1:
				wf = WAL_R;
				wr = WAL_B;
				wb = WAL_L;
				wl = WAL_T;
				ef = EXP_R;
				er = EXP_B;
				eb = EXP_L;
				el = EXP_T;
				break;
			case 2:
				wf = WAL_B;
				wr = WAL_L;
				wb = WAL_T;
				wl = WAL_R;
				ef = EXP_B;
				er = EXP_L;
				eb = EXP_T;
				el = EXP_R;
				break;
			case 3:
				wf = WAL_L;
				wr = WAL_T;
				wb = WAL_R;
				wl = WAL_B;
				ef = EXP_L;
				er = EXP_T;
				eb = EXP_R;
				el = EXP_B;
				break;
			}
		}

		//choose path
		if (!API_wallFront() && nodeList[node(nodeID - 1)][ef])
		{
			direction = updateDir(direction, 0);
			nodeList[node(nodeID - 1)][ef] = false;
		}
		else if (!API_wallLeft() && nodeList[node(nodeID - 1)][el])
		{
			API_turnLeft();
			direction = updateDir(direction, 3);
			nodeList[node(nodeID - 1)][el] = false;
		}
		else if (!API_wallRight() && nodeList[node(nodeID - 1)][er])
		{
			API_turnRight();
			direction = updateDir(direction, 1);
			nodeList[node(nodeID - 1)][er] = false;
		}
		else
		{
			simLog("\tERROR: expected node class to not be DEADEND");
			API_turnRight();
			API_turnRight();
			direction = updateDir(direction, 2);
		}

		//Move beyond current node
		if (!API_wallFront()) //verify that this is a valid move to prevent position errors
		{
			API_moveForward();
			updatePos(position, direction, 1);
		}
		else
		{
			simLog("FATAL ERROR: expected valid direction to be picked, but there's a wall in front.");
			return direction;
		}

		//vvvv debug code vvvv
		if (position[0] < 0 || position[0] >= 16)
		{
			simLog("FATAL X position ERROR");
			return direction;
		}
		if (position[1] < 0 || position[1] >= 16)
		{
			simLog("FATAL Y position ERROR");
			return direction;
		}
	}
}
