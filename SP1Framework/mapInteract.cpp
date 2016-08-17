#include "mapInteract.h"

COORD teleportation(string str, int x, int y)
{
	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	for (int i = 0; i < str.size() / 4; i++)
	{
		int j = 4;
		if (x == str[i * j] && y == str[i * j + 1])
		{
			coord.X = str[i * j + 2];
			coord.Y = str[i * j + 3];

			return coord;
		}
		else if (x == str[i * j + 2] && y == str[i * j + 3])
		{
			coord.X = str[i * j];
			coord.Y = str[i * j + 1];

			return coord;
		}
		j++;
	}
	return coord;
}
