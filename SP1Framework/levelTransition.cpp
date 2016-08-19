#include "levelTransition.h"

COORD mapTransition(COORD spawn,int x, int y, int *level)
{
	if (x == 59 && y == 19 && *level == 0)
	{
		spawn.X = 0;
		spawn.Y = 19;
		*level += 1;
	}
	else if (x == 59 && y == 2 && *level == 1)
	{
		*level += 1;
		spawn.X = 0;
		spawn.Y = 2;
	}
	return spawn;
}