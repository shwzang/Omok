#include "Omok.h"
#include "Board.h"

using namespace std;

class Omok;
class Player;
class Board;

int main()
{
	Omok* GameInstance = new Omok();
	Board* GameBoard = new Board();
	GameInstance->GameBoard = GameBoard;

	GameInstance->Init(); //초기화
	GameInstance->Play();

	GameInstance->Move();
}

void Omok::Init()
{
	if ( GameBoard != nullptr )
	{
		GameBoard->InitBoard();
	}

	for ( int i = 0; i < N * N; i++ )
	{	// 기보 초기화
		Gibo[i][0] = 0;
		Gibo[i][1] = 0;
	}

	PlayerList[0] = new Player( false );
	PlayerList[1] = new Player( false );

	CursorX = N / 2;
	CursorY = N / 2;

	Count = 1;

	Display(); //전광판 그리기
	SelectPlayer(); // 1p, 2p 사용자 또는 컴퓨터 선택

	GoToXY( CursorX * 2, CursorY );
}
void Omok::Play()
{
	Winner = 0;

	do
	{
		int tmp = 0;
		Display();
		if ( PlayerList[( Count - 1 ) % 2]->IsComputer == false )
		{
			Move();
		} // 플레이어가 유저면 돌 옮기기
		else if ( PlayerList[( Count - 1 ) % 2]->IsComputer == true )
		{
			Timer();
			if ( Count >= 3 )
			{
				tmp = ABSearch();
			}
			CursorX = tmp / 100;
			CursorY = tmp % 100;
			OneTwo();

			DrawStone( CursorX, CursorY );
		} // 플레이어가 컴퓨터면 계산하기
		if ( Winner == 0 )
		{
			Winner = CheckWinner( Count % 2 );
		}

		GoToXY( N + 1, N + 5 );
		cout << Count;
		GoToXY( CursorX * 2, CursorY );
	} while ( Winner == 0 );

	FinishGame();
}

void Omok::Move()
{
	int c = Count;
	StartTime = clock();
	do
	{
		Timer();
		int a = _getch();
		Timer();

		if ( a == 224 )  // 입력이 방향키 면
		{
			a = _getch();
			if ( ( a == 72 ) && ( CursorY > 0 ) )
			{
				CursorY--;
			}
			else if ( ( a == 80 ) && ( CursorY < N - 1 ) )
			{
				CursorY++;
			}
			else if ( ( a == 75 ) && ( CursorX > 0 ) )
			{
				CursorX--;
			}
			else if ( ( a == 77 ) && ( CursorX < N - 1 ) )
			{
				CursorX++;
			}
		}
		else if ( ( ( a == 119 ) || ( a == 87 ) ) && ( CursorY > 0 ) )// 입력이 wasd 면
		{
			CursorY--;
		}
		else if ( ( ( a == 115 ) || ( a == 83 ) ) && ( CursorY < N - 1 ) )
		{
			CursorY++;
		}
		else if ( ( ( a == 97 ) || ( a == 65 ) ) && ( CursorX > 0 ) )
		{
			CursorX--;
		}
		else if ( ( ( a == 100 ) || ( a == 69 ) ) && ( CursorX < N - 1 ) )
		{
			CursorX++;
		}

		// 입력이 스페이스바 또는 엔터면
		if ( ( a == 32 ) || ( a == 13 ) )
		{
			GoToXY( CursorX * 2, CursorY );
			OneTwo();
			DrawStone( CursorX, CursorY ); // 돌 놓기
		}
		GoToXY( CursorX * 2, CursorY );
	} while ( ( c == Count ) && ( Winner == 0 ) );
}

void Omok::GoToXY( int x, int y )
{
	Util::GoToXY( x, y );
} // 커서 이동

