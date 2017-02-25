#include "machine.h"
#include "admin.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <windows.h>
using namespace std;

int machine::gameNum = 0;
int machine::coin = 0;
int machine::mcoin = 0;
int machine::runningGame = -1;
char* machine::gameName[100] = {0};
int machine::gameCoin[];

int machine::gameOpeate(int op){          //��Ϸ���� 
	if(op == 0x0D){
		system("pause");
	} else if(op == 0x1B){
		system("cls");
//		chooseGame();
		return 1;
	}
	return 0;
}

int machine::checkCoin(int id){
	if(id < 0 || id > gameNum-1)
		return 1;
	gameCoin[id] = gameCoin[id] < 1 ? 1 : gameCoin[id];
	if(coin < gameCoin[id]){
		return 0;
	}
	coin -= gameCoin[id];
	mcoin += gameCoin[id]; 
	return 1;	
}

void machine::addCoin(){
	coin++;
}

int machine::ifContinue(){
	int choose;
	cout<<"0.�˳���Ϸ\t1.����\n��ѡ��";
	cin>>choose;
	if(choose==1){
		if(!checkCoin(runningGame)){
			system("cls");
			cout<<"��Ϸ�Ҳ���"<<endl;
			Sleep(600);	
			return 0;		
		}
		return 1;
	}else{
//		chooseGame();
		return 0;
	}
}

void machine::setHeight(int t){
	t = (t<0)?0:t;
	height = t;
}

void machine::setTop(int t){
	t = (t<0)?0:t;
	top = t;
}

void machine::setLeft(int t){
	t = (t<0)?0:t;
	left = t;
}

void machine::setWidth(int t){
	t = (t<0)?0:t;
	width = t;
}

/*   ����ÿ����Ϸ����    */
void machine::readData(){
	int i = 0, j = 0, flag = 0;
	int tempCoin[100];
	char* tempGameName[100];
	
	char **t = new char*[100];    //������λ���� 
	for(int m=0;m<100;m++){
		t[m] = new char[30];
	}
	
	ifstream in("./data/gameCoin.txt", ios::in);  //��������� ��������c++������Ȼ��nocreate�򿪷�ʽc++�����Ѳ�֧�� 
	if(in){
		while(!in.eof()){
			in>>t[i];
			if(strcmp(t[i], "#") == 0){    //#Ϊ�ָ����������� 
				flag = 1;
				j = 0;
				continue;
			}
			if(flag){
				tempCoin[j] = atoi(t[i]);   //ת��int
			} else {
				tempGameName[j] = t[i];				
			}
			i++;
			j++;
		}
		
		delete []t;   //ɾ����ʱ���� 
		
		for(int k=0;k<gameNum;k++){
			for(int l=0;l<j;l++){
				if(strcmp(tempGameName[l], gameName[k]) == 0){
					gameCoin[k] = tempCoin[l];
					break;
				}
			}
		}
	}
}

void machine::showTop(){
	int mscore1,mscore2;
	ifstream in("./data/game2048.dat", ios::binary);
	if(in){
		in.read((char*)&mscore1, sizeof(int));
	} 
	in.close();	
	ifstream in2("./data/greedySnake.dat", ios::binary);
	if(in2){
		in2.read((char*)&mscore2, sizeof(int));
	} 
	in2.close();	
	system("cls");
	gotoxy(1,0);
	cout<<"\tTop"<<endl;
	gotoxy(1,2);
	cout<<"2048\t"<<mscore1<<endl;
	gotoxy(1,4);
	cout<<"̰����\t"<<mscore2<<endl;
	gotoxy(1,6);
	system("pause");
}

