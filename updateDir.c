
#include <stdbool.h>	
#include <stdio.h>

void simLog(char* text); //modified from main.c in mms example (https://github.com/mackorone/mms-c)

short int updateDir(short int direction, short int relativeChange)
{
	short int dire = direction;
	fprintf(stderr, "DIRECTION: %d\n", dire);
	fflush(stderr);
	switch (relativeChange)
	{
	case 0: //straight
		simLog("Turning Straight?");
		break;
	case 1: //turn right
		simLog("Turning Right");
		dire++;
		if (dire > 3)
			dire -= 4;
		fprintf(stderr, "DIRECTION: %d\n", dire);
		fflush(stderr);
		break;
	case 2: //about face
		simLog("About Face");
		dire += 2;
		if (dire > 3)
			dire -= 4;
		fprintf(stderr, "DIRECTION: %d\n", dire);
		fflush(stderr);
		break;
	case 3: //turn left
		simLog("Turning Left");
		dire--;
		if (dire < 0)
			dire += 4;
		fprintf(stderr, "DIRECTION: %d\n", dire);
		fflush(stderr);
		break;
	}
	return dire;
}
