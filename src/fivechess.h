#ifndef A_H
#define A_H

#include <iostream>
#include "machine.h"
#include "game.h"

using namespace std; 

class fiveChess : public machine, public game
{
	private:
		int cx;							//光标的x坐标 
		int cy;
		int cols;   			   	 	//棋盘缓冲器当前列数 
		int rows;  				 	 	//棋盘缓冲器当前行数 
		int now;						//下棋方 
		int ch[100][100];   		 	//储存棋盘上的棋子 
		char buff[100*2+1][100*4+3]; 	//棋盘缓冲器
		int maxm;    					//棋盘大小 
		
		void gotoxy(int x, int y);
		void printChessBoard();    				//输出棋盘 
		void write(char *c1, char const * c2);  //向棋盘c1写入字符c2 
		int check();
		char const *getCurse(int i, int j);     //获取光标 
		char const *getTable(int i, int j);     //获取当前位置对应的制表符 
		
	public:
		void init();              //初始化对局 
		void runGame();           //进行对局 

};

#endif
