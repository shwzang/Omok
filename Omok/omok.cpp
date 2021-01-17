#include "omok.h"

#include <conio.h>
#include <iostream>

#include "board.h"
#include "node.h"
#include "player.h"
#include "stone.h"
#include "util.h"

using namespace std;

int main()
{
	omok* game_instance = new omok();
	game_instance->game_board = new board();

	game_instance->init(); //초기화
	game_instance->play();

	game_instance->move_by_key_input();
}

void omok::init()
{
	if (game_board != nullptr)
	{
		game_board->init_board();
	}

	player* player_a = new player(false);
	player* player_b = new player(false);
	player_list.push_back(player_a);
	player_list.push_back(player_b);

	cursor_x = BOARD_SIZE / 2;
	cursor_y = BOARD_SIZE / 2;

	count = 1;

	//전광판 그리기
	game_board->draw_display(count);

	// 1p, 2p 사용자 또는 컴퓨터 선택
	select_player_is_user(0);
	select_player_is_user(1);

	go_to_xy(cursor_x * 2, cursor_y);
}

void omok::play()
{
	winner = 0;

	do
	{
		stone* cursor = new stone();
		game_board->draw_display(count);

		// 플레이어가 유저면 
		if (player_list[(count - 1) % 2]->is_computer == false)
		{
			move_by_key_input();
		}
		else
		{
			timer();
			if (count >= 3)
			{
				cursor = ab_search();
			}

			cursor_x = cursor->x;
			cursor_y = cursor->y;
			one_two();


			draw_stone(cursor_x, cursor_y);
		}

		// 플레이어가 컴퓨터면 계산하기
		if (winner == 0)
		{
			winner = determine_winner();
		}

		go_to_xy(BOARD_SIZE + 1, BOARD_SIZE + 5);
		cout << count;
		go_to_xy(cursor_x * 2, cursor_y);
	} while (winner == 0);

	finish_game();
}

void omok::move_by_key_input()
{
	int c = count;
	start_time = clock();
	do
	{
		timer();
		int input_key = _getch();
		timer();

		// 입력이 방향키인 경우
		if (input_key == 224)
		{
			input_key = _getch();

			// 방향키 위키 입력
			if ((input_key == 72) && (cursor_y > 0))
			{
				cursor_y--;
			}
				// 방향키 아래키 입력
			else if ((input_key == 80) && (cursor_y < BOARD_SIZE - 1))
			{
				cursor_y++;
			}
				// 방향키 왼쪽키 입력
			else if ((input_key == 75) && (cursor_x > 0))
			{
				cursor_x--;
			}
				// 방향키 오른쪽키 입력
			else if ((input_key == 77) && (cursor_x < BOARD_SIZE - 1))
			{
				cursor_x++;
			}
		}
			// w 키 입력
		else if (((input_key == 119) || (input_key == 87)) && (cursor_y > 0)) // 입력이 wasd 면
		{
			cursor_y--;
		}
			// s 키 입력
		else if (((input_key == 115) || (input_key == 83)) && (cursor_y < BOARD_SIZE - 1))
		{
			cursor_y++;
		}
			// a 키 입력
		else if (((input_key == 97) || (input_key == 65)) && (cursor_x > 0))
		{
			cursor_x--;
		}
			// b 키 입력
		else if (((input_key == 100) || (input_key == 69)) && (cursor_x < BOARD_SIZE - 1))
		{
			cursor_x++;
		}

		// 입력이 스페이스바 또는 엔터면
		if ((input_key == 32) || (input_key == 13))
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
		game_record.push_back(new stone(x, y));
		count++;
	}
	else
	{
		go_to_xy(BOARD_SIZE, BOARD_SIZE);
		cout << "Already Laid\a";

		Sleep(1000);

		go_to_xy(BOARD_SIZE, BOARD_SIZE);
		cout << "            ";

		go_to_xy(cursor_x * 2, cursor_y);
	}
}

void omok::select_player_is_user(int player_num)
{
	bool has_selected = false;
	game_board->show_player_is_user(player_list, player_num);
	do
	{
		int a = _getch();

		if (a == 224) // 입력이 방향키 면
		{
			a = _getch();
			if ((a == 75) || (a == 77))
			{
				player_list[player_num]->is_computer = !player_list[player_num]->is_computer;
				game_board->show_player_is_user(player_list, player_num);
			}
		}

		else if (((a == 97) || (a == 65)) || ((a == 100) || (a == 69)))
		{
			player_list[player_num]->is_computer = !player_list[player_num]->is_computer;
			game_board->show_player_is_user(player_list, player_num);
		} // 입력이 ad 면

		if ((a == 32) || (a == 13))
		{
			// 입력이 스페이스바 또는 엔터면
			has_selected = true;
		}
	} while (has_selected == false);
}

