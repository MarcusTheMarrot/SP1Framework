#include "extractscreen.h"

string extractscreen(int x)
{
	string myfile;
	string row;
	string screen;
	
	if (x == 0)
	{
		myfile = "title.txt";
	}
	if (x == 1)
	{
		myfile = "title2.txt";
	}
	if (x == 2)
	{
		myfile = "Instruction.txt";
	}
	if (x == 3)
	{
		myfile = "PickALevel.txt";
	}
	if (x == 4)
	{
		myfile = "GameOver.txt";
	}
	if (x == 5)
	{
		myfile = "firework.txt";
	}
	if (x == 6)
	{
		myfile = "fireworks2.txt";
	}

	ifstream file(myfile);
	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, row);
			screen += row;
		}
		file.close();
	}
	return screen;
}