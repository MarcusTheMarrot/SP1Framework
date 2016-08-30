#include "extractSplashTwo.h"

string extractSplashTwo(int spl)
{
	string myfile;
	string row;
	string splashart2;
	if (spl >= -1 && spl <= 2)
	{
		ifstream file("title2.txt");

		if (file.is_open())
		{
			while (file.good())
			{
				getline(file, row);
				splashart2 += row;
			}
			file.close();
		}
	}
	return splashart2;
}