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
	if (x == 59 && y == 4 && *level == 13)
	{
		spawn.X = 0;
		spawn.Y = 4;
		*level = 14;
		*transisted = true;
	}
<<<<<<< HEAD
	
	

	if (x == 59 & y == 4 && *level == 14)
=======
	if (x == 59 && y == 4 && *level == 14)
>>>>>>> 5359771ac0a8a33dc506094d5c17582c1cba7916
	{
		spawn.X = 0;
		spawn.Y = 4;
		*level = 21;
		*transisted = true;
	}
<<<<<<< HEAD

=======
	if (x == 59 && y == 19 && *level == 21)
	{
		spawn.X = 0;
		spawn.Y = 19;
		*level = 22;
		*transisted = true;
	}
	if (x == 59 && y == 2 && *level == 22)
	{
		spawn.X = 0;
		spawn.Y = 2;
		*level = 23;
		*transisted = true;
	}
>>>>>>> 5359771ac0a8a33dc506094d5c17582c1cba7916
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