#include "Util.h"

void Util::GoToXY( int x, int y )
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), Cur );
}
