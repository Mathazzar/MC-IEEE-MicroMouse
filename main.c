/*
Written by Mathazzar
Last modified: 11/12/20
Purpose: negotiate commands between the mms simulator on a PC and an arduino connected to that PC.

NOTE: CHECK fopen() AND VERIFY IT'S POINTING TO THE CORRECT USB PORT BEFORE COMPILING.
*/

#include <stdio.h>
#include "API.h" //only needed for simulator use
#include <stdbool.h>

void simLog(char* text); //modified from main.c in mms example (https://github.com/mackorone/mms-c)

int main()
{
	//open serial port
	//uses method from stdio.h: https://stackoverflow.com/questions/36571268/how-to-read-data-from-arduino-board-to-pc-using-c
	FILE *arduino;
	arduino = fopen("", "w+"); //first argument is dependant on specific PC and USB port used.
	if (arduino == NULL)
	{
		simLog("FATAL ERROR: unable to open serial port.");
		return 0;
	}
	else
	{
		fprintf(stderr, "serial port located at %d.\n", arduino);
		fflush(stderr);
	}
	//wait for Arduino to acknowledge (3-way handshake?)

	while (1 == 1)
	{
		//wait for command
		int serialIN;
		do
		{
			serialIN = 10;
			if (fscanf(arduino, "%d", &serialIN) != 1) //assumes that if data is written to the serial line, fscanf will return a 1, and will return a 0 otherwise. Expects a single-digit integer.
				serialIN = 10;
		} while (serialIN != 10);

		//interpret command and pass to simulator, then pass simulator's response back to arduino
		switch (serialIN)
		{
		case 0: //if API_wallFront()
			simLog("Checking front wall.");
			fprintf(arduino, "%d", API_wallFront());
			fflush(arduino);
			break;
		case 1: //else if API_wallRight()
			simLog("Checking right wall.");
			fprintf(arduino, "%d", API_wallRight());
			fflush(arduino);
			break;
		case 2: //else if API_wallLeft()
			simLog("Checking left wall.");
			fprintf(arduino, "%d", API_wallLeft());
			fflush(arduino);
			break;
		case 3: //else if API_moveForward()
			simLog("Moving forwards.");
			fprintf(arduino, "%d", API_moveForward());
			fflush(arduino);
			break;
		case 4: //else if API_turnRight()
			simLog("Turning right.");
			API_turnRight();
			break;
		case 5: //else if API_turnLeft()
			simLog("Turning left.");
			API_turnLeft();
			break;
		case 6: //else assume error message
		{
			bool newLine = false;
			while (!newLine)
			{
				char serialSTR[10];
				fscanf(arduino, "%s", serialSTR);
				for (int i = 0; i < 10; i++)
				{
					if (serialSTR[i] == '\n')
						newLine = true;
				}
				if (!newLine)
				{
					fprintf(stderr, "%s", serialSTR);
					fflush(stderr);
				}
			}
			simLog("");
			break;
		}
		case 7: //else program finished
			simLog("PROGRAM COMPLETE.");
			return 0;
		}
	}

	//should be unreachable
	return 0;
}
