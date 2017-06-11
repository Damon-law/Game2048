// Game2048v1.0.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "Game.h"
Game GAME;
int main()
{
	GAME.drawBoard();
	while (1)
	{
		GAME.update();
		while (GAME.getgame().GetGameStatus() == 0)
		{
			GAME.run();
		}
		GAME.drawResult();
		//GAME.again();
	}
    return 0;
}

