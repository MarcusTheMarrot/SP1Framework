#include "extractfirework.h"

string extractfirework(COORD spawn, int x, int y, int *level)
{
	string myfile;
	string row;
	string fwart;

	ifstream file("firework.txt"); 

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, row);
			fwart += row;
		}
		file.close();
	}
	return fwart;
}