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
	if (level == 21)
	{
		text = "These intra-dimensional gates have proven to be completely safe.";
	}
	if (level == 22)
	{
		text = "The Device, however, has not.";
	}
	if (level == 23)
	{
		text = "Quit now and cake will be served immediately.";
	}
	if (level == 31)
	{
		text = "Cake, and grief counseling, will be available at the conclusion of the test. ";
	}
	if (level == 32)
	{
		text = "Your entire life has been a mathematical error... a mathematical error I'm about to correct!";
	}
	if (level == 33)
	{
		text = "If you become light - headed from thirst, feel free to pass out.";
	}
	if (level == 41)
	{
		text = "Here come the test results: You are a horrible person. I'm serious, that's what it says: A horrible person.";
	}
	if (level == 42)
	{
		text = "Did you know that people with guilty consciences are more easily startled by loud noise--[train horn]--";
	}
	if (level == 43)
	{
		text = "I think that one was about to say 'I love you.' They ARE sentient, of course. We just have a LOT of them.";
	}
	if (level == 51)
	{
		text = "When you die, I'm going to laminate your skeleton and pose you in the lobby.";
	}
	if (level == 52)
	{
		text = "Enjoy this next test. I'm going to go to the surface. It's a beautiful day out.";
	}
	if (level == 0)
	{
		text = "OMG GGWP EZPZ NOOB SCRUBS!";
	}

	return text;
}