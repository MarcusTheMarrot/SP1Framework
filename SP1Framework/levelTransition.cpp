#include "levelTransition.h"

COORD mapTransition(COORD spawn,int x, int y, int *level, bool *transisted)
{
	if (x == 59 && y == 4 && *level == 11)
	{
		spawn.X = 0;
		spawn.Y = 4;
		*level = 12;
		*transisted = true;
	}
	if (x == 59 && y == 19 && *level == 12)
	{
		spawn.X = 0;
		spawn.Y = 19;
		*level = 13;
		*transisted = true;
	}
	if (x == 59 & y == 4 && *level == 13)
	{
<<<<<<< HEAD
		*level += 1; 
=======

		*level += 1; 

>>>>>>> 8e4b9a996a8ac27b0ead8621f3bfa1413b30a2a1
		spawn.X = 0;
		spawn.Y = 4;
		*level = 14;
		*transisted = true;
	}
	//else if (x == 59 && y == 2 && *level == 11)
	//{
	//	*level += 1;
	//	spawn.X = 0;
	//	spawn.Y = 2;
	//	*transisted = true;
	//}
	//else if (x == 59 && y == 19 && *level == 2)
	//{
	//	*level += 1;
	//	spawn.X = 0;
	//	spawn.Y = 19;
	//	*transisted = true;
	//}
	else
	{
		transisted = false;
	}
	return spawn;
}