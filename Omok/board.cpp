#include "board.h"

#include <iostream>
#include <iomanip>
#include "util.h"

using namespace std;

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
	cout << setw(2) << (is_black ? "○" : "●");
	map[x][y] = is_black ? black : white;
}

void board::go_to_xy(int x, int y)
{
	util::go_to_xy(x * 2, y);
}
