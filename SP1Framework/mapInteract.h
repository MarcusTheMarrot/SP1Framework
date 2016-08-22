#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

COORD teleportation(string str, int x, int y);
bool dooring(COORD lever1, COORD lever2, int x1, int y1, int x2, int y2);
