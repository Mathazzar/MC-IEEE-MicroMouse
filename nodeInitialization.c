#include "API.h"

#define INF 1024
#define NOPATHS 255
#define WALL 9
#define MAXDIST 14


//Initializes node list
void nodeInitialization(int NodeList[256][5])
{
	int i;
	for (i = 0; i < 256; i++)
	{
		NodeList[i][0] = i + 1;//
		NodeList[i][1] = INF;
		NodeList[i][2] = 0;
		NodeList[i][3] = 0;
		NodeList[i][4] = NOPATHS;
	}

	API_setColor(0, 0, 'Y'); //visual mark
	API_setText(0, 0, "start");
	API_setColor(7, 7, 'Y');
	API_setColor(7, 8, 'Y');
	API_setColor(8, 8, 'Y');
	API_setColor(8, 7, 'Y');
	API_setText(7, 7, "Goal");
	API_setText(7, 8, "Goal");
	API_setText(8, 8, "Goal");
	API_setText(8, 7, "Goal");

	//Node Identification Number //Heuristic Distance //Backpath //0||1 //PathList
	NodeList[1][0] = 1;//
	NodeList[1][1] = MAXDIST; //7 inward + 7 inward
	NodeList[1][2] = 1; //NULL == 0
	NodeList[1][3] = 1; //0 = Corner/Unexplorable || 1 = Explorable //non-explorable //hmm 0 or 1 at S depends on maze and affects main()
	NodeList[1][4] = 0;//PathList[0]
}//end initialization
 //confused Nodelist priority queue
