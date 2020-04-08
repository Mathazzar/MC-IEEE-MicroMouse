#include <stdbool.h>
#include <stdio.h>
#include "API.h" //only needed for simulator use

#define INFINITY 1024
#define DATA 7

void simLog(char* text); //modified from main.c in mms example (https://github.com/mackorone/mms-c)

bool stackInsert(int nodeList[256][DATA], int nodeCurrent[DATA]) //adds new node into correct rank in stack based on distance
{
	simLog("\t\tInserting node to stack...");
	//bool rankFound = 0; //becomes 1 when stack rank for new node is found
	int tempArr[DATA]; //temporary storage array to allow for swaping in stack
	for (int i = 0; i < 256; i++) //hope element 256 has nothing in it... (skipped in this loop)
	{
		if (nodeList[i][0] != INFINITY)
		{
			fprintf(stderr, "\t\t\tRank of node %d: %d \n", nodeList[i][0], i);
			fflush(stderr);
		}

		if (nodeCurrent[0] == INFINITY)//if current node is blank
		{
			simLog("All nodes on stack checked.");
			return true;
		}
		else if (nodeList[i][0] == nodeCurrent[0])//if current node has same ID
		{
			simLog("Node already exists.");
			return false;
		}
		else if (nodeCurrent[1] < nodeList[i][1])
		{
			//store information of node in ranking below current node to temporary array
			for (int j = 0; j < DATA; j++)
			{
				tempArr[j] = nodeList[i][j];
			}

			//add current node to the stack
			for (int j = 0; j < DATA; j++)
			{
				nodeList[i][j]=nodeCurrent[j];
			}

			//treat the node in temporary storage as the new current node
			for (int j = 0; j < DATA; j++)
			{
				nodeCurrent[j] = tempArr[j];
			}
			fprintf(stderr, "\t\t\tRank of node %d: %d \n", nodeList[i][0], i);
			fflush(stderr);
		}
		/*
		if (nodeList[i - 1][0] != INFINITY) //if a recorded node
		{
			fprintf(stderr, "\t\t\tRank of node %d: %d \n", nodeList[i - 1][0], i);
			fflush(stderr);
		}

		//if the current node is a blank node, all existing nodes have been shifted over and the loop can end
		//if the current node already exists on the stack, then it doesn't need to be added to the stack, and cthe loop can end
		if (nodeCurrent[0] == INFINITY)//if current node is blank
		{
			simLog("All nodes on stack checked.");
			return true;
		}
		else if (nodeList[i][0] == nodeCurrent[0])//if current node has same ID
		{
			simLog("Node already exists.");
			return false;
		}
		//starting inserting nodes down the stack
		else if ((nodeList[i - 1][1] < nodeCurrent[1]) && (nodeList[i][1] > nodeCurrent[1]))
		{
			//store information of node in ranking below current node to temporary array
			tempArr[0] = nodeList[i][0];
			tempArr[1] = nodeList[i][1];
			tempArr[2] = nodeList[i][2];
			tempArr[3] = nodeList[i][3];

			//add current node to the stack
			nodeList[i][0] = nodeCurrent[0];
			nodeList[i][1] = nodeCurrent[1];
			nodeList[i][2] = nodeCurrent[2];
			nodeList[i][3] = nodeCurrent[3];

			//treat the node in temporary storage as the new current node
			nodeCurrent[0] = tempArr[0];
			nodeCurrent[1] = tempArr[1];
			nodeCurrent[2] = tempArr[2];
			nodeCurrent[3] = tempArr[3];
		}
		*/
	}
	simLog("ERROR: NO SPACE LEFT ON STACK");
}