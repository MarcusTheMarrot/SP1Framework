#include "extract.h"

string extractMap(int *level)
{
	string myfile;
	string row;
	string master;

	//if (*level == 0)
	//{
	//	myfile = "Testmap/sampleLevel.txt";
	//}
	//else if (*level == 1)
	//{
	//	myfile = "Testmap/test.txt";
	//}
	//else if (*level == 2)
	//{
	//	myfile = "Testmap/test2.txt";
	//}
	//else if (*level == 3)
	//{
	//	myfile = "Testmap/test3.txt";
	//}
	if (*level == 11)
	{
		myfile = "Level 1/level1-1.txt";
	}
	if (*level == 12)
	{
		myfile = "Level 1/level1-2.txt";
	}
	if (*level == 13)
	{
		myfile = "Level 1/level1-3.txt";
	}
	if (*level == 14)
	{
		myfile = "Level 1/level1-4.txt";
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