void Omok::DrawStone( int x, int y )
{
	if ( GameBoard->Map[x][y] == 0 )
	{
		GameBoard->DrawStone( x, y, ( Count % 2 ) );
		Gibo[Count][0] = x;
		Gibo[Count][1] = y;
		Count++;
	}
	else
	{
		GoToXY( N, N );
		cout << "Already Laid\a";
		Sleep( 2000 );
		GoToXY( N, N );
		cout << "            ";
		GoToXY( CursorX * 2, CursorY );
	}
}
void Omok::OneTwo()
{
	if ( Count == 1 )
	{
		CursorX = N / 2;
		CursorY = N / 2;
	}
	else if ( Count == 2 )
	{
		if ( ( CursorX > 10 ) || ( CursorX < 8 ) || ( CursorX > 10 ) || ( CursorX < 8 ) )
		{
			CursorX = N / 2;
			CursorY = N / 2;
			srand( (unsigned) time( NULL ) );
			do
			{
				CursorX = CursorX + rand() % 3 - 1;
				CursorY = CursorY + rand() % 3 - 1;
			} while ( ( CursorX == N / 2 ) && ( CursorY == N / 2 ) );
		}
	}
	GoToXY( CursorX * 2, CursorY );
}
void Omok::Display()
{
	GoToXY( N * 3 / 5, N + 1 );
	cout << ( Count % 2 ? "Black" : "White" ) << "\'s Turn";
	GoToXY( 2 * N + 2, N / 4 );
	cout << "Black○";

	GoToXY( 2 * N + 2, N / 2 );
	cout << "vs";
	GoToXY( 2 * N + 2, N * 3 / 4 );
	cout << "White●";

	ShowPlayer( 0 );
	ShowPlayer( 1 );
}
void Omok::SelectPlayer()
{
	for ( char i = 0; i < 2; i++ )
	{
		int user = 0;
		int sel = 0;
		ShowPlayer( i );
		do
		{
			int a = _getch();

			if ( a == 224 )  // 입력이 방향키 면
			{
				a = _getch();
				if ( ( a == 75 ) || ( a == 77 ) )
				{
					PlayerList[i]->IsComputer = !PlayerList[i]->IsComputer;
					ShowPlayer( i );
				}
			}

			else if ( ( ( a == 97 ) || ( a == 65 ) ) || ( ( a == 100 ) || ( a == 69 ) ) )
			{
				PlayerList[i]->IsComputer = !PlayerList[i]->IsComputer;
				ShowPlayer( i );
			} // 입력이 ad 면

			if ( ( a == 32 ) || ( a == 13 ) )
			{   // 입력이 스페이스바 또는 엔터면
				sel = 1;
			}
		} while ( sel == 0 );
	}
} // 플레이어 선택하기
void Omok::ShowPlayer( int num )
{
	if ( num == 0 )
	{
		GoToXY( 2 * N + 2, N / 4 + 1 );
	}
	else if ( num == 1 )
	{
		GoToXY( 2 * N + 2, N * 3 / 4 + 1 );
	}

	if ( PlayerList[num]->IsComputer == false )
	{
		cout.width( 5 );
		cout << "User";
	}
	else if ( PlayerList[num]->IsComputer == true )
	{
		cout.width( 5 );
		cout << "Com";
	}
} // 플레이어 보여주기

int Omok::CheckWinner( int player )
{
	Winner = 0;

	for ( int i = 0; i <= Count; i++ )
	{
		if ( player == ( Count % 2 ) )
		{
			for ( int j = 0; j < 4; j++ )
			{
				char sum = 0;
				char x = Gibo[i][0];
				char y = Gibo[i][1];
				for ( int k = 0; k <= 4; k++ )
				{
					if ( GameBoard->Map[x][y] == GameBoard->Map[x + ( Direction[j][0] * k )][y + ( Direction[j][1] * k )] )
					{
						sum += GameBoard->Map[x + Direction[j][0] * k][y + Direction[j][1] * k];
					}
				}
				if ( abs( sum ) == 5 )
				{
					Winner = sum * 200;
				}
			}
		}
	}
	return Winner;
}
void Omok::FinishGame()
{
	if ( Winner >= 10 || Winner <= -10 )
	{
		GoToXY( N + 2, N );
		cout << "player" << ( Winner < 0 ? 1 : 2 ) << " win\a";
		Sleep( 2000 );
		GoToXY( CursorX * 2, CursorY );
	}
}

int Omok::Evaluate()
{
	int eval = 0;

	char x, y;
	for ( int i = 1; i <= Count; i++ )
	{ // 모든 수
		int onestone = 0;
		for ( char j = 0; j < 4; j++ )
		{ // 4방향
			for ( char k = 5; k >= 2; k-- )
			{ // 4,3,2,1,0
				OppositeStoneNumber = 0;  //다른 색 돌 수
				EmptyStoneNumber = 0;    //빈 돌 수
				char sum = 0;
				int mid = 0;
				int read = 0;

				x = Gibo[i][0];
				y = Gibo[i][1];

				for ( char l = 0; l < k; l++ )
				{
					if ( GameBoard->Map[x][y] == GameBoard->Map[x + ( Direction[j][0] * l )][y + ( Direction[j][1] * l )] )
					{
						sum += GameBoard->Map[x][y];
					}
					else if ( ( GameBoard->Map[x + ( Direction[j][0] * l )][y + ( Direction[j][1] * l )] == 0 ) && ( l != k - 1 ) )
					{
						mid++;
					}
				}
				if ( -1 * ( GameBoard->Map[x][y] ) == GameBoard->Map[x + ( Direction[j][0] * k )][y + ( Direction[j][1] * k )] )
				{
					OppositeStoneNumber++;
				}
				if ( -1 * ( GameBoard->Map[x][y] ) == GameBoard->Map[x - ( Direction[j][0] )][y - ( Direction[j][1] )] )
				{
					OppositeStoneNumber++;
				}
				if ( 0 == GameBoard->Map[x + ( Direction[j][0] * k )][y + ( Direction[j][1] * k )] )
				{
					EmptyStoneNumber++;
				}
				if ( 0 == GameBoard->Map[x - ( Direction[j][0] )][y - ( Direction[j][1] )] )
				{
					EmptyStoneNumber++;
				}

				if ( read == 0 )
				{
					int sign = 0;
					if ( sum != 0 )
					{
						sign = sum / abs( sum );
					}

					if ( abs( sum ) == 5 )
					{
						eval = eval + sign * 1000;
						read++;
					}
					else if ( abs( sum ) == 1 )
					{
					}
					else if ( abs( sum ) == k )
					{
						if ( EmptyStoneNumber == 2 )
						{
							eval = eval + sign * ( k * k + 1 );
							if ( abs( sum ) == 4 )
							{
								eval = eval + sign * 2 * ( k * k + 1 );
							}
							read++;
						}
						else if ( ( EmptyStoneNumber == 1 ) && ( OppositeStoneNumber == 1 ) )
						{
							eval = eval + sign * ( k * k + 2 ) / 2;
							read++;
						}
					}
					else if ( ( abs( sum ) == k - 1 ) && ( mid == 1 ) )
					{
						if ( EmptyStoneNumber == 2 )
						{
							eval = eval + sign * ( k - 1 ) * ( k - 1 );
							read++;
						}
						else if ( ( EmptyStoneNumber == 1 ) && ( OppositeStoneNumber == 1 ) )
						{
							eval = eval + sign * ( k - 1 ) * ( k - 1 ) / 2;
							read++;
						}
					}
				}
			}
		}
	}
	return eval;
}

