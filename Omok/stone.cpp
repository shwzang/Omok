#include "stone.h"

stone::stone()
{
	x = -1;
	y = -1;
}

stone::stone(int x, int y)
{
	stone();

	this->x = x;
	this->y = y;
}
