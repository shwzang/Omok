#include "omok.h"

#include <algorithm>
#include <conio.h>
#include <iostream>

#include "board.h"
#include "node.h"
#include "player.h"
#include "util.h"

using namespace std;

class player;
class board;

int main()
{
	omok* game_instance = new omok();
	board* game_board = new board();
	game_instance->game_board = game_board;

	game_instance->init(); //초기화
	game_instance->play();

	game_instance->move();
}

void omok::init()
{
	if (game_board != nullptr)
	{
		game_board->init_board();
	}

	for (int i = 0; i < N * N; i++)
	{
		// 기보 초기화
		gibo[i][0] = 0;
		gibo[i][1] = 0;
	}

	player_list[0] = new player(false);
	player_list[1] = new player(false);

	cursor_x = N / 2;
	cursor_y = N / 2;

	count = 1;

	display(); //전광판 그리기
	select_player(); // 1p, 2p 사용자 또는 컴퓨터 선택

	go_to_xy(cursor_x * 2, cursor_y);
}

void omok::play()
{
	winner = 0;

	do
	{
		int tmp = 0;
		display();
		if (player_list[(count - 1) % 2]->is_computer == false)
		{
			move();
		} // 플레이어가 유저면 돌 옮기기
		else if (player_list[(count - 1) % 2]->is_computer == true)
		{
			timer();
			if (count >= 3)
			{
				tmp = ab_search();
			}
			cursor_x = tmp / 100;
			cursor_y = tmp % 100;
			one_two();

			draw_stone(cursor_x, cursor_y);
		} // 플레이어가 컴퓨터면 계산하기
		if (winner == 0)
		{
			winner = check_winner(count % 2);
		}

		go_to_xy(N + 1, N + 5);
		cout << count;
		go_to_xy(cursor_x * 2, cursor_y);
	} while (winner == 0);

	finish_game();
}

void omok::move()
{
	int c = count;
	start_time = clock();
	do
	{
		timer();
		int a = _getch();
		timer();

		if (a == 224) // 입력이 방향키 면
		{
			a = _getch();
			if ((a == 72) && (cursor_y > 0))
			{
				cursor_y--;
			}
			else if ((a == 80) && (cursor_y < N - 1))
			{
				cursor_y++;
			}
			else if ((a == 75) && (cursor_x > 0))
			{
				cursor_x--;
			}
			else if ((a == 77) && (cursor_x < N - 1))
			{
				cursor_x++;
			}
		}
		else if (((a == 119) || (a == 87)) && (cursor_y > 0)) // 입력이 wasd 면
		{
			cursor_y--;
		}
		else if (((a == 115) || (a == 83)) && (cursor_y < N - 1))
		{
			cursor_y++;
		}
		else if (((a == 97) || (a == 65)) && (cursor_x > 0))
		{
			cursor_x--;
		}
		else if (((a == 100) || (a == 69)) && (cursor_x < N - 1))
		{
			cursor_x++;
		}

		// 입력이 스페이스바 또는 엔터면
		if ((a == 32) || (a == 13))
		{
			go_to_xy(cursor_x * 2, cursor_y);
			one_two();
			draw_stone(cursor_x, cursor_y); // 돌 놓기
		}
		go_to_xy(cursor_x * 2, cursor_y);
	} while ((c == count) && (winner == 0));
}

void omok::go_to_xy(int x, int y)
{
	util::go_to_xy(x, y);
} // 커서 이동

void omok::draw_stone(int x, int y)
{
	if (game_board->map[x][y] == 0)
	{
		game_board->draw_stone(x, y, (count % 2));
		gibo[count][0] = x;
		gibo[count][1] = y;
		count++;
	}
	else
	{
		go_to_xy(N, N);
		cout << "Already Laid\a";
		Sleep(2000);
		go_to_xy(N, N);
		cout << "            ";
		go_to_xy(cursor_x * 2, cursor_y);
	}
}

void omok::one_two()
{
	if (count == 1)
	{
		cursor_x = N / 2;
		cursor_y = N / 2;
	}
	else if (count == 2)
	{
		if ((cursor_x > 10) || (cursor_x < 8) || (cursor_x > 10) || (cursor_x < 8))
		{
			cursor_x = N / 2;
			cursor_y = N / 2;
			srand((unsigned)time(NULL));
			do
			{
				cursor_x = cursor_x + rand() % 3 - 1;
				cursor_y = cursor_y + rand() % 3 - 1;
			} while ((cursor_x == N / 2) && (cursor_y == N / 2));
		}
	}
	go_to_xy(cursor_x * 2, cursor_y);
}