int Omok::ABSearch()
{
	Node state;

	StartTime = clock();
	if ( ( Count % 2 ) == 1 )
	{
		state.Value = MaxValue( state, -10000, 10000 );
	}
	else if ( ( Count % 2 ) == 0 )
	{
		state.Value = MinValue( state, -10000, 10000 );
	}

	return state.Position;
}
int Omok::MaxValue( Node& state, int alpha, int beta )
{
	SearchEndTime = clock();
	if ( SearchEndTime - EndTime >= CLOCKS_PER_SEC ) Timer();
	Node child;
	child.Value = -10000;
	child.Parent = &state;
	child.Height = child.Parent->Height + 1;
	if ( ( (double) ( EndTime - StartTime ) >= ( TIMELIMIT - 3 * CLOCKS_PER_SEC ) ) || ( child.Height >= NODELIMIT ) )
	{
		return Evaluate();
	}
	else
	{
		for ( int i = 1; i <= N; i++ )
		{
			for ( int j = 1; j <= N; j++ )
			{
				if ( GameBoard->Map[i][j] == 0 )
				{
					GameBoard->Map[i][j] = ( Count % 2 ) ? 1 : -1;
					Gibo[Count][0] = i;
					Gibo[Count][1] = j;
					Count++;
					int temp = MinValue( child, alpha, beta );
					GameBoard->Map[i][j] = 0;
					Gibo[Count][0] = 0;
					Gibo[Count][1] = 0;
					Count--;
					if ( child.Value < temp )
					{
						child.Value = temp;
						child.Position = 100 * i + j;
					}
					if ( child.Value >= beta )
					{
						return child.Value;
					}
					alpha = max( alpha, child.Value );
				}
			}
		}
	}
	child.Parent->Position = child.Position;
	return child.Value;
}
int Omok::MinValue( Node& state, int alpha, int beta )
{
	SearchEndTime = clock();
	if ( SearchEndTime - EndTime >= CLOCKS_PER_SEC ) Timer();
	Node child;
	child.Value = 10000;
	child.Parent = &state;
	child.Height = child.Parent->Height + 1;
	if ( ( (double) ( EndTime - StartTime ) >= TIMELIMIT - 3 * CLOCKS_PER_SEC ) || ( child.Height >= NODELIMIT ) )
	{
		return Evaluate();
	}
	else
	{
		for ( int i = 1; i <= N; i++ )
		{
			for ( int j = 1; j <= N; j++ )
			{
				if ( GameBoard->Map[i][j] == 0 )
				{
					GameBoard->Map[i][j] = ( Count % 2 ) ? 1 : -1;
					Gibo[Count][0] = i;
					Gibo[Count][1] = j;
					Count++;
					int temp = MaxValue( child, alpha, beta );
					GameBoard->Map[i][j] = 0;
					Gibo[Count][0] = 0;
					Gibo[Count][1] = 0;
					Count--;
					if ( child.Value > temp )
					{
						child.Value = temp;
						child.Position = 100 * i + j;
					}
					if ( child.Value <= alpha )
					{
						return child.Value;
					}
					beta = min( beta, child.Value );
				}
			}
		}
	}
	child.Parent->Position = child.Position;
	return child.Value;
}

void Omok::Timer()
{
	EndTime = clock();
	GoToXY( 3, N );
	cout << "TIMER :";
	cout.width( 5 );
	cout << ( TIMELIMIT - ( EndTime - StartTime ) ) / CLOCKS_PER_SEC << "s";
	GoToXY( CursorX * 2, CursorY );

	if ( TIMELIMIT < ( EndTime - StartTime ) )
	{
		GoToXY( 3, N );
		cout << "TIME OUT";
		if ( Count % 2 == 1 )
		{
			Winner = -1000;
		}
		else if ( Count % 2 == 0 )
		{
			Winner = +1000;
		}
	}
}