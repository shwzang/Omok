#pragma once

#include<iostream>
#include<iomanip>
#include<list>
#include<string>
#include<conio.h>
#include<time.h>
#include<Windows.h>
#include "Node.h"

#define N 19
#define TIMELIMIT (CLOCKS_PER_SEC * 50)  // �ð� ����
#define NODELIMIT 3 // ��� ����

class Omok
{
public:
	char Map[N + 5][N + 5];  //����
	int Gibo[N * N][2]; // �⺸

	char CursorX;  // Ŀ��x
	char CursorY;  // Ŀ��y

	int Direction[4][2] = { { 1, 0 },{ 0, 1 },{ 1, 1 },{ -1, 1 } }; // ����

	int Count = 2; //��

	char OppositeStoneNumber;  //�ٸ� �� �� ��
	char EmptyStoneNumber;    //�� �� ��
	char Winner = 0;

	clock_t StartTime, EndTime, SearchEndTime;

	int Player[3];  // �÷��̾� user or com

public:
	void OneTwo();
	void Init();
	void Play();
	void DrawBoard(int x, int y);
	void Display();
	void Move();
	void GoToXY(int x, int y);
	void DrawStone(int x, int y);
	void SelectPlayer();
	void ShowPlayer(int num);
	int CheckWinner(int player);
	void FinishGame();
	void Timer();

	int Evaluate();
	int MaxValue(Node& state, int alpha, int beta);
	int MinValue(Node& state, int alpha, int beta);
	int ABSearch();
};