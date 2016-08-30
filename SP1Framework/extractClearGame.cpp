#include "extractClearGame.h"

string extractclear(int *level)
{
	string myfile;
	string row;
	string clearart;
	if (*level == 0)
	{
		ifstream file("cleargame.txt");

		if (file.is_open())
		{
			while (file.good())
			{
				getline(file, row);
				clearart += row;
			}
			file.close();
		}
	}
	return clearart;
}