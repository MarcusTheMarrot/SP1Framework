#include "colour.h"

WORD getColour(int selected, int current)
{
	if (selected == current)
	{
		return 0x70;
	}
	else
	{
		return 0x07;
	}
	
}