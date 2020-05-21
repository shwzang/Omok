#pragma once

#include<vector>

using namespace std;

class Player
{
public:
	Player();
	Player( bool IsComputer );

public:
	// 해당 플레이어가 컴퓨터인지 True 면 컴퓨터
	bool IsComputer;
};
