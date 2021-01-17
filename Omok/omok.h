#pragma once

#include <Windows.h>
#include <time.h>
#include <vector>

#define BOARD_SIZE 19
#define TIME_LIMIT (CLOCKS_PER_SEC * 20)  // 시간 제한
#define NODE_LIMIT 3 // 노드 제한

using namespace std;

class omok
{
public:
	class player* player_list[2]; // Player 2명 리스트
	class board* game_board;

	vector<class stone*> game_record; // 기보

	char cursor_x; // 커서x
	char cursor_y; // 커서y

	int direction[4][2] = {{1, 0}, {0, 1}, {1, 1}, {-1, 1}}; // 방향

	int count; // 수
	int winner;

	char opposite_stone_number; //다른 색 돌 수
	char empty_stone_number; //빈 돌 수

	clock_t start_time, end_time, search_end_time;

public:
	void one_two();
	void init();
	void play();
	void move_by_key_input();
	void go_to_xy(int x, int y);
	void draw_stone(int x, int y);
	void select_player_is_user(int player_num);
	int determine_winner();
	void finish_game();


	int evaluate();
	int max_value(class node& state, int alpha, int beta);
	int min_value(node& state, int alpha, int beta);
	class stone* ab_search();

private:
	void timer();
};
