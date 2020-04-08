/*
Written by squidKnight, Mathazzar
Last modified: 04/7/20
Purpose: run the program on the simulator, which requires a main.c

NOTE: ONLY USED FOR SIMULATOR, NOT FOR USE ON ARDUINO!!
*/

#define DATA 7

int nodeList[256][7]; //0 = nodeID, 1 = distance from start, 2 = previous node, 3 = left path, 4 = front path, 5 = right path, 6 = orientation

void nodeInit(int nodeList[256][DATA]); //initialize nodeList
void scan(int nodeList[256][DATA]); //scans the maze

int main()
{
	nodeInit(nodeList);
	scan(nodeList);
	return 0;
}
