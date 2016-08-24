#include "Portalgun-teleporting.h"

COORD Player1Position(COORD player1, COORD Firstportal, COORD Secondportal, COORD Thirdportal, COORD Fourthportal, bool first, bool second, bool third, bool fourth)
{
	if (player1.X == Firstportal.X && player1.Y == Firstportal.Y && first && second)
	{
		player1.X = Secondportal.X;
		player1.Y = Secondportal.Y;
	}
	else if (player1.X == Secondportal.X && player1.Y == Secondportal.Y && first && second)
	{
		player1.X = Firstportal.X;
		player1.Y = Firstportal.Y;
	}
	if (player1.X == Thirdportal.X && player1.Y == Thirdportal.Y && third && fourth)
	{
		player1.X = Fourthportal.X;
		player1.Y = Fourthportal.Y;
	}
	else if (player1.X == Fourthportal.X && player1.Y == Fourthportal.Y && third && fourth)
	{
		player1.X = Thirdportal.X;
		player1.Y = Thirdportal.Y;
	}
	return player1;
}

COORD Player2Position(COORD player2, COORD Firstportal, COORD Secondportal, COORD Thirdportal, COORD Fourthportal, bool first, bool second, bool third, bool fourth)
{
	if (player2.X == Firstportal.X && player2.Y == Firstportal.Y && first && second)
	{
		player2.X = Secondportal.X;
		player2.Y = Secondportal.Y;
	}
	else if (player2.X == Secondportal.X && player2.Y == Secondportal.Y && first && second)
	{
		player2.X = Firstportal.X;
		player2.Y = Firstportal.Y;
	}
	if (player2.X == Thirdportal.X && player2.Y == Thirdportal.Y && third && fourth)
	{
		player2.X = Fourthportal.X;
		player2.Y = Fourthportal.Y;
	}
	else if (player2.X == Fourthportal.X && player2.Y == Fourthportal.Y && third && fourth)
	{
		player2.X = Thirdportal.X;
		player2.Y = Thirdportal.Y;
	}
	return player2;
}