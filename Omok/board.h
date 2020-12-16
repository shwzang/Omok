#pragma once

#include "omok.h"

class board
{
public:
	// 바둑판
	char map[N + 5][N + 5];

public:

	void init_board();

	// x, y 좌표에 해당하는 바둑판을 그리는 함수
	void draw_board(int x, int y);

	// x, y 좌표에 돌을 그리는 함수
	void draw_stone(int x, int y, bool is_black);

	// 해당 위치로 이동
	void go_to_xy(int x, int y);
};
