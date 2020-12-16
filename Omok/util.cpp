#include "util.h"

#include <Windows.h>

void util::go_to_xy( int x, int y )
{
	COORD cur;
	cur.X = x;
	cur.Y = y;
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), cur );
}