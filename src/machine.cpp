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

int machine::gameOpeate(int op){          //游戏操作 
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
	cout<<"0.退出游戏\t1.继续\n请选择：";
	cin>>choose;
	if(choose==1){
		if(!checkCoin(runningGame)){
			system("cls");
			cout<<"游戏币不足"<<endl;
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

/*   读入每个游戏费用    */
void machine::readData(){
	int i = 0, j = 0, flag = 0;
	int tempCoin[100];
	char* tempGameName[100];
	
	char **t = new char*[100];    //创建二位数组 
	for(int m=0;m<100;m++){
		t[m] = new char[30];
	}
	
	ifstream in("./data/gameCoin.txt", ios::in);  //《面向对象 程序语言c++》上虽然的nocreate打开方式c++现在已不支持 
	if(in){
		while(!in.eof()){
			in>>t[i];
			if(strcmp(t[i], "#") == 0){    //#为分隔符，不读入 
				flag = 1;
				j = 0;
				continue;
			}
			if(flag){
				tempCoin[j] = atoi(t[i]);   //转成int
			} else {
				tempGameName[j] = t[i];				
			}
			i++;
			j++;
		}
		
		delete []t;   //删除临时变量 
		
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
	cout<<"贪吃蛇\t"<<mscore2<<endl;
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
	cout<<"恭喜你打破游戏记录！本机决定奖励你 "<<gameCoin[game]<<" 枚游戏币"<<endl;
} 

void machine::help(){
	system("cls");
	cout<<endl;
	cout<<" 1.投入的游戏币不予以归还"<<endl;
	cout<<" 2.在游戏进行中可以按回车进行暂停"<<endl;
	cout<<" 3.在游戏中可以按ESC立即退出游戏"<<endl;
	cout<<" 4.打破游戏记录可获得相应的游戏币奖励，获得的游戏币自动投入本机\n"<<endl;
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
	cout<<"欢迎打开游戏机";
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
	cout<<"欢迎使用游戏机";
	gotoxy(left,height+top+3);
	if(gameNum == 0){
		cout<<"请先添加游戏再打开游戏机"<<endl;
		exit(0); 
	}
	int len=0; 
	len+=strlen("  1.玩游戏     ");
	if(len < width){
		cout<<"1.玩游戏     ";
	} else{
		flag+=2;
		gotoxy(left,height+top+3+flag);
		cout<<"1.玩游戏     ";
		len = 0;
	}
	len+=strlen("  2.历史最高     ");
	if(len < width){
		cout<<"2.历史最高     ";
	} else{
		flag+=2;
		gotoxy(left,height+top+3+flag);
		cout<<"2.历史最高     ";
		len = 0;
	}
	len+=strlen("  3.游戏帮助     ");
	if(len < width){
		cout<<"3.游戏帮助     ";
	} else{
		flag+=2;
		gotoxy(left,height+top+3+flag);
		cout<<"3.游戏帮助     ";
		len = 0;
	}
	len+=strlen("777.进入后台     ");
	if(len < width){
		cout<<"777.进入后台     ";
	} else{
		flag+=2;
		gotoxy(left,height+top+3+flag);
		cout<<"777.进入后台     ";
		len = 0;
	}
	gotoxy(left+width-17, top+height);
	cout<<"剩余游戏币："<<coin;
	gotoxy(left,height+top+3+flag+2);
	cout<<"请选择："; 
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
		cout<<"选择游戏";
		gotoxy(left,height+top+3);
		int len=0; 
	
		len+=strlen("0.投币     ");
		if(len < width){
			cout<<"0.投币     ";
		} else{
			flag+=2;
			gotoxy(left,height+top+3+flag);
			cout<<"0.投币     ";
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
		len+=strlen(" .返回     ");
		if(len < width){
			cout<<gameNum+1<<".返回     ";
		} else{
			flag+=2;
			gotoxy(left,height+top+3+flag);
			cout<<gameNum+1<<".返回     ";
			len = 0;
		}
		for(int i=0;i<gameNum;i++){
			gotoxy(left+width+5, top+2+i);
			gameCoin[i] = gameCoin[i]<1 ? 1 : gameCoin[i];
			cout<<gameName[i]<<"\t"<<gameCoin[i]<<"枚/次";
		}	
		gotoxy(left+width-17, top+height);
		cout<<"剩余游戏币："<<coin;
		gotoxy(left,height+top+3+flag+2);
		cout<<"请选择："; 
		gotoxy(left+8 ,top+height+5+flag);

		int select; 
		while(1){
			cin>>select;
			if(select != 0 && !checkCoin(select-1)){
				gotoxy(left ,top+height+flag+7);
				cout<<"游戏币不足！";
				gotoxy(left+8  ,top+height+flag+5);   //以下三句，返回“请选择：”并局部清除上次输入 
				cout<<" ";
				gotoxy(left+8  ,top+height+flag+5);			
				continue;
			}
			break;	
		}
		for(int i=0;i<gameNum;i++){
			if(select == 0){            //投币 
				addCoin();
				break;
			} else if(i+1 == select){   //进行游戏 
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
