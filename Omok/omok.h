#pragma once

#include <Windows.h>
#include <time.h>

#define N 19
#define TIME_LIMIT (CLOCKS_PER_SEC * 20)  // 시간 제한
#define NODE_LIMIT 3 // 노드 제한

class omok
{
public:
	class player* player_list[2]; // Player 2명 리스트
	class board* game_board;

	int gibo[N * N][2]; // 기보

	char cursor_x; // 커서x
	char cursor_y; // 커서y

	int direction[4][2] = {{1, 0}, {0, 1}, {1, 1}, {-1, 1}}; // 방향

	int count = 2; //수

	char opposite_stone_number; //다른 색 돌 수
	char empty_stone_number; //빈 돌 수
	char winner = 0;

	clock_t start_time, end_time, search_end_time;

public:
	void one_two();
	void init();
	void play();
	void display();
	void move();
	void go_to_xy(int x, int y);
	void draw_stone(int x, int y);
	void select_player();
	void show_player(int num);
	int check_winner(int player);
	void finish_game();
	void timer();

	int evaluate();
	int max_value(class node& state, int alpha, int beta);
	int min_value(node& state, int alpha, int beta);
	int ab_search();
};
