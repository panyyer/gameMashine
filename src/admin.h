#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>

using namespace std;
class admin
{
	private:
		char pass[30];
		void checkProfit(); //�鿴��ӯ�� 
		void takeOut();     //�ó���Ϸ��
		void changePass();	
		void init();
		void setGameCoin();
		void poweroff();    //�ػ� 
				
	public:
		int profit;
		int password();   //��������
		void show();      //�������
					
	admin(){}
	
	~admin(){}
};

#endif
