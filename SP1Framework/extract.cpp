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
	if (*level == 21)
	{
		myfile = "Level 2/level2-1.txt";
	}
	if (*level == 22)
	{
		myfile = "Level 2/level2-2.txt";
	}
	if (*level == 23)
	{
		myfile = "Level 2/level2-3.txt";
	}
	if (*level == 31)
	{
		myfile = "Level 3/level3-1.txt";
	}
	if (*level == 32)
	{
		myfile = "Level 3/level3-2.txt";
	}
	if (*level == 33)
	{
		myfile = "Level 3/level3-3.txt";
	}
	if (*level == 41)
	{
		myfile = "Level 4/level4-1.txt";
	}
	if (*level == 42)
	{
		myfile = "Level 4/level4-2.txt";
	}
	if (*level == 43)
	{
		myfile = "Level 4/level4-3.txt";
	}
	if (*level == 51)
	{
		myfile = "Level 5/level5-1.txt";
	}
	if (*level == 52)
	{
		myfile = "Level 5/level5-2.txt";
	}
	if (*level == 0)
	{
		myfile = "Testmap/sampleLevel.txt";
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