#include "mapInteract.h"

COORD teleportation(string str, int x, int y)
{
	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	//i store coords in a string for portal
	//str = { 1 , 2 , 3 , 4};
	//		  (P1)     (P2)
	for (int i = 0; i < str.size() / 4; i++)
	{
		//becuz it is in a set of 4
		int j = 4;
		//check if player is in 1st portal
		if (x == str[i * j] && y == str[i * j + 1])
		{
			//move if is in P1
			coord.X = str[i * j + 2];
			coord.Y = str[i * j + 3];

			return coord;
		}
		//check if player is in 2nd portal
		else if (x == str[i * j + 2] && y == str[i * j + 3])
		{
			//move if is in P2
			coord.X = str[i * j];
			coord.Y = str[i * j + 1];

		}
		j++;
	}
	return coord;
}

bool dooring(COORD lever1, COORD lever2, int x1, int y1, int x2, int y2, int xb, int yb)
{
	if (lever1.X == x1 && lever1.Y == y1 && lever2.X == x2 && lever2.Y == y2)
	{
		return true;
	}
	else if (lever1.X == x2 && lever1.Y == y2 && lever2.X == x1 && lever2.Y == y1)
	{
		return true;
	}
	else if (lever1.X == x1 && lever1.Y == y1 && lever2.X == xb && lever2.Y == yb)
	{
		return true;
	}
	else if (lever1.X == x2 && lever1.Y == y2 && lever2.X == xb && lever2.Y == yb)
	{
		return true;
	}
	else
	{
		return false;
	}
}