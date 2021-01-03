#include "board.h"

#include <iostream>
#include <iomanip>
#include "util.h"
#include "player.h"

using namespace std;

board::board()
{
	black_stone = "O "; //"○";
	white_stone = "X "; //"●";
}

void board::init_board()
{
	system("cls");
	for (int i = 1; i <= BOARD_SIZE; i++)
	{
		for (int j = 1; j <= BOARD_SIZE; j++)
		{
			map[i][j] = 0; // 바둑판 초기화
			draw_board(i, j); // 바둑판 그리기
		}
	}
}

void board::draw_board(int x, int y)
{
	cout << setw(2) << get_board_char(x, y);
	if (y == BOARD_SIZE)
	{
		cout << endl;
	}
}

string board::get_board_char(int x, int y)
{
	if (x == 1)
	{
		if (y == 1)
		{
			return "┌ ";
		}
		if (y != BOARD_SIZE)
		{
			return "┬ ";
		}
		if (y == BOARD_SIZE)
		{
			return "┐ ";
		}
	}
	else if (x == BOARD_SIZE)
	{
		if (y == 1)
		{
			return "└ ";
		}
		if (y != BOARD_SIZE)
		{
			return "┴ ";
		}
		if (y == BOARD_SIZE)
		{
			return "┘ ";
		}
	}
	else if (x != BOARD_SIZE)
	{
		if (y == 1)
		{
			return "├ ";
		}
		if (y != BOARD_SIZE)
		{
			return "┼ ";
		}
		if (y == BOARD_SIZE)
		{
			return "┤ ";
		}
	}

	return "";
}

void board::draw_stone(int x, int y, bool is_black)
{
	go_to_xy(x, y);
	cout << setw(2) << (is_black ? black_stone : white_stone);
	map[x][y] = is_black ? black : white;
}

void board::draw_display(int count)
{
	util::go_to_xy(BOARD_SIZE * 3 / 5, BOARD_SIZE + 1);
	cout << (count % 2 ? "Black" : "White") << "\'s Turn";
	util::go_to_xy(2 * BOARD_SIZE + 2, BOARD_SIZE / 4);
	cout << "Black" << black_stone;

	util::go_to_xy(2 * BOARD_SIZE + 2, BOARD_SIZE / 2);
	cout << "vs";
	util::go_to_xy(2 * BOARD_SIZE + 2, BOARD_SIZE * 3 / 4);
	cout << "White" << white_stone;
}

void board::show_player_is_user(player** player_list, int player_num)
{
	if (player_num == 0)
	{
		util::go_to_xy(2 * BOARD_SIZE + 2, BOARD_SIZE / 4 + 1);
	}
	else if (player_num == 1)
	{
		util::go_to_xy(2 * BOARD_SIZE + 2, BOARD_SIZE * 3 / 4 + 1);
	}

	if (player_list[player_num]->is_computer == false)
	{
		cout.width(5);
		cout << "User";
	}
	else if (player_list[player_num]->is_computer == true)
	{
		cout.width(5);
		cout << "Com";
	}
}

void board::go_to_xy(int x, int y)
{
	util::go_to_xy(x * 2, y);
}
