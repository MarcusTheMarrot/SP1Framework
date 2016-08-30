#include "extractfirework.h"

string extractfirework(int *level)
{
	string myfile;
	string row;
	string fwart;
	if (*level == 0)
	{
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
	}
	return fwart;
}