#include "extractClearGame.h"

string extractclear(COORD spawn, int x, int y, int *level)
{
	string myfile;
	string row;
	string clearart;

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
	
	return clearart;
}