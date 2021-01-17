#pragma once

#include <string>

#include "omok.h"

using namespace std;

class board
{
public:
	board();

public:
	static const int black = 1;
	static const int white = -1;
	static const int none = 0;

	string black_stone;
	string white_stone;


	// 바둑판
	int map[BOARD_SIZE + 5][BOARD_SIZE + 5] = {0};

public:
	// 바둑판 초기화 함수
	void init_board();

	// x, y 좌표에 해당하는 바둑판을 그리는 함수
	void draw_board(int x, int y);

	// 바둑판 위치에 맞는 문자를 반환
	string get_board_char(int x, int y);

	// x, y 좌표에 돌을 그리는 함수
	void draw_stone(int x, int y, bool is_black);

	// 전광판을 화면에 표시
	void draw_display(int count);

	// 플레이어의 
	void show_player_is_user(vector<player*> player_list, int player_num);

	// 해당 위치로 이동
	void go_to_xy(int x, int y);
};
