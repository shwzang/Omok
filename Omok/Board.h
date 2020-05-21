#pragma once
#include "Omok.h"
#include "Util.h"

class Board
{
public:
	// 바둑판
	char Map[N + 5][N + 5];

public:

	void InitBoard();

	// x, y 좌표에 해당하는 바둑판을 그리는 함수
	void DrawBoard( int x, int y );

	// x, y 좌표에 돌을 그리는 함수
	void DrawStone( int x, int y, bool IsBlack);


	// 해당 위치로 이동
	void GoToXY( int x, int y );
};
