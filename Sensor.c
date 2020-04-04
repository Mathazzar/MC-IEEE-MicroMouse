#include <stdbool.h>
#include "API.h"

/*Sensor*/
//int sensorFront;
bool wallFront()
{
	return API_wallFront();
	//int walldist = (IRV / analogRead(sensorFront));
	//if (walldist > WALL)
	//{
	//  return 1; //using 1 instead of 0
	//}
	//else
	//{
	//  return 0; //using 0 instead of 1
	//}
}//end front wall sensor

 //int sensorRight;
bool wallRight()
{
	return API_wallRight();
	//int walldist = (IRV / analogRead(sensorRight));
	//if (walldist > WALL)
	//{
	//  return 1; //using 1 instead of 0
	//}
	//else
	//{
	//  return 0; //using 0 instead of 1
	//}
}//end right wall sensor

 //int sensorLeft;
bool wallLeft()
{
	return API_wallLeft();

	//int walldist = (IRV / analogRead(sensorLeft));
	//if (walldist > WALL)
	//{
	//  return 1; //using 1 instead of 0
	//}
	//else
	//{
	//  return 0; //using 0 instead of 1
	//}

} //end left wall sensor

  /*End Sensor*/