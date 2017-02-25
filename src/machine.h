#ifndef DISPLAY_H
#define DISPLAY_H

#include "game.h"
#include "admin.h"
#include <iostream>

using namespace std;

class machine
{
	private:
		int width;     //主界面宽度 
		int height;    //主界面高度 
		int left;      //主界面左边距
		int top;       //主界面上边距 	
		game *games[100];  //游戏对象 
		int checkCoin(int id);     //检查是否有足够硬币 
		void chooseGame();   //选择游戏 
		void help();    //游戏帮助 
		
	protected:
		void gotoxy(int x, int y);   //移动光标
		int gameOpeate(int op);        //暂停游戏
		int ifContinue();            //游戏结束后是否继续
		void getCoin(int game);            //破纪录后游戏币奖励 
		static int runningGame; //当前正在运行的游戏 
		static int coin;      //玩家可用硬币数
		static char* gameName[100];
		static int gameCoin[100];   //玩游戏需要硬币数 
		static int gameNum;
		static int mcoin;     //游戏机收入硬币数
		
	public:

		void show();          //展示主界面
		void openMachine();   //开机动画 
		void showTop();      //输出最高分 
		void addCoin();       //投币 
		void readData();      //读入游戏数据 
		void appendGame(char const* name, game *g);    //追加游戏
		void setWidth(int t);
		void setHeight(int t);
		void setLeft(int t);
		void setTop(int t);

	machine(){        //初始化参数 
		width = 79;
		height = 10;
		left = 5;
		top = 0;
	}
	
	friend admin;
};

#endif
