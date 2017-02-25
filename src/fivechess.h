#ifndef A_H
#define A_H

#include <iostream>
#include "machine.h"
#include "game.h"

using namespace std; 

class fiveChess : public machine, public game
{
	private:
		int cx;							//����x���� 
		int cy;
		int cols;   			   	 	//���̻�������ǰ���� 
		int rows;  				 	 	//���̻�������ǰ���� 
		int now;						//���巽 
		int ch[100][100];   		 	//���������ϵ����� 
		char buff[100*2+1][100*4+3]; 	//���̻�����
		int maxm;    					//���̴�С 
		
		void gotoxy(int x, int y);
		void printChessBoard();    				//������� 
		void write(char *c1, char const * c2);  //������c1д���ַ�c2 
		int check();
		char const *getCurse(int i, int j);     //��ȡ��� 
		char const *getTable(int i, int j);     //��ȡ��ǰλ�ö�Ӧ���Ʊ�� 
		
	public:
		void init();              //��ʼ���Ծ� 
		void runGame();           //���жԾ� 

};

#endif
