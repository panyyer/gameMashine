#ifndef GAME2048_H
#define GAME2048_H

#include<iostream>
#include "machine.h"
#include "game.h"
using namespace std;
class game2048 : public machine, public game
{
		
	private:
		int buff[4][4];  //缓冲器
		int score;       //当前分数 
		int mscore;      //历史最高分 
		
		int check();
		int operate(int op);
		void init();
		void inFile();   //读出最高分 
		void outFile();   //写入最高分 
		void createRandValue();
		void printInterface();
		
	public:
		void runGame();
};

#endif
