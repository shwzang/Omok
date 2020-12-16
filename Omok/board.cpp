#include "board.h"

#include <iostream>
#include <iomanip>
#include "util.h"

using namespace std;

void board::init_board()
{
	system("cls");
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			map[i][j] = 0; // 바둑판 초기화
			draw_board(i, j); // 바둑판 그리기
		}
	}
}

void board::draw_board(int x, int y)
{
	if (x == 1)
	{
		if (y == 1)
		{
			cout << setw(2) << "┌ ";
		}
		else if (y != N)
		{
			cout << setw(2) << "┬ ";
		}
		else if (y == N)
		{
			cout << setw(2) << "┐ " << endl;
		}
	}
	else if (x == N)
	{
		if (y == 1)
		{
			cout << setw(2) << "└ ";
		}
		else if (y != N)
		{
			cout << setw(2) << "┴ ";
		}
		else if (y == N)
		{
			cout << setw(2) << "┘ " << endl;
		}
	}
	else if (x != N)
	{
		if (y == 1)
		{
			cout << setw(2) << "├ ";
		}
		else if (y != N)
		{
			cout << setw(2) << "┼ ";
		}
		else if (y == N)
		{
			cout << setw(2) << "┤ " << endl;
		}
	}
}

void board::draw_stone(int x, int y, bool is_black)
{
	cout << (is_black ? "○" : "●");
	map[x][y] = is_black ? 1 : -1;
}

void board::go_to_xy(int x, int y)
{
	util::go_to_xy(x, y);
}
