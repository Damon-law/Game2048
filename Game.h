#pragma once
#ifndef GAME_H_
#define GAME_H_

#include "ConsoleSet.h"
#include "MyTime.h"
#include "GameAlgorithm.h"
#include <conio.h>

int NUM[12] = { 1,2,4,8,16,32,64,128,256,512,1024,2048 };
int TEXTCOLOR[12] = { 3,4,5,6,7,8,9,10,11,12,13,14 };

class Game
{
private:
	GameAlgorithm game;
	MyTime mt;
	ConsoleSet canvas;
	//const int NUM[12];
	//const int TEXTCOLOR[12];
	int sum;
	int win;
	int maxscore;
public:
	Game();
	void drawBoard();
	inline int getNumLen(int num);
	void drawNum(int row, int col, int value);
	void update();
	void link();
	void run();
	void init();
	void drawResult();
	void again();
	GameAlgorithm & getgame();
};
Game::Game()//:NUM{ 1,2,4,8,16,32,64,128,256,512,1024,2048},TEXTCOLOR{ 3,4,5,6,7,8,9,10,11,12,13,14 }
{
	sum = 0;
	win = 0;
	maxscore = 0;
}
void Game::drawBoard()
{
	canvas.SetTitle(TEXT("Game2048"));
	canvas.SetCursorInvisible();
	canvas.SetForeground(9);
	canvas.SetCursorPosition(45, 4);
	printf("最高成绩：0");
	canvas.SetCursorPosition(45, 6);
	printf("胜率：0/0");
	canvas.SetForeground(12);
	canvas.SetCursorPosition(3, 2);
	printf("Score:0          Step:0");
	canvas.SetForeground(7);
	canvas.SetCursorPosition(0, 3);
	printf("   +------+------+------+------+\n");
	printf("   |      |      |      |      |\n");
	printf("   +------+------+------+------+\n");
	printf("   |      |      |      |      |\n");
	printf("   +------+------+------+------+\n");
	printf("   |      |      |      |      |\n");
	printf("   +------+------+------+------+\n");
	printf("   |      |      |      |      |\n");
	printf("   +------+------+------+------+\n");

	canvas.SetForeground(2);
	canvas.SetCursorPosition(1, 19);
	printf("%d年%d月%d日 星期%d", mt.GetYear(), mt.GetMonth(), mt.GetMDay(), mt.GetWDay());
	canvas.SetCursorPosition(1, 21);
	printf("Game Help：\n");
	printf(" Up↑  Down↓  Left←  Right→");
	canvas.SetCursorPosition(1, 23);
	printf("按q会有意外惊喜! ");

	canvas.SetForeground(10);
	canvas.SetCursorPosition(36, 12);
	printf("※※※※※※※※※※※※※※※※※※※※※");
	canvas.SetCursorPosition(36, 13);
	printf("※                                      ※");
	canvas.SetCursorPosition(36, 14);
	printf("※                                      ※");
	canvas.SetCursorPosition(36, 15);
	printf("※                                      ※");
	canvas.SetCursorPosition(36, 16);
	printf("※                                      ※");
	canvas.SetCursorPosition(36, 17);
	printf("※                                      ※");
	canvas.SetCursorPosition(36, 18);
	printf("※                                      ※");
	canvas.SetCursorPosition(36, 19);
	printf("※                                      ※");
	canvas.SetCursorPosition(36, 20);
	printf("※                                      ※");
	canvas.SetCursorPosition(36, 21);
	printf("※                                      ※");
	canvas.SetCursorPosition(36, 22);
	printf("※                                      ※");
	canvas.SetCursorPosition(36, 23);
	printf("※                                      ※");
	canvas.SetCursorPosition(36, 24);
	printf("※※※※※※※※※※※※※※※※※※※※※");

	canvas.SetForeground(2);
	canvas.SetCursorPosition(38, 13);
	printf("游戏说明：");
	canvas.SetCursorPosition(42, 14);
	printf("本游戏取材于安卓版的2048小游戏，");
	canvas.SetCursorPosition(42, 15);
	printf("游戏玩法简单却又充满趣味。");
	canvas.SetCursorPosition(42, 16);
	printf("在游戏中你只需要按上、下、左、右");
	canvas.SetCursorPosition(42, 17);
	printf("方向键即可，相同的数字相遇会合并");
	canvas.SetCursorPosition(42, 18);
	printf("为两者之和。当出现2048时即为胜利，");
	canvas.SetCursorPosition(42, 19);
	printf("当棋盘占满且无法移动时，游戏");
	canvas.SetCursorPosition(42, 20);
	printf("宣告失败。祝你玩得愉快！");
	canvas.SetCursorPosition(45, 22);
	printf(" --Damon Law");
}
int Game::getNumLen(int num) 
{
	if (num == 0)return 1;
	int len = 0;
	while (num) 
	{
		num /= 10;
		len++;
	}
	return len;
}
void Game::drawNum(int row, int col, int value)
{
	int x, y, len, color;
	len = getNumLen(value);
	x = 5 + 7 * col;
	y = 4 + 2 * row;
	canvas.SetCursorPosition(x, y);
	printf("    ");
	if (value == 0)return;
	if (len == 2 || len == 1)x++;
	for (int i = 0; i<12; i++) 
	{
		if (value == NUM[i]) 
		{
			color = TEXTCOLOR[i];
			break;
		}
	}
	canvas.SetCursorPosition(x, y);
	canvas.SetForeground(color);
	printf("%d", value);
}
void Game::update()
{
	canvas.SetForeground(13);
	canvas.SetCursorPosition(9, 2);
	printf("          ");
	canvas.SetCursorPosition(9, 2);
	printf("%d", game.GetScore());
	canvas.SetCursorPosition(25, 2);
	printf("          ");
	canvas.SetCursorPosition(25, 2);
	printf("%d", game.GetStep());

	for (int i = 0; i<4; i++) {
		for (int j = 0; j<4; j++) {
			drawNum(i, j, game.GetXYNum(i, j));
		}
	}
}
void Game::link() 
{
	system("explorer ");
}
void Game::run() 
{
	short ch;
	ch = _getch();
	if (ch == 0xE0) 
	{
		ch = _getch();
		switch (ch) 
		{
		case 72:game.Move(1); break;
		case 80:game.Move(2); break;
		case 75:game.Move(3); break;
		case 77:game.Move(4); break;
		}
		update();
	}
	else if (ch == 'q') {
		link();
	}
}
void Game::init()
{
	canvas.SetForeground(13);
	canvas.SetCursorPosition(9, 2);
	printf("          ");
	canvas.SetCursorPosition(9, 2);
	printf("0");
	canvas.SetCursorPosition(25, 2);
	printf("          ");
	canvas.SetCursorPosition(25, 2);
	printf("0");
	for (int i = 0; i<4; i++) {
		for (int j = 0; j<4; j++) {
			drawNum(i, j, 0);
		}
	}
}
void Game::drawResult()
{
	canvas.SetForeground(14);
	canvas.SetCursorPosition(1, 15);
	if (game.GetGameStatus() == 1) 
	{
		printf("恭喜你取得胜利！");
		win++;
	}
	else 
	{
		printf("好可惜··！失败了，再来一把？");
	}
	sum++;
	if (game.GetScore()>maxscore)maxscore = game.GetScore();
	canvas.SetForeground(9);
	canvas.SetCursorPosition(55, 4);
	printf("            ");
	canvas.SetCursorPosition(55, 4);
	printf("%d", maxscore);
	canvas.SetCursorPosition(51, 6);
	printf("            ");
	canvas.SetCursorPosition(51, 6);
	printf("%d/%d", win, sum);
	canvas.SetCursorPosition(57, 8);
	printf("0");
}
void Game::again()
{
	_getch();
	canvas.SetForeground(14);
	canvas.SetCursorPosition(1, 15);
	printf("                             ");
	game.clear();
	init();
}
 GameAlgorithm & Game::getgame()
{
	return game;
}
#endif // !GAME_H_

