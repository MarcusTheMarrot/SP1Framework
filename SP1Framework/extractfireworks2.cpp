#include "extractfirework.h"

string extractfireworks2(int *level)
{
	string myfile;
	string row;
	string fwart2;
	if (*level == 0)
	{
		ifstream file("fireworks2.txt");
		if (file.is_open())
		{
			while (file.good())
			{
				getline(file, row);
				fwart2 += row;
			}
			file.close();
		}
	}
	return fwart2;
}