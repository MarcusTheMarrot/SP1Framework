#include "extract.h"

string extractMap(int *level)
{
	string myfile;
	string row;
	string master;

	if (*level == 0)
	{
		myfile = "sampleLevel.txt";
	}
	else if (*level == 1)
	{
		myfile = "test.txt";
	}
	else if (*level == 2)
	{
		myfile = "test2.txt";
	}
	else if (*level == 3)
	{
		myfile = "test3.txt";
	}

	ifstream file(myfile);
	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, row);
			master += row;
		}
		file.close();
	}
	return master;
}