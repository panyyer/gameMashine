#include "fiveChess.h"
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <iostream>
#include <string.h>
#define BLACK 1
#define WHITE 2
using namespace std;


void fiveChess::init(){
	system("cls");
	cout<<"请输入棋盘大小：";
	cin>>maxm;
	system("color B0");//设置颜色
	cx = cy = maxm/2;
	now = BLACK;  //黑方先开局 
	memset(ch,0,sizeof(ch));
	memset(buff,'\0',sizeof(buff));	
}

void fiveChess::write(char *c1, char const * c2){
	cols+=strlen(c2); 
	while(*c2 != '\0')
		*c1++ = *c2++;			
}

char const* fiveChess::getCurse(int i,int j){
	if(i==cy){
		if(j==cx)
			return "┏";
		else if (j==cx+1)
			return "┓";
	}
	else if(i==cy+1){
		if(j==cx)
			return "┗";
		else if (j==cx+1)
			return "┛";
	}	
	return "　"; //如果不在光标附近则为全角空格 
}

char const* fiveChess::getTable(int i,int j){
	if(ch[i][j]==1)//1为黑子
	return "●";
	else if(ch[i][j]==2)//2为白子
	return "○";
	else if(i==0&&j==0)//以下为边缘棋盘样式
		return "┏";
	else if(i==maxm-1&&j==0)
		return "┓";
	else if(i==maxm-1&&j==maxm-1)
		return "┛";
	else if(i==0&&j==maxm-1)
		return "┗";
	else if(i==0)
		return "┣";
	else if(i==maxm-1)
		return "┫";
	else if(j==0)
		return "┳";
	else if(j==maxm-1)
		return "┻";
	return "╋";//中间的空位
}

int fiveChess::check(){  //胜负检查，即判断当前走子位置有没有造成五连珠的情况
	int w=1,x=1,y=1,z=1,i;//累计横竖正斜反邪四个方向的连续相同棋子数目
	for(i=1;i<5;i++)
		if(cy+i<maxm&&ch[cx][cy+i]==now) //向下检查
			w++;
		else break;
	for(i=1;i<5;i++)
		if(cy-i>=0&&ch[cx][cy-i]==now) //向上检查
			w++;
		else break;
	if(w>=5)
		return now;	//若果达到5个则判断当前走子玩家为赢家
	for(i=1;i<5;i++)
		if(cx+i<maxm&&ch[cx+i][cy]==now)	 //向右检查
			x++;
		else break;
	for(i=1;i<5;i++)
		if(cx-i>=0&&ch[cx-i][cy]==now) //向左检查
			x++;
		else break;
	if(x>=5) 
		return now;
	for(i=1;i<5;i++)
		if(cx+i<maxm&&cy+i<maxm&&ch[cx+i][cy+i]==now) //向右下检查
			y++;
		else break;
	for(i=1;i<5;i++)
		if(cx-i>=0&&cy-i>=0&&ch[cx-i][cy-i]==now) //向左上检查
			y++;
		else break;
	if(y>=5)
		return now;
	for(i=1;i<5;i++)
		if(cx+i<maxm&&cy-i>=0&&ch[cx+i][cy-i]==now) //向右上检查
			z++;
		else break;
	for(i=1;i<5;i++)
		if(cx-i>=0&&cy+i<maxm&&ch[cx-i][cy+i]==now) //向左下检查
			z++;
		else break;
	if(z>=5)
		return now;
	return 0;
}

void fiveChess::runGame(){
	int op,flag;
	int winner;
	int cnt=0; 
	char const* showText;
	init();
	while(1){
		printChessBoard();
		op = getch();   //非标准函数，按下键盘无需回车自动读取 
		if(gameOpeate(op)){
			break;
		}		
		if(op == 0x20){
			if(ch[cx][cy] == 0){
				ch[cx][cy] = now;
				cnt++;
				flag = 1;
			}
			if(winner = check()){  //检查胜负
				if(winner == BLACK)
					showText = "黑方";
				else if(winner == WHITE)
					showText = "白方";
				printChessBoard();				
				cout<<showText<<"只用了"<<cnt/2+1<<"回合就KO了对手！"<<endl;
				if(ifContinue()){
					runGame();
				}
//				show();
				break;
			}
			else if(cnt == maxm*maxm){
				printChessBoard();
				cout<<"两人各不相让，平局告终！"<<endl;
				if(ifContinue()){
					runGame();
				}
//				show();
				break;
			}
			if(flag == 1){
				now = now==BLACK ? WHITE : BLACK;
				flag = 0;
			}

		}

		else if(op == 0xE0){  //特殊标志 
		
			op = getch();
			switch(op){
				case 0x4B:{cx--;break;}
				case 0x48:{cy--;break;}
				case 0x4D:{cx++;break;}
				case 0x50:{cy++;break;}
			}
			if(cx<0)cx=maxm-1;//如果光标位置越界则移动到对侧
			if(cy<0)cy=maxm-1;
			if(cx>maxm-1)cx=0;
			if(cy>maxm-1)cy=0;			
		}
	}
	system("cls");

}

void fiveChess::printChessBoard(){
	rows = cols = 0;
	for(int i=0;i<=maxm;i++){
		for(int j=0;j<=maxm;j++){
			write(buff[rows]+cols, getCurse(i,j));
			if(i==0 || i==maxm){
				if(j!=maxm)
				write(buff[rows]+cols,"　"); 
			}
			else if(j!=maxm)//中间的竖线
				write(buff[rows]+cols,"┃");
		}
		
		if(i==maxm) //如果是最后一次循环，则只需要处理边侧字符，交点要少一排
			break;
		rows++;    //下一行 
		cols=0;
		write(buff[rows]+cols,"　");
		for(int j=0;j<maxm;j++){
			write(buff[rows]+cols,getTable(j,i)); //写入交点字符
			if(j!=maxm-1){
				write(buff[rows]+cols,"━");
			}
		}
		rows++;
		cols=0;	
	}
	system("cls");
	for(int i=0;i<maxm*2+1;i++)
		cout<<buff[i]<<endl;
	if(now == BLACK)
		cout<<"黑方回合"<<endl;
	else if(now == WHITE)
		cout<<"白方回合"<<endl; 
}

