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
	cout<<"���������루q���أ�:";
	char input[30] = {'\0'};
	cin>>input;
	if(input[0] == 'q' && input[1] == '\0'){
		return 0;
	}
	for(i=2;strcmp(pass, input) != 0 && i>0;i--){
		system("cls");
		cout<<"�����������!\n";
		cout<<"�㻹��������"<<i<<"��\n";
		cout<<"��������������:";
		cin>>input;
	}
	if(i==0 && strcmp(pass, input) != 0){
		cout<<"ϵͳ������";
		Sleep(1000);
		exit(0);
	}
	if(strcmp(pass, input) == 0){
		system("cls");
		cout<<"������ȷ����������ϵͳ...";
		system("cls");
		return 1;
	}
	return 0; 
}

void admin::changePass(){
	char input[30] = {'\0'}, newpass1[30] = {'\0'}, newpass2[30] = {'\0'};
	cout<<"����ԭ���룺";
	cin>>input;
	if(strcmp(pass, input) == 0){
		ofstream out("./data/pass.txt");
		while(1){
			cout<<"�����������룺";
			cin>>newpass1;
			cout<<"���ٴ����������룺";
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
				cout<<"�޸ĳɹ���"<<endl;
				strcpy(pass, newpass1);
				Sleep(500); 
				break;
			} else {
				cout<<"�������벻һ�£�"<<endl;
			}
		}
	} else {
		cout<<"��������";
	}
}

void admin::takeOut(){
	if(machine::mcoin > 0){
		ofstream out("./data/coin.dat", ios::binary | ios::app);
		if(out){
			out.write((char*)&machine::mcoin, sizeof(int));
		}
		out.close();
		cout<<"��ȡ��"<<machine::mcoin<<"ö��Ϸ��"<<endl;
		machine::mcoin = 0;
	} else{
		cout<<"û�п�ȡ��������Ϸ�ң�"<<endl;
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
	cout<<"��ֹĿǰ����Ϸ�����������������ǣ�"<<profit<<"Ԫ\tע����Ϸ�� 1Ԫ/ö"<<endl;
	system("pause");
}

void admin::setGameCoin(){
	int select,fare;
	cout<<endl; 
	for(int i=0;i<machine::gameNum;i++){
		cout<<i+1<<"."<<machine::gameName[i]<<endl;
	}
	cout<<"Ҫ�����շѵ���Ϸ��";
	cin>>select;

	if(select > 0 && select <= machine::gameNum){
		cout<<"���÷���Ϊ��";
		cin>>fare;
		machine::gameCoin[select-1] = fare;

 		ofstream fileout("./data/gameCoin.txt",ios::trunc);    //���ԭ�������� 
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
		cout<<i<<"���ػ�.."<<endl;
		Sleep(1000);
	}		
	exit(0);
}

void admin::show(){
	int op;
	while(1){
		system("cls");
		cout<<"����Ϸ����̨��\n"<<endl;
		cout<<"0.�ر���Ϸ��\t1.�ó���Ϸ��\t2.�鿴��ӯ��\t3.��������\t4.������Ϸ�շ�\t5.�˳���̨\n"<<endl;
		cout<<"�������";
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