void machine::gotoxy(int x, int y){ 
	COORD pos = {x,y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}
 
void machine::appendGame(char const* name, game *g){
	gameName[gameNum] = (char*)name;
	games[gameNum] = g;
	gameNum++;
}

void machine::getCoin(int game){
	coin+= gameCoin[game];
	cout<<"��ϲ�������Ϸ��¼���������������� "<<gameCoin[game]<<" ö��Ϸ��"<<endl;
} 

void machine::help(){
	system("cls");
	cout<<endl;
	cout<<" 1.Ͷ�����Ϸ�Ҳ����Թ黹"<<endl;
	cout<<" 2.����Ϸ�����п��԰��س�������ͣ"<<endl;
	cout<<" 3.����Ϸ�п��԰�ESC�����˳���Ϸ"<<endl;
	cout<<" 4.������Ϸ��¼�ɻ����Ӧ����Ϸ�ҽ�������õ���Ϸ���Զ�Ͷ�뱾��\n"<<endl;
	cout<<" ";
	system("pause");
}
void machine::openMachine(){
	gotoxy(left,top);
	for(int i=0;i<width;i++){
		cout<<"*";
	}
	cout<<endl;
 	gotoxy(left,top+1);
	for(int i=0;i<height;i++)
	{ 
		cout<<"*";
		for(int j=0;j<width-2;j++)
			cout<<" ";
		cout<<"*"<<endl;
    	gotoxy(left,top+i+2);

	Sleep(100);
	}
	for(int i=0;i<width;i++){
		cout<<"*";
	}
	cout<<endl;
	gotoxy(left+width/2-8,top+height/2);
	system("color 3");
	cout<<"��ӭ����Ϸ��";
	Sleep(300);
	system("color 4");
    Sleep(300);
	system("color B");
	Sleep(300);
	system("color D");
	Sleep(300);
	system("color F");
	gotoxy(left,height+top+3);
}

void machine::show(){
	int flag=0;
	system("color F");
	system("cls");
	gotoxy(left,top);
	for(int i=0;i<width;i++){
		cout<<"*";
	}
	cout<<endl;
 	gotoxy(left,top+1);
	for(int i=0;i<height;i++)
	{ 
		cout<<"*";
		for(int j=0;j<width-2;j++)
			cout<<" ";
		cout<<"*"<<endl;
    	gotoxy(left,top+i+2);
	}
	for(int i=0;i<width;i++){
		cout<<"*";
	}
	cout<<endl;
	gotoxy(left+width/2-8,top+height/2);
	cout<<"��ӭʹ����Ϸ��";
	gotoxy(left,height+top+3);
	if(gameNum == 0){
		cout<<"���������Ϸ�ٴ���Ϸ��"<<endl;
		exit(0); 
	}
	int len=0; 
	len+=strlen("  1.����Ϸ     ");
	if(len < width){
		cout<<"1.����Ϸ     ";
	} else{
		flag+=2;
		gotoxy(left,height+top+3+flag);
		cout<<"1.����Ϸ     ";
		len = 0;
	}
	len+=strlen("  2.��ʷ���     ");
	if(len < width){
		cout<<"2.��ʷ���     ";
	} else{
		flag+=2;
		gotoxy(left,height+top+3+flag);
		cout<<"2.��ʷ���     ";
		len = 0;
	}
	len+=strlen("  3.��Ϸ����     ");
	if(len < width){
		cout<<"3.��Ϸ����     ";
	} else{
		flag+=2;
		gotoxy(left,height+top+3+flag);
		cout<<"3.��Ϸ����     ";
		len = 0;
	}
	len+=strlen("777.�����̨     ");
	if(len < width){
		cout<<"777.�����̨     ";
	} else{
		flag+=2;
		gotoxy(left,height+top+3+flag);
		cout<<"777.�����̨     ";
		len = 0;
	}
	gotoxy(left+width-17, top+height);
	cout<<"ʣ����Ϸ�ң�"<<coin;
	gotoxy(left,height+top+3+flag+2);
	cout<<"��ѡ��"; 
	gotoxy(left+8 ,top+height+5+flag);
	int select;
	cin>>select;
	switch(select){
		case 1:{
			chooseGame();
			break;
		}
		case 2:{
			runningGame = -1;
			showTop();
			break;
		}
		case 3:{
			runningGame = -1;			
			help();
			break;
		} 
		case 777:{
			admin a;
			runningGame = -1;
			if(a.password()){
				a.show();
			}
			break;			
		}
	} 
	system("cls");		
}

void machine::chooseGame(){
	while(1){
		int flag=0, mark=0;
		system("color F");
		system("cls");
		gotoxy(left,top);
		for(int i=0;i<width;i++){
			cout<<"*";
		}
		cout<<endl;
	 	gotoxy(left,top+1);
		for(int i=0;i<height;i++)
		{ 
			cout<<"*";
			for(int j=0;j<width-2;j++)
				cout<<" ";
			cout<<"*"<<endl;
	    	gotoxy(left,top+i+2);
		}
		for(int i=0;i<width;i++){
			cout<<"*";
		}
		cout<<endl;
		gotoxy(left+width/2-8,top+height/2);
		cout<<"ѡ����Ϸ";
		gotoxy(left,height+top+3);
		int len=0; 
	
		len+=strlen("0.Ͷ��     ");
		if(len < width){
			cout<<"0.Ͷ��     ";
		} else{
			flag+=2;
			gotoxy(left,height+top+3+flag);
			cout<<"0.Ͷ��     ";
			len = 0;
		}
		for(int i=0;i<gameNum;i++){   
			len+=strlen(gameName[i]) + 1 + strlen(".     ");
			if(len < width){
				cout<<i+1<<"."<<gameName[i]<<"     ";
			} else{
				flag+=2;
				gotoxy(left,height+top+3+flag);
				cout<<i+1<<"."<<gameName[i]<<"     ";
				len = 0;
			}
		}	
		len+=strlen(" .����     ");
		if(len < width){
			cout<<gameNum+1<<".����     ";
		} else{
			flag+=2;
			gotoxy(left,height+top+3+flag);
			cout<<gameNum+1<<".����     ";
			len = 0;
		}
		for(int i=0;i<gameNum;i++){
			gotoxy(left+width+5, top+2+i);
			gameCoin[i] = gameCoin[i]<1 ? 1 : gameCoin[i];
			cout<<gameName[i]<<"\t"<<gameCoin[i]<<"ö/��";
		}	
		gotoxy(left+width-17, top+height);
		cout<<"ʣ����Ϸ�ң�"<<coin;
		gotoxy(left,height+top+3+flag+2);
		cout<<"��ѡ��"; 
		gotoxy(left+8 ,top+height+5+flag);

		int select; 
		while(1){
			cin>>select;
			if(select != 0 && !checkCoin(select-1)){
				gotoxy(left ,top+height+flag+7);
				cout<<"��Ϸ�Ҳ��㣡";
				gotoxy(left+8  ,top+height+flag+5);   //�������䣬���ء���ѡ�񣺡����ֲ�����ϴ����� 
				cout<<" ";
				gotoxy(left+8  ,top+height+flag+5);			
				continue;
			}
			break;	
		}
		for(int i=0;i<gameNum;i++){
			if(select == 0){            //Ͷ�� 
				addCoin();
				break;
			} else if(i+1 == select){   //������Ϸ 
				runningGame = i;				
				games[i]->runGame();
				mark = 1;
				break;
			} else if(select == gameNum+1){
				mark = 1;
				break;
			}
		}
		if(mark) break;	
	}
	
}
