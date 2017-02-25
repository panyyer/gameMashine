#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>

using namespace std;
class admin
{
	private:
		char pass[30];
		void checkProfit(); //查看总盈利 
		void takeOut();     //拿出游戏币
		void changePass();	
		void init();
		void setGameCoin();
		void poweroff();    //关机 
				
	public:
		int profit;
		int password();   //输入密码
		void show();      //输出界面
					
	admin(){}
	
	~admin(){}
};

#endif
