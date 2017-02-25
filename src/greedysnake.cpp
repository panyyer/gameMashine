#include "greedysnake.h"
#include <cstring>
#include <conio.h>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <fstream>

#define UP 0x48
#define DOWN 0x50
#define LEFT 0x4B
#define RIGHT 0x4D
#define WALLTYPE "■"
#define HEAD "¤"
#define BODYTYPE "●"

using namespace std;

void greedySnake::init(){
	system("cls");
	cout<<"输入地图的宽度和高度（空格隔开）";
	cin>>width>>height;
	if(width <= 3 || height <= 3){
		width = height = 20;	
	}
	
	srand((int)time(NULL));
	system("cls");
	foodType[0] = "★";
	foodType[1] = "☆";
	foodType[2] = "◆";
	foodType[3] = "◇";
	foodType[4] = "▲";
	foodType[5] = "△";
	foodType[6] = "▼";
	foodType[7] = "▽";
	score = mscore = 0;
	level = 1;
	gSnake.dir = RIGHT;
	gSnake.len = 3;
	gSnake.body[0].x = 6;
	gSnake.body[0].y = 1;
	gSnake.body[1].x = 4;
	gSnake.body[1].y = 1;
	gSnake.body[2].x = 2;
	gSnake.body[2].y = 1;
	inFile();
	createFood();
	printWall();
	printSnake();
	printFood();
}
 
void greedySnake::inFile(){
	ifstream in("./data/greedySnake.dat", ios::binary);
	if(in){
		in.read((char*)&mscore, sizeof(int));
	}
	in.close();
}

void greedySnake::outFile(){
	ofstream out("./data/greedySnake.dat", ios::binary);
	if(out){
		out.write((char*)&score, sizeof(int));
	}
	out.close();
}

void greedySnake::printData(){
	gotoxy((width+4)*2, 2);
	cout<<"当前分数："<<score;	
	gotoxy((width+4)*2, 3);
	cout<<"历史最高："<<mscore;	
	gotoxy((width+4)*2, 4);
	cout<<"当前等级："<<level;	
}

int greedySnake::check(){
	int x = gSnake.body[0].x;
	int y = gSnake.body[0].y;
	if(x<2 || x>(width*2+1) || y<1 || y>height){
		return 0;
	} else {
		for(int i=1;i<gSnake.len;i++){
			if(x == gSnake.body[i].x && y == gSnake.body[i].y){
				return 0;
			}
		}
	}
	return 1;
}

void greedySnake::printWall(){
	for(int i=0;i<width+2;i++){
		cout<<WALLTYPE;
	}
	for(int i=0;i<height;i++){
		gotoxy(0, i+1);
		cout<<WALLTYPE;
		gotoxy((width+1)*2, i+1);
		cout<<WALLTYPE;
	}
	gotoxy(0, height+1);
	for(int i=0;i<width+2;i++){
		cout<<WALLTYPE;
	}
}

void greedySnake::personOperate(){
	int op = getch();
	switch(op){
		case UP: {
			if(gSnake.dir != DOWN){
				gSnake.dir = UP;					
			}
			break;
		}
		case DOWN: {
			if(gSnake.dir != UP){
				gSnake.dir = DOWN;
			}
			break;
		}
		case LEFT: {
			if(gSnake.dir != RIGHT){
				gSnake.dir = LEFT;
			}
			break;
		}
		case RIGHT: {
			if(gSnake.dir != LEFT){
				gSnake.dir = RIGHT;
			}
			break;
		}
	}
}

void greedySnake::move(){
	int tempx = gSnake.body[gSnake.len-1].x;  //缓存最后一个节点坐标，根据移动后是否能吃到食物来选择去留 
	int tempy = gSnake.body[gSnake.len-1].y; 
	cout<<" ";
	for(int i=gSnake.len-1;i>0;i--){
		gSnake.body[i].x = gSnake.body[i-1].x;
		gSnake.body[i].y = gSnake.body[i-1].y;
	}
	switch(gSnake.dir){
		case UP: {
			gSnake.body[0].y--; 
			break;
		}
		case DOWN: {
			gSnake.body[0].y++; 
			break;
		}
		case LEFT: {
			gSnake.body[0].x-=2; 
			break;
		}
		case RIGHT: {
			gSnake.body[0].x+=2; 
			break;
		}		
	}
	if(gSnake.body[0].x == sFood.x && gSnake.body[0].y == sFood.y){
		gSnake.len++;
		gSnake.body[gSnake.len-1].x = tempx;
		gSnake.body[gSnake.len-1].y = tempy;
		createFood();
		score+=10;
		if(level < 9)
			level = score/50 + 1;
	} else{
		gotoxy(tempx, tempy);  //吃不到食物，清除原来的最后一节点 
		cout<<" "; 
	}
}

void greedySnake::printSnake(){
	gotoxy(gSnake.body[0].x, gSnake.body[0].y);
	cout<<HEAD;
	for(int i=1;i<gSnake.len;i++){
		gotoxy(gSnake.body[i].x, gSnake.body[i].y);
		cout<<BODYTYPE;
	}
}

void greedySnake::printFood(){
	gotoxy(sFood.x, sFood.y);
	cout<<foodType[sFood.type];
}

void greedySnake::createFood(){
	int fx = rand()%(2*width-1)+2;
	int fy = rand()%height+1;
	if(fx%2!=0){
		fx++;
	}
	for(int i=0;i<gSnake.len;i++){
		if(fx == gSnake.body[i].x && fy == gSnake.body[i].y){
			fx = rand()%(2*width-1)+2;
			if(fx%2!=0){
				fx++;
			}
			fy = rand()%height+1;
			i=0;				
		}
	}
	sFood.x = fx;
	sFood.y = fy;
	sFood.type = rand()%8;

}

void greedySnake::runGame(){
	int op;
	init();
	while(1){
		Sleep(290 - (level-1)*30);
		if(_kbhit()){   //用来检查当前是否有键盘输入
			op = getch();
			if(op == 0xE0){        //按下方向键 
				personOperate();  //真人操作 
			} else {
				gotoxy(0, height+3);
				if(gameOpeate(op)){
					break;
				}
				gotoxy(0, height+3);
				cout<<setw(20)<<" ";
			}
		}
		move();
		printSnake();
		printFood();
		printData();
		if(!check()){
			gotoxy(0, height+3);
			cout<<"GAME OVER!"<<endl;
			cout<<"最终得分："<<score<<endl;
			if(score > mscore){
				getCoin(runningGame);
				outFile();
			}
			if(ifContinue()){
				runGame();
			}
//			show();
			break;
		}
	}
}

