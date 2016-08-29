#include "Portalgun-teleporting.h"

COORD PlayerPositionTeleport(COORD player, COORD Firstportal, COORD Secondportal, COORD Thirdportal, COORD Fourthportal, bool first, bool second, bool third, bool fourth)
{
	if (player.X == Firstportal.X && player.Y == Firstportal.Y && first && second)
	{
		player.X = Secondportal.X;
		player.Y = Secondportal.Y;
	}
	else if (player.X == Secondportal.X && player.Y == Secondportal.Y && first && second)
	{
		player.X = Firstportal.X;
		player.Y = Firstportal.Y;
	}
	if (player.X == Thirdportal.X && player.Y == Thirdportal.Y && third && fourth)
	{
		player.X = Fourthportal.X;
		player.Y = Fourthportal.Y;
	}
	else if (player.X == Fourthportal.X && player.Y == Fourthportal.Y && third && fourth)
	{
		player.X = Thirdportal.X;
		player.Y = Thirdportal.Y;
	}
	return player;
}