void omok::display()
{
	go_to_xy(N * 3 / 5, N + 1);
	cout << (count % 2 ? "Black" : "White") << "\'s Turn";
	go_to_xy(2 * N + 2, N / 4);
	cout << "Black○";

	go_to_xy(2 * N + 2, N / 2);
	cout << "vs";
	go_to_xy(2 * N + 2, N * 3 / 4);
	cout << "White●";

	show_player(0);
	show_player(1);
}

void omok::select_player()
{
	for (int i = 0; i < 2; i++)
	{
		int sel = 0;
		show_player(i);
		do
		{
			int a = _getch();

			if (a == 224) // 입력이 방향키 면
			{
				a = _getch();
				if ((a == 75) || (a == 77))
				{
					player_list[i]->is_computer = !player_list[i]->is_computer;
					show_player(i);
				}
			}

			else if (((a == 97) || (a == 65)) || ((a == 100) || (a == 69)))
			{
				player_list[i]->is_computer = !player_list[i]->is_computer;
				show_player(i);
			} // 입력이 ad 면

			if ((a == 32) || (a == 13))
			{
				// 입력이 스페이스바 또는 엔터면
				sel = 1;
			}
		} while (sel == 0);
	}
} // 플레이어 선택하기
void omok::show_player(int num)
{
	if (num == 0)
	{
		go_to_xy(2 * N + 2, N / 4 + 1);
	}
	else if (num == 1)
	{
		go_to_xy(2 * N + 2, N * 3 / 4 + 1);
	}

	if (player_list[num]->is_computer == false)
	{
		cout.width(5);
		cout << "User";
	}
	else if (player_list[num]->is_computer == true)
	{
		cout.width(5);
		cout << "Com";
	}
} // 플레이어 보여주기

int omok::check_winner(int player)
{
	winner = 0;

	for (int i = 0; i <= count; i++)
	{
		if (player == (count % 2))
		{
			for (int j = 0; j < 4; j++)
			{
				char sum = 0;
				char x = gibo[i][0];
				char y = gibo[i][1];
				for (int k = 0; k <= 4; k++)
				{
					if (game_board->map[x][y] == game_board->map[x + (direction[j][0] * k)][y + (direction[j][1] * k)])
					{
						sum += game_board->map[x + direction[j][0] * k][y + direction[j][1] * k];
					}
				}
				if (abs(sum) == 5)
				{
					winner = sum * 200;
				}
			}
		}
	}
	return winner;
}

void omok::finish_game()
{
	if (winner >= 10 || winner <= -10)
	{
		go_to_xy(N + 2, N);
		cout << "player" << (winner < 0 ? 1 : 2) << " win\a";
		Sleep(2000);
		go_to_xy(cursor_x * 2, cursor_y);
	}
}

int omok::evaluate()
{
	int eval = 0;

	for (int i = 1; i <= count; i++)
	{
		// 모든 수
		int onestone = 0;
		for (char j = 0; j < 4; j++)
		{
			int read = 0;
			// 4방향
			for (char k = 5; k >= 2; k--)
			{
				// 4,3,2,1,0
				opposite_stone_number = 0; //다른 색 돌 수
				empty_stone_number = 0; //빈 돌 수
				char sum = 0;
				int mid = 0;

				int x = gibo[i][0];
				int y = gibo[i][1];

				for (char l = 0; l < k; l++)
				{
					if (game_board->map[x][y] == game_board->map[x + (direction[j][0] * l)][y + (direction[j][1] * l)])
					{
						sum += game_board->map[x][y];
					}
					else if ((game_board->map[x + (direction[j][0] * l)][y + (direction[j][1] * l)] == 0) && (l != k - 1
					))
					{
						mid++;
					}
				}
				if (-1 * (game_board->map[x][y]) == game_board->map[x + (direction[j][0] * k)][y + (direction[j][1] * k)
				])
				{
					opposite_stone_number++;
				}
				if (-1 * (game_board->map[x][y]) == game_board->map[x - (direction[j][0])][y - (direction[j][1])])
				{
					opposite_stone_number++;
				}
				if (0 == game_board->map[x + (direction[j][0] * k)][y + (direction[j][1] * k)])
				{
					empty_stone_number++;
				}
				if (0 == game_board->map[x - (direction[j][0])][y - (direction[j][1])])
				{
					empty_stone_number++;
				}

				if (read == 0)
				{
					int sign = 0;
					if (sum != 0)
					{
						sign = sum / abs(sum);
					}

					if (abs(sum) == 5)
					{
						eval = eval + sign * 1000;
						read++;
					}
					else if (abs(sum) == 1)
					{
					}
					else if (abs(sum) == k)
					{
						if (empty_stone_number == 2)
						{
							eval = eval + sign * (k * k + 1);
							if (abs(sum) == 4)
							{
								eval = eval + sign * 2 * (k * k + 1);
							}
							read++;
						}
						else if ((empty_stone_number == 1) && (opposite_stone_number == 1))
						{
							eval = eval + sign * (k * k + 2) / 2;
							read++;
						}
					}
					else if ((abs(sum) == k - 1) && (mid == 1))
					{
						if (empty_stone_number == 2)
						{
							eval = eval + sign * (k - 1) * (k - 1);
							read++;
						}
						else if ((empty_stone_number == 1) && (opposite_stone_number == 1))
						{
							eval = eval + sign * (k - 1) * (k - 1) / 2;
							read++;
						}
					}
				}
			}
		}
	}
	return eval;
}

