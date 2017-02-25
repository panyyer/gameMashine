#include "admin.h"
#include "machine.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <windows.h>
#include <string>
using namespace std;

void admin::init(){
	char t;
	int i=0;
	pass[0] = '1';
	pass[1] = '2';
	pass[2] = '3';

	ifstream in("./data/pass.txt");
	if(in){
		while(in>>t && t != '\0'){
			pass[i] = t-i;
			i++; 			
		}
		pass[i] = '\0';
	}
	in.close();
}

int admin::password(){
	int i;
	init();
	system("cls");
	cout<<"请输入密码（q返回）:";
	char input[30] = {'\0'};
	cin>>input;
	if(input[0] == 'q' && input[1] == '\0'){
		return 0;
	}
	for(i=2;strcmp(pass, input) != 0 && i>0;i--){
		system("cls");
		cout<<"输入密码错误!\n";
		cout<<"你还可以输入"<<i<<"次\n";
		cout<<"请重新输入密码:";
		cin>>input;
	}
	if(i==0 && strcmp(pass, input) != 0){
		cout<<"系统已锁定";
		Sleep(1000);
		exit(0);
	}
	if(strcmp(pass, input) == 0){
		system("cls");
		cout<<"密码正确，即将进入系统...";
		system("cls");
		return 1;
	}
	return 0; 
}

void admin::changePass(){
	char input[30] = {'\0'}, newpass1[30] = {'\0'}, newpass2[30] = {'\0'};
	cout<<"输入原密码：";
	cin>>input;
	if(strcmp(pass, input) == 0){
		ofstream out("./data/pass.txt");
		while(1){
			cout<<"请输入新密码：";
			cin>>newpass1;
			cout<<"请再次输入新密码：";
			cin>>newpass2;
			if(strcmp(newpass1, newpass2) == 0){
				char tpass[30];
				int i=0;
				while(newpass1[i] != '\0'){
					tpass[i] = newpass1[i];
					tpass[i] = tpass[i] + i;
					i++;
				}
				if(out){
					tpass[i] = '\0';
					out.write(tpass, i+1);
				}
				out.close();
				cout<<"修改成功！"<<endl;
				strcpy(pass, newpass1);
				Sleep(500); 
				break;
			} else {
				cout<<"两次密码不一致！"<<endl;
			}
		}
	} else {
		cout<<"密码有误！";
	}
}

void admin::takeOut(){
	if(machine::mcoin > 0){
		ofstream out("./data/coin.dat", ios::binary | ios::app);
		if(out){
			out.write((char*)&machine::mcoin, sizeof(int));
		}
		out.close();
		cout<<"共取出"<<machine::mcoin<<"枚游戏币"<<endl;
		machine::mcoin = 0;
	} else{
		cout<<"没有可取出来的游戏币！"<<endl;
	}
	system("pause");

}

void admin::checkProfit(){
	int temp = 0;
	profit = 0;

	ifstream in("./data/coin.dat", ios::binary);
	if(in){
		while(!in.eof()){
			in.read((char*)&temp, sizeof(int));
			profit += temp;
			temp = 0;
		}
	}
	in.close();	
	cout<<"截止目前，游戏机给您带来的利润是："<<profit<<"元\t注：游戏币 1元/枚"<<endl;
	system("pause");
}

void admin::setGameCoin(){
	int select,fare;
	cout<<endl; 
	for(int i=0;i<machine::gameNum;i++){
		cout<<i+1<<"."<<machine::gameName[i]<<endl;
	}
	cout<<"要更改收费的游戏：";
	cin>>select;

	if(select > 0 && select <= machine::gameNum){
		cout<<"设置费用为：";
		cin>>fare;
		machine::gameCoin[select-1] = fare;

 		ofstream fileout("./data/gameCoin.txt",ios::trunc);    //清空原来的内容 
 		fileout.close();
		ofstream out("./data/gameCoin.txt");
		if(out){
			char c1 = '#';
			char c2 = '\n';
			for(int i=0;i<machine::gameNum;i++){
				out<<machine::gameName[i]; 
				out.write((char*)&c2,1);
			}
			out.write((char*)&c1, 1);
			out.write((char*)&c2, 1);
			for(int i=0;i<machine::gameNum;i++){
				machine::gameCoin[i] = machine::gameCoin[i]<1 ? 1 : machine::gameCoin[i];
				out<<machine::gameCoin[i];
				out.write((char*)&c2,1);
			}
		}
		out.close();

		
	}
	system("pause");
}

void admin::poweroff(){
	cout<<endl;
	for(int i=3;i>0;i--){
		cout<<i<<"秒后关机.."<<endl;
		Sleep(1000);
	}		
	exit(0);
}

void admin::show(){
	int op;
	while(1){
		system("cls");
		cout<<"【游戏机后台】\n"<<endl;
		cout<<"0.关闭游戏机\t1.拿出游戏币\t2.查看总盈利\t3.更改密码\t4.更改游戏收费\t5.退出后台\n"<<endl;
		cout<<"请操作：";
		cin>>op;
		switch(op){
			case 0:{
				poweroff();
				break;
			}
			case 1:{
				takeOut();
				break;
			}
			case 2:{
				checkProfit();
				break;
			}
			case 3:{
				changePass();
				break;
			}
			case 4:{
				setGameCoin(); 
				break;
			}
		}
		if(op == 5){
			break;
		}
	}
}



