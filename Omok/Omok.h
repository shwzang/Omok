#pragma once

#include<conio.h>
#include<iostream>
#include<iomanip>
#include<list>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<time.h>
#include "Player.h"
#include "Node.h"
#include "Util.h"

#define N 19
#define TIMELIMIT (CLOCKS_PER_SEC * 20)  // �ð� ����
#define NODELIMIT 3 // ��� ����

class Omok
{
public:
	Player* PlayerList[2];	// Player 2�� ����Ʈ
	class Board* GameBoard;

	int Gibo[N * N][2]; // �⺸

	char CursorX;  // Ŀ��x
	char CursorY;  // Ŀ��y

	int Direction[4][2] = { { 1, 0 },{ 0, 1 },{ 1, 1 },{ -1, 1 } }; // ����

	int Count = 2; //��

	char OppositeStoneNumber;  //�ٸ� �� �� ��
	char EmptyStoneNumber;    //�� �� ��
	char Winner = 0;

	clock_t StartTime, EndTime, SearchEndTime;

public:
	void OneTwo();
	void Init();
	void Play();
	void Display();
	void Move();
	void GoToXY( int x, int y );
	void DrawStone( int x, int y );
	void SelectPlayer();
	void ShowPlayer( int num );
	int CheckWinner( int player );
	void FinishGame();
	void Timer();

	int Evaluate();
	int MaxValue( Node& state, int alpha, int beta );
	int MinValue( Node& state, int alpha, int beta );
	int ABSearch();
};
