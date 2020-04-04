#define INF 1024
#define NOPATHS 255
#define WALL 9
#define MAXDIST 14

//int calculate_heuristic_distance(int NIN, char Q1[], char Q2[], char Q3[], char Q4[]);
//void simLog(char* text);

//Choice
int choice(int NIN, int PathList[256][3], int orientation)
{
	int i;
	int min = 0;
	int minimum = MAXDIST;
	int choices = 0;
	int option1 = -1;
	int option2 = -1;
	int orientationoption1 = -1;
	int orientationoption2 = -1;
	int optimalchoice = -1;
	int suboptimalchoice = -1;
	int leastoptimalchoice = -1;

	for (i = 0; i < 2; i++) //Heuristic Remaining Distance to Goal
	{
		if (PathList[NIN][i] != 0) //Adjacent accessible coordinate
		{
			min = calculate_heuristic_distance(PathList[NIN][i]); //Calculate heuristic remaining distance

			if (min < minimum) //Optimal choice
			{
				minimum = min;
				leastoptimalchoice = suboptimalchoice;
				suboptimalchoice = optimalchoice;
				optimalchoice = i;

				if (PathList[NIN][i] == NIN + 16)
				{
					orientationoption1 = 0;
					option1 = i;
				}
				else if (PathList[NIN][i] == NIN - 16)
				{
					orientationoption1 = 1;
					option1 = i;
				}
				else if (PathList[NIN][i] == NIN + 1)
				{
					orientationoption1 = 2;
					option1 = i;
				}
				else if (PathList[NIN][i] == NIN - 1)
				{
					orientationoption1 = 3;
					option1 = i;
				}
			}

			else if (min == minimum) //Equidistant paths evaluated based on orientation
			{
				if (PathList[NIN][i] == NIN + 16)
				{
					orientationoption2 = 0;
					option2 = i;
				}
				else if (PathList[NIN][i] == NIN - 16)
				{
					orientationoption2 == 1;
					option2 = i;
				}
				else if (PathList[NIN][i] == NIN + 1)
				{
					orientationoption2 == 2;
					option2 = i;
				}
				else if (PathList[NIN][i] == NIN - 1);
				{
					orientationoption2 = 3;
					option2 = i;
				}
				leastoptimalchoice = suboptimalchoice;
				if (orientation == orientationoption1)
				{
					optimalchoice = option1;
					suboptimalchoice = option2;
				}
				else if (orientation == orientationoption2)
				{
					optimalchoice = option2;
					suboptimalchoice = option1;
				}
			}

			else //Suboptimal and least optimal choice
			{
				if (suboptimalchoice != -1)
				{
					leastoptimalchoice = i; //not evaluating orientation not in the mood
				}
				else
				{
					suboptimalchoice = i;
				}
			}

		}
	}//optimal choice


	 //Count choices
	if (suboptimalchoice != -1)
	{
		choices++;
	}
	if (leastoptimalchoice != -1)
	{
		choices++;
	}

	//Explore all choices
	for (i = 0; i < choices; i++)
	{

	}
	if (optimalchoice == 0)
	{
		choseForward(orientation, NIN);
	}
	else if (optimalchoice == 1)
	{
		choseRight(orientation, NIN);
	}
	else if (optimalchoice == 2)
	{
		choseLeft(orientation, NIN);
	}

	//after it explores all 3

	//choose [h]

	//after [h] return to main 

}//end choice