int omok::ab_search()
{
	node state;

	start_time = clock();
	if ((count % 2) == 1)
	{
		state.value = max_value(state, -10000, 10000);
	}
	else if ((count % 2) == 0)
	{
		state.value = min_value(state, -10000, 10000);
	}

	return state.position;
}

int omok::max_value(node& state, int alpha, int beta)
{
	search_end_time = clock();
	if (search_end_time - end_time >= CLOCKS_PER_SEC)
		timer();
	node child;
	child.value = -10000;
	child.parent = &state;
	child.height = child.parent->height + 1;
	if (((double)(end_time - start_time) >= (TIME_LIMIT - 3 * CLOCKS_PER_SEC)) || (child.height >= NODE_LIMIT))
	{
		return evaluate();
	}
	else
	{
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				if (game_board->map[i][j] == 0)
				{
					game_board->map[i][j] = (count % 2) ? 1 : -1;
					gibo[count][0] = i;
					gibo[count][1] = j;
					count++;
					int temp = min_value(child, alpha, beta);
					game_board->map[i][j] = 0;
					gibo[count][0] = 0;
					gibo[count][1] = 0;
					count--;
					if (child.value < temp)
					{
						child.value = temp;
						child.position = 100 * i + j;
					}
					if (child.value >= beta)
					{
						return child.value;
					}
					alpha = max(alpha, child.value);
				}
			}
		}
	}
	child.parent->position = child.position;
	return child.value;
}

int omok::min_value(node& state, int alpha, int beta)
{
	search_end_time = clock();
	if (search_end_time - end_time >= CLOCKS_PER_SEC)
	{
		timer();
	}

	node child;
	child.value = 10000;
	child.parent = &state;
	child.height = child.parent->height + 1;
	if (static_cast<double>(end_time - start_time) >= TIME_LIMIT - 3 * CLOCKS_PER_SEC || child.height >= NODE_LIMIT)
	{
		return evaluate();
	}
	else
	{
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				if (game_board->map[i][j] == 0)
				{
					game_board->map[i][j] = (count % 2) ? 1 : -1;
					gibo[count][0] = i;
					gibo[count][1] = j;
					count++;
					int temp = max_value(child, alpha, beta);
					game_board->map[i][j] = 0;
					gibo[count][0] = 0;
					gibo[count][1] = 0;
					count--;
					if (child.value > temp)
					{
						child.value = temp;
						child.position = 100 * i + j;
					}
					if (child.value <= alpha)
					{
						return child.value;
					}
					beta = min(beta, child.value);
				}
			}
		}
	}
	child.parent->position = child.position;
	return child.value;
}

void omok::timer()
{
	end_time = clock();
	go_to_xy(3, N);
	cout << "TIMER :";
	cout.width(5);
	cout << (TIME_LIMIT - (end_time - start_time)) / CLOCKS_PER_SEC << "s";
	go_to_xy(cursor_x * 2, cursor_y);

	if (TIME_LIMIT < (end_time - start_time))
	{
		go_to_xy(3, N);
		cout << "TIME OUT";
		if (count % 2 == 1)
		{
			winner = -1000;
		}
		else if (count % 2 == 0)
		{
			winner = +1000;
		}
	}
}
