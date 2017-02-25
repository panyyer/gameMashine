#ifndef GREEDYSNAKE_H
#define GREEDYSNAKE_H

#include "machine.h"
#include "game.h"
#include <iostream>

using namespace std;

struct sbody{
	int x;
	int y;
};

struct snake{
	int dir;    //蛇此时移动的方向 
	int len;
	struct sbody body[100*100];  //蛇身 
};

struct food{
	int x;
	int y;
	int type;
};

class greedySnake : public machine, public game
{
	private:
		snake gSnake;  //greedy snake
		food sFood;    //snake food
		char const* foodType[10];
		int width;
		int height;
		int level;
		int score;
		int mscore;  //历史最高 

		int check();
		void init();
		void move();
		void inFile();
		void outFile();	
		void personOperate();
		void eatFood();
		void printSnake();     //输出蛇 
		void printFood();      //输出食物
		void printWall();      //输出墙壁 
		void printData();      //输出游戏数据 
		void createFood();

	public: 
		void runGame();


};

#endif
