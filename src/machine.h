#ifndef DISPLAY_H
#define DISPLAY_H

#include "game.h"
#include "admin.h"
#include <iostream>

using namespace std;

class machine
{
	private:
		int width;     //�������� 
		int height;    //������߶� 
		int left;      //��������߾�
		int top;       //�������ϱ߾� 	
		game *games[100];  //��Ϸ���� 
		int checkCoin(int id);     //����Ƿ����㹻Ӳ�� 
		void chooseGame();   //ѡ����Ϸ 
		void help();    //��Ϸ���� 
		
	protected:
		void gotoxy(int x, int y);   //�ƶ����
		int gameOpeate(int op);        //��ͣ��Ϸ
		int ifContinue();            //��Ϸ�������Ƿ����
		void getCoin(int game);            //�Ƽ�¼����Ϸ�ҽ��� 
		static int runningGame; //��ǰ�������е���Ϸ 
		static int coin;      //��ҿ���Ӳ����
		static char* gameName[100];
		static int gameCoin[100];   //����Ϸ��ҪӲ���� 
		static int gameNum;
		static int mcoin;     //��Ϸ������Ӳ����
		
	public:

		void show();          //չʾ������
		void openMachine();   //�������� 
		void showTop();      //�����߷� 
		void addCoin();       //Ͷ�� 
		void readData();      //������Ϸ���� 
		void appendGame(char const* name, game *g);    //׷����Ϸ
		void setWidth(int t);
		void setHeight(int t);
		void setLeft(int t);
		void setTop(int t);

	machine(){        //��ʼ������ 
		width = 79;
		height = 10;
		left = 5;
		top = 0;
	}
	
	friend admin;
};

#endif