void omok::one_two()
{
	if (count == 1)
	{
		cursor_x = BOARD_SIZE / 2;
		cursor_y = BOARD_SIZE / 2;
	}
	else if (count == 2)
	{
		if ((cursor_x > 10) || (cursor_x < 8) || (cursor_x > 10) || (cursor_x < 8))
		{
			cursor_x = BOARD_SIZE / 2;
			cursor_y = BOARD_SIZE / 2;
			srand(static_cast<unsigned>(time(nullptr)));
			do
			{
				cursor_x = cursor_x + rand() % 3 - 1;
				cursor_y = cursor_y + rand() % 3 - 1;
			} while ((cursor_x == BOARD_SIZE / 2) && (cursor_y == BOARD_SIZE / 2));
		}
	}
	go_to_xy(cursor_x * 2, cursor_y);
}

int omok::determine_winner()
{
	winner = 0;

	for (int i = 0; i < game_record.size(); i++)
	{
		int x = game_record.at(i)->x;
		int y = game_record.at(i)->y;

		for (int j = 0; j < 4; j++)
		{
			char sum = 0;

			for (int k = 0; k <= 4; k++)
			{
				if (x + (direction[j][0] * k) > BOARD_SIZE || y + (direction[j][1] * k) > BOARD_SIZE)
				{
					break;
				}

				if (game_board->map[x][y] == game_board->map[x + (direction[j][0] * k)][y + (direction[j][1] * k)])
				{
					sum += game_board->map[x + direction[j][0] * k][y + direction[j][1] * k];
				}
			}

			if (abs(sum) == 5)
			{
				winner = sum * 200;
				break;
			}
		}
	}
	return winner;
}

void omok::finish_game()
{
	if (winner >= 10 || winner <= -10)
	{
		go_to_xy(BOARD_SIZE + 2, BOARD_SIZE);
		cout << "player" << (winner < 0 ? 1 : 2) << " win\a";

		Sleep(2000);

		go_to_xy(cursor_x * 2, cursor_y);
	}
}


void omok::timer()
{
	end_time = clock();
	go_to_xy(3, BOARD_SIZE);
	cout << "TIMER :";
	cout.width(5);
	cout << (TIME_LIMIT - (end_time - start_time)) / CLOCKS_PER_SEC << "s";
	go_to_xy(cursor_x * 2, cursor_y);

	if (TIME_LIMIT < (end_time - start_time))
	{
		go_to_xy(3, BOARD_SIZE);
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


int omok::evaluate()
{
	int eval = 0;

	for (int i = 1; i < game_record.size(); i++)
	{
		int x = game_record.at(i)->x;
		int y = game_record.at(i)->y;

		// 모든 수
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

				for (char l = 0; l < k; l++)
				{
					if (game_board->map[x][y] == game_board->map[x + (direction[j][0] * l)][y + (direction[j][1] * l
					)])
					{
						sum += game_board->map[x][y];
					}
					else if ((game_board->map[x + (direction[j][0] * l)][y + (direction[j][1] * l)] == 0) && (l != k
						- 1
					))
					{
						mid++;
					}
				}
				if (-1 * (game_board->map[x][y]) == game_board->map[x + (direction[j][0] * k)][y + (direction[j][1]
						* k)
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

stone* omok::ab_search()
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
	{
		timer();
	}

	node child;
	child.value = -10000;
	child.parent = &state;
	child.height = child.parent->height + 1;
	if (static_cast<double>(end_time - start_time) >= TIME_LIMIT - 3 * CLOCKS_PER_SEC || child.height >= NODE_LIMIT)
	{
		return evaluate();
	}
	for (int i = 1; i <= BOARD_SIZE; i++)
	{
		for (int j = 1; j <= BOARD_SIZE; j++)
		{
			if (game_board->map[i][j] == 0)
			{
				game_board->map[i][j] = (count % 2) ? 1 : -1;
				game_record.push_back(new stone(i, j));
				count++;

				int temp = min_value(child, alpha, beta);

				game_board->map[i][j] = 0;
				game_record.pop_back();
				count--;

				if (child.value < temp)
				{
					child.value = temp;
					child.position = new stone(i, j);
				}
				if (child.value >= beta)
				{
					return child.value;
				}
				alpha = max(alpha, child.value);
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
	for (int i = 1; i <= BOARD_SIZE; i++)
	{
		for (int j = 1; j <= BOARD_SIZE; j++)
		{
			if (game_board->map[i][j] == 0)
			{
				game_board->map[i][j] = (count % 2) ? 1 : -1;
				game_record.push_back(new stone(i, j));
				count++;

				int temp = max_value(child, alpha, beta);

				game_board->map[i][j] = 0;
				game_record.pop_back();
				count--;

				if (child.value > temp)
				{
					child.value = temp;
					child.position = new stone(i, j);
				}
				if (child.value <= alpha)
				{
					return child.value;
				}
				beta = min(beta, child.value);
			}
		}
	}
	child.parent->position = child.position;
	return child.value;
}
