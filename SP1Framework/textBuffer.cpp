#include "textBuffer.h"

string text(int level)
{
	string text;
	if (level == 11)
	{
		text = "Welcome to Potaru, proceed to the green door.";
	}
	if (level == 12)
	{
		text = "Now it's harder, because simply walking to the exit is too easy.";
	}
	if (level == 13)
	{
		text = "Don't step into a fire, unless your dream is to be a fried chicken";
	}
	if (level == 14)
	{
		text = "That's quite the sea of fire, if only you can teleport there...";
	}

	return text;
}