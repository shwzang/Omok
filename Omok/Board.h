#pragma once
#include "Omok.h"
#include "Util.h"

class Board
{
public:
	// �ٵ���
	char Map[N + 5][N + 5];

public:

	void InitBoard();

	// x, y ��ǥ�� �ش��ϴ� �ٵ����� �׸��� �Լ�
	void DrawBoard( int x, int y );

	// x, y ��ǥ�� ���� �׸��� �Լ�
	void DrawStone( int x, int y, bool IsBlack);


	// �ش� ��ġ�� �̵�
	void GoToXY( int x, int y );
};
