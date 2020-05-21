#include "Board.h"

void Board::InitBoard()
{
	system( "cls" );
	for ( int i = 1; i <= N; i++ )
	{
		for ( int j = 1; j <= N; j++ )
		{
			Map[i][j] = 0;			// 바둑판 초기화
			DrawBoard( i, j );		// 바둑판 그리기
		}
	}
}

void Board::DrawBoard( int x, int y )
{
	if ( x == 1 )
	{
		if ( y == 1 )
		{
			cout << setw( 2 ) << "┌ ";
		}
		else if ( y != N )
		{
			cout << setw( 2 ) << "┬ ";
		}
		else if ( y == N )
		{
			cout << setw( 2 ) << "┐ " << endl;
		}
	}
	else if ( x == N )
	{
		if ( y == 1 )
		{
			cout << setw( 2 ) << "└ ";
		}
		else if ( y != N )
		{
			cout << setw( 2 ) << "┴ ";
		}
		else if ( y == N )
		{
			cout << setw( 2 ) << "┘ " << endl;
		}
	}
	else if ( x != N )
	{
		if ( y == 1 )
		{
			cout << setw( 2 ) << "├ ";
		}
		else if ( y != N )
		{
			cout << setw( 2 ) << "┼ ";
		}
		else if ( y == N )
		{
			cout << setw( 2 ) << "┤ " << endl;
		}
	}
}

void Board::DrawStone( int x, int y, bool IsBlack )
{
	cout << ( IsBlack ? "○" : "●" );
	Map[x][y] = IsBlack ? 1 : -1;
}

void Board::GoToXY( int x, int y )
{
	Util::GoToXY( x, y );
}
