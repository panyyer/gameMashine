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
	cout<<"���������̴�С��";
	cin>>maxm;
	system("color B0");//������ɫ
	cx = cy = maxm/2;
	now = BLACK;  //�ڷ��ȿ��� 
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
			return "��";
		else if (j==cx+1)
			return "��";
	}
	else if(i==cy+1){
		if(j==cx)
			return "��";
		else if (j==cx+1)
			return "��";
	}	
	return "��"; //������ڹ�긽����Ϊȫ�ǿո� 
}

char const* fiveChess::getTable(int i,int j){
	if(ch[i][j]==1)//1Ϊ����
	return "��";
	else if(ch[i][j]==2)//2Ϊ����
	return "��";
	else if(i==0&&j==0)//����Ϊ��Ե������ʽ
		return "��";
	else if(i==maxm-1&&j==0)
		return "��";
	else if(i==maxm-1&&j==maxm-1)
		return "��";
	else if(i==0&&j==maxm-1)
		return "��";
	else if(i==0)
		return "��";
	else if(i==maxm-1)
		return "��";
	else if(j==0)
		return "��";
	else if(j==maxm-1)
		return "��";
	return "��";//�м�Ŀ�λ
}

int fiveChess::check(){  //ʤ����飬���жϵ�ǰ����λ����û���������������
	int w=1,x=1,y=1,z=1,i;//�ۼƺ�����б��а�ĸ������������ͬ������Ŀ
	for(i=1;i<5;i++)
		if(cy+i<maxm&&ch[cx][cy+i]==now) //���¼��
			w++;
		else break;
	for(i=1;i<5;i++)
		if(cy-i>=0&&ch[cx][cy-i]==now) //���ϼ��
			w++;
		else break;
	if(w>=5)
		return now;	//�����ﵽ5�����жϵ�ǰ�������ΪӮ��
	for(i=1;i<5;i++)
		if(cx+i<maxm&&ch[cx+i][cy]==now)	 //���Ҽ��
			x++;
		else break;
	for(i=1;i<5;i++)
		if(cx-i>=0&&ch[cx-i][cy]==now) //������
			x++;
		else break;
	if(x>=5) 
		return now;
	for(i=1;i<5;i++)
		if(cx+i<maxm&&cy+i<maxm&&ch[cx+i][cy+i]==now) //�����¼��
			y++;
		else break;
	for(i=1;i<5;i++)
		if(cx-i>=0&&cy-i>=0&&ch[cx-i][cy-i]==now) //�����ϼ��
			y++;
		else break;
	if(y>=5)
		return now;
	for(i=1;i<5;i++)
		if(cx+i<maxm&&cy-i>=0&&ch[cx+i][cy-i]==now) //�����ϼ��
			z++;
		else break;
	for(i=1;i<5;i++)
		if(cx-i>=0&&cy+i<maxm&&ch[cx-i][cy+i]==now) //�����¼��
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
		op = getch();   //�Ǳ�׼���������¼�������س��Զ���ȡ 
		if(gameOpeate(op)){
			break;
		}		
		if(op == 0x20){
			if(ch[cx][cy] == 0){
				ch[cx][cy] = now;
				cnt++;
				flag = 1;
			}
			if(winner = check()){  //���ʤ��
				if(winner == BLACK)
					showText = "�ڷ�";
				else if(winner == WHITE)
					showText = "�׷�";
				printChessBoard();				
				cout<<showText<<"ֻ����"<<cnt/2+1<<"�غϾ�KO�˶��֣�"<<endl;
				if(ifContinue()){
					runGame();
				}
//				show();
				break;
			}
			else if(cnt == maxm*maxm){
				printChessBoard();
				cout<<"���˸������ã�ƽ�ָ��գ�"<<endl;
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

		else if(op == 0xE0){  //�����־ 
		
			op = getch();
			switch(op){
				case 0x4B:{cx--;break;}
				case 0x48:{cy--;break;}
				case 0x4D:{cx++;break;}
				case 0x50:{cy++;break;}
			}
			if(cx<0)cx=maxm-1;//������λ��Խ�����ƶ����Բ�
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
				write(buff[rows]+cols,"��"); 
			}
			else if(j!=maxm)//�м������
				write(buff[rows]+cols,"��");
		}
		
		if(i==maxm) //��������һ��ѭ������ֻ��Ҫ����߲��ַ�������Ҫ��һ��
			break;
		rows++;    //��һ�� 
		cols=0;
		write(buff[rows]+cols,"��");
		for(int j=0;j<maxm;j++){
			write(buff[rows]+cols,getTable(j,i)); //д�뽻���ַ�
			if(j!=maxm-1){
				write(buff[rows]+cols,"��");
			}
		}
		rows++;
		cols=0;	
	}
	system("cls");
	for(int i=0;i<maxm*2+1;i++)
		cout<<buff[i]<<endl;
	if(now == BLACK)
		cout<<"�ڷ��غ�"<<endl;
	else if(now == WHITE)
		cout<<"�׷��غ�"<<endl; 
}

