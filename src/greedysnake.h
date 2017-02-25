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
	int dir;    //�ߴ�ʱ�ƶ��ķ��� 
	int len;
	struct sbody body[100*100];  //���� 
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
		int mscore;  //��ʷ��� 

		int check();
		void init();
		void move();
		void inFile();
		void outFile();	
		void personOperate();
		void eatFood();
		void printSnake();     //����� 
		void printFood();      //���ʳ��
		void printWall();      //���ǽ�� 
		void printData();      //�����Ϸ���� 
		void createFood();

	public: 
		void runGame();


};

#endif
