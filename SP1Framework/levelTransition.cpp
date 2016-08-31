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
	else if (x == 59 && y == 19 && *level == 12)
	{
		spawn.X = 0;
		spawn.Y = 19;
		*level = 13;
		*transisted = true;
	}
	else if (x == 59 && y == 4 && *level == 13)
	{
		spawn.X = 0;
		spawn.Y = 4;
		*level = 14;
		*transisted = true;
	}
	else if (x == 59 && y == 3 && *level == 14)
	{
		spawn.X = 0;
		spawn.Y = 4;
		*level = 21;
		*transisted = true;
	}
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

	if (x == 59 && y == 19 && *level == 23)
	{
		spawn.X = 0;
		spawn.Y = 19;
		*level = 31;
		*transisted = true;
	}

	if (x == 59 && y == 19 && *level == 31)
	{
		spawn.X = 0;
		spawn.Y = 19;
		*level = 32;
		*transisted = true;
	}
	if (x == 59 && y == 19 && *level == 32)
	{
		spawn.X = 0;
		spawn.Y = 19;
		*level = 33;
		*transisted = true;
	}
	if (x == 59 && y == 2 && *level == 33)
	{
		spawn.X = 0;
		spawn.Y = 2;
		*level = 41;
		*transisted = true;
	}
	if (x == 59 && y == 19 && *level == 41)
	{
		spawn.X = 0;
		spawn.Y = 19;
		*level = 42;
		*transisted = true;
	}
	if (x == 59 && y == 2 && *level == 42)
	{
		spawn.X = 0;
		spawn.Y = 2;
		*level = 43;
		*transisted = true;
	}
	if (x == 59 && y == 19 && *level == 43)
	{
		spawn.X = 0;
		spawn.Y = 19;
		*level = 51;
		*transisted = true;
	}
	if (x == 59 && y == 19 && *level == 51)
	{
		spawn.X = 0;
		spawn.Y = 19;
		*level = 52;
		*transisted = true;
	}
	if (x == 60 && y == 19 && *level == 52)
	{
		spawn.X = 5;
		spawn.Y = 15;
		*level = 0;
		*transisted = true;
	}
	if (x == 59 && y == 19 && *level == 0)
	{
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