#include "extractmain.h"

string extractmain(int lvl)
{
	string myfile;
	string row;
	string menuart;

	ifstream file("PickALevel.txt"); // read file from PickALevel.txt to print the ascii art

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, row);
			menuart += row;
		}
		file.close();
	}
	return menuart;
}