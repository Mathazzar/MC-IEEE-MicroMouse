short int updateDir(short int direction, short int relativeChange)
{
	short int dire = direction;
	switch (relativeChange)
	{
	case 0: //straight
		break;
	case 1: //turn right
		dire++;
		if (dire >= 4)
			dire -= 4;
		break;
	case 2: //about face
		dire++;
		dire++;
		if (dire >= 4)
			dire -= 4;
		break;
	case 3: //turn left
		dire--;
		if (dire <= -1)
			dire += 4;
		break;
	}
	return dire;
}