#ifndef GAME2048_H
#define GAME2048_H

#include<iostream>
#include "machine.h"
#include "game.h"
using namespace std;
class game2048 : public machine, public game
{
		
	private:
		int buff[4][4];  //������
		int score;       //��ǰ���� 
		int mscore;      //��ʷ��߷� 
		
		int check();
		int operate(int op);
		void init();
		void inFile();   //������߷� 
		void outFile();   //д����߷� 
		void createRandValue();
		void printInterface();
		
	public:
		void runGame();
};

#endif
