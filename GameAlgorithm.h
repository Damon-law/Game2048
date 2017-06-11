#pragma once
//游戏2048算法实现
#ifndef GAME_ALGORITHM_H_
#define GAME_ALGORITHM_H_

#include "Random.h"
#include <iostream>
#include <cstring>
#include <list>

#define CHESS_BOARD_SIZE 4
#define MOVE_UP 1
#define MOVE_DOWN 2
#define MOVE_LEFT 3
#define MOVE_RIGHT 4
#define WIN_SCORE 2048

class GameState
{
public:
	int score;
	int steps;
	int Board[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE];
};

class GameAlgorithm
{
private:
	int score;
	int steps;
	int Board[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE];
	Random ran;
	GameState temp;
	void GetRandomPosition(int & x, int & y);
	const int NUM[2];
	inline void AddNum();
	inline void AddScore(int value);
	inline void MoveUp();
	inline void MoveDown();
	inline void MoveLeft();
	inline void MoveRight();
	inline int GetEmptyCounts();
public:
	GameAlgorithm();
	void Move(int direct);
	int GetXYNum(int x, int y);
	int GetScore();
	int GetStep();
	int GetGameStatus();
	bool IsFull();
	bool IsWin();
	bool IsLive();
	void clear();
};
GameAlgorithm::GameAlgorithm() :NUM{2,4}
{
	score = 0;
	steps = 0;
	memset(Board, 0, sizeof(Board));
	AddNum();
	AddNum();
}
void GameAlgorithm::GetRandomPosition(int & x, int & y)
{
	int emptycount = GetEmptyCounts();
	int pos = static_cast<int>(ran.GetRandom(0, emptycount));
	int rounds = -1;
	for(int i = 0; i < CHESS_BOARD_SIZE; ++i)
		for (int j = 0; j < CHESS_BOARD_SIZE; ++j)
			if (!Board[i][j])
			{
				++rounds;
				if (rounds == pos)
				{
					x = i;
					y = j;
					return;
				}
			}
}
void GameAlgorithm::AddNum()
{
	if (IsFull()) return;
	int x, y, values;
	GetRandomPosition(x, y);
	values = static_cast<int>(ran.GetRandom(0,2));
	Board[x][y] = NUM[values];
}
void GameAlgorithm::AddScore(int value)
{
	score += value;
}
int GameAlgorithm::GetEmptyCounts()
{
	int cnt = 0;
	for (int i = 0; i < CHESS_BOARD_SIZE; ++i)
		for (int j = 0; j < CHESS_BOARD_SIZE; ++j)
			if (!Board[i][j])	++cnt;
	return cnt;
}
void GameAlgorithm::MoveUp()
{
	int i, j, k;
	bool flag = false;
	for (j = 0; j<CHESS_BOARD_SIZE; j++)
	{
		for (i = 1; i<CHESS_BOARD_SIZE; i++)
		{
			if (!Board[i][j])continue;
			for (k = i - 1; k >= 0; k--)
			{
				if (Board[k][j])break;
			}
			if (k == -1)k++;
			if (Board[k][j] == Board[i][j])
			{
				Board[k][j] *= 2;
				Board[i][j] = 0;
				AddScore(Board[k][j]);
				flag = true;
			}
			else
			{
				if (Board[k][j] == 0)
				{
					Board[k][j] = Board[i][j];
					Board[i][j] = 0;
					flag = true;
				}
				else
				{
					if (k + 1 != i)
					{
						Board[k + 1][j] = Board[i][j];
						Board[i][j] = 0;
						flag = true;
					}
				}
			}
		}
	}
	if (flag)
	{
		AddNum();
		steps++;
	}
}
void GameAlgorithm::MoveDown()
{
	int i, j, k;
	bool flag = false;
	for (j = 0; j < CHESS_BOARD_SIZE; j++)
	{
		for (i = CHESS_BOARD_SIZE - 2; i >= 0; i--)
		{
			if (!Board[i][j])continue;
			for (k = i + 1; k < CHESS_BOARD_SIZE; k++)
			{
				if (Board[k][j])break;
			}
			if (k == CHESS_BOARD_SIZE)k--;
			if (Board[k][j] == Board[i][j])
			{
				Board[k][j] *= 2;
				Board[i][j] = 0;
				AddScore(Board[k][j]);
				flag = true;
			}
			else
			{
				if (Board[k][j] == 0)
				{
					Board[k][j] = Board[i][j];
					Board[i][j] = 0;
					flag = true;
				}
				else
				{
					if (k - 1 != i)
					{
						Board[k - 1][j] = Board[i][j];
						Board[i][j] = 0;
						flag = true;
					}
				}
			}
		}
	}
	if (flag)
	{
		AddNum();
		steps++;
	}
}
void GameAlgorithm::MoveLeft()
{
	int i, j, k;
	bool flag = false;
	for (i = 0; i < CHESS_BOARD_SIZE; i++)
	{
		for (j = 1; j < CHESS_BOARD_SIZE; j++)
		{
			if (!Board[i][j])continue;
			for (k = j - 1; k >= 0; k--)
			{
				if (Board[i][k])break;
			}
			if (k == -1)k++;
			if (Board[i][k] == Board[i][j])
			{
				Board[i][k] *= 2;
				Board[i][j] = 0;
				AddScore(Board[i][k]);
				flag = true;
			}
			else
			{
				if (Board[i][k] == 0)
				{
					Board[i][k] = Board[i][j];
					Board[i][j] = 0;
					flag = true;
				}
				else
				{
					if (k + 1 != j)
					{
						Board[i][k + 1] = Board[i][j];
						Board[i][j] = 0;
						flag = true;
					}
				}
			}
		}
	}
	if (flag)
	{
		AddNum();
		steps++;
	}
}
void GameAlgorithm::MoveRight()
{
	int i, j, k;
	bool flag = false;
	for (i = 0; i < CHESS_BOARD_SIZE; i++) {
		for (j = CHESS_BOARD_SIZE - 2; j >= 0; j--) {
			if (!Board[i][j])continue;
			for (k = j + 1; k < CHESS_BOARD_SIZE; k++) {
				if (Board[i][k])break;
			}
			if (k == CHESS_BOARD_SIZE)k--;
			if (Board[i][k] == Board[i][j]) {
				Board[i][k] *= 2;
				Board[i][j] = 0;
				AddScore(Board[i][k]);
				flag = true;
			}
			else {
				if (Board[i][k] == 0) {
					Board[i][k] = Board[i][j];
					Board[i][j] = 0;
					flag = true;
				}
				else {
					if (k - 1 != j) {
						Board[i][k - 1] = Board[i][j];
						Board[i][j] = 0;
						flag = true;
					}
				}
			}
		}
	}
	if (flag) 
	{
		AddNum();
		steps++;
	}
}
void GameAlgorithm::Move(int direct)
{ 
	//temp.score = score;
	//temp.steps = steps;
	//memcpy(Board, temp.Board, sizeof(Board));
	switch (direct)
	{
	case MOVE_UP: MoveUp(); break;
	case MOVE_DOWN: MoveDown(); break;
	case MOVE_LEFT: MoveLeft(); break;
	case MOVE_RIGHT:MoveRight(); break;
	}
}
int GameAlgorithm::GetXYNum(int x, int y)
{
	return Board[x][y];
}
int GameAlgorithm::GetScore()
{
	return score;
}
int GameAlgorithm::GetStep()
{
	return steps;
}
int GameAlgorithm::GetGameStatus()
{
	if (IsWin()) return 1;
	if (!IsFull()) return 0;
	if (IsLive()) return 0;
	return -1;
}
bool GameAlgorithm::IsFull()
{
	for (int i = 0; i < CHESS_BOARD_SIZE; ++i)
		for (int j = 0; j < CHESS_BOARD_SIZE; ++j)
			if (!Board[i][j])	return false;
	return true;
}
bool GameAlgorithm::IsWin()
{
	for (int i = 0; i < CHESS_BOARD_SIZE; ++i)
		for (int j = 0; j < CHESS_BOARD_SIZE; ++j)
			if (Board[i][j] == WIN_SCORE)	return true;
	return false;
}
bool GameAlgorithm::IsLive()
{
	for (int i = 0; i < CHESS_BOARD_SIZE - 1; ++i)
		for (int j = 0; j < CHESS_BOARD_SIZE - 1; ++j)
			if (Board[i][j] == Board[i + 1][j] || Board[i][j] == Board[i + 1][j])
				return true;
	for (int i = 0; i < CHESS_BOARD_SIZE - 1; ++i)
		if (Board[i][CHESS_BOARD_SIZE - 1] == Board[i + 1][CHESS_BOARD_SIZE - 1])
			return true;
	for (int i = 0; i < CHESS_BOARD_SIZE - 1; ++i)
		if (Board[CHESS_BOARD_SIZE - 1][i] == Board[CHESS_BOARD_SIZE][i + 1])
			return true;
}
void GameAlgorithm::clear()
{
	steps = 0;
	score = 0;
	memset(Board, 0, sizeof(Board));
}
#endif // !GAME_ALGORITHM_H_

