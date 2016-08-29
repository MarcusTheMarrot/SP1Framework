#include "extractSplashOne.h"

string extractSplashOne(int spl)
{
	string myfile;
	string row;
	string splashart;

	ifstream file("title.txt");

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, row);
			splashart += row;
		}
		file.close();
	}
	
	return splashart;
}