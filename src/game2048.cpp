#include "game2048.h"
#include <iostream>
#include <cstring>
#include <ctime>
#include <conio.h>
#include <cstdlib>
#include <iomanip>
#include <fstream>

using namespace std;

void game2048::init(){
	srand((unsigned)time(NULL));	
	memset(buff, 0, sizeof(buff));
	score = 0; 
}

int game2048::check(){
	int mark = 0;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(buff[i][j] == 0)
				return 0;
			if(i-1 >= 0 && buff[i][j] == buff[i-1][j])
				return 0;
			if(j-1 >= 0 && buff[i][j] == buff[i][j-1])
				return 0;
			if(i+1 <= 3 && buff[i][j] == buff[i+1][j])
				return 0;			
			if(j+1 <= 3 && buff[i][j] == buff[i][j+1])
				return 0;		
		}
	}
	return 1;
}

void game2048::inFile(){
	ifstream in("./data/game2048.dat", ios::binary);
	if(in){
		in.read((char*)&mscore, sizeof(int));
	} 
	in.close();
}

void game2048::outFile(){
	ofstream out("./data/game2048.dat", ios::binary);
	if(out){
		out.write((char*)&score, sizeof(int));
	}
	out.close();
}

void game2048::runGame(){
	int op;
	init();
	inFile();          //������߷� 
	createRandValue();  //һ��ʼ������������� 
	createRandValue();
	while(1){
		printInterface();
		op = getch();
		if(gameOpeate(op)){
			break;
		}
		if(op == 0xE0){
			if(operate(getch())){
				createRandValue();
			}
			if(check()){
				system("cls");
				printInterface();
				cout<<"GAME OVER!!"<<endl;
				cout<<"���յ÷֣�"<<score<<endl;
				if(score > mscore){
					getCoin(runningGame);
					outFile();
				}
				if(ifContinue()){
					runGame();
				}
				break;
			}
		}
	}
	system("cls");
}

int game2048::operate(int op){
	int first,second; //��һ�͵ڶ����ϲ�����
	int empty = -1;   //��λʱ��ʱ��¼Ŀ�Ŀ�λ
	int flag = 0;     //��ǲ����Ƿ����������һЩ�ı� 
	first = second = -1;
	switch(op){
		case 0x4B:{    //�� 
			for(int i=0;i<4;i++){
				for(int j=0;j<4;j++){    //�ϲ� 
					if(buff[i][j] != 0 && first == -1){
						first = j;
					} else if(buff[i][j] != 0 && second == -1){
						second = j;
						if(buff[i][first] == buff[i][second]){
							buff[i][first] *= 2;
							buff[i][second] = 0;
							second = first = -1;
							flag = 1; 
						} else {
							first = second;
							second = -1;
						}
					}
				}
				for(int j=0;j<4;j++){    //��λ 
					if(buff[i][j] == 0 && empty == -1){
						empty = j;
					} else if(buff[i][j] != 0 && empty != -1){
						buff[i][empty] = buff[i][j];
						buff[i][j] = 0;
						j = empty;  //�ӿ�λ����һλ������ 
						empty = -1;	
						flag = 1; 
					}
				}
				first = second = empty = -1;
			}
			break;
		}
		case 0x4D:{    //�� 
			for(int i=3;i>=0;i--){
				for(int j=3;j>=0;j--){    //�ϲ� 
					if(buff[i][j] != 0 && first == -1){
						first = j;
					} else if(buff[i][j] != 0 && second == -1){
						second = j;
						if(buff[i][first] == buff[i][second]){
							buff[i][first] *= 2;
							buff[i][second] = 0;
							second = first = -1;
							flag = 1; 
						} else {
							first = second;
							second = -1;
						}
					}
				}
				for(int j=3;j>=0;j--){    //��λ 
					if(buff[i][j] == 0 && empty == -1){
						empty = j;
					} else if(buff[i][j] != 0 && empty != -1){
						buff[i][empty] = buff[i][j];
						buff[i][j] = 0;
						j = empty;  //�ӿ�λ����һλ������ 
						empty = -1;	
						flag = 1; 
					}
				}
				first = second = empty = -1;
			}
			break;
		}
		case 0x48:{    //�� 
			for(int i=0;i<4;i++){
				for(int j=0;j<4;j++){    //�ϲ� 
					if(buff[j][i] != 0 && first == -1){
						first = j;
					} else if(buff[j][i] != 0 && second == -1){
						second = j;
						if(buff[first][i] == buff[second][i]){
							buff[first][i] *= 2;
							buff[second][i] = 0;
							second = first = -1;
							flag = 1; 
						} else {
							first = second;
							second = -1;
						}					
					}
				}
				for(int j=0;j<4;j++){    //��λ 
					if(buff[j][i] == 0 && empty == -1){
						empty = j;
					} else if(buff[j][i] != 0 && empty != -1){
						buff[empty][i] = buff[j][i];
						buff[j][i] = 0;
						j = empty;  //�ӿ�λ����һλ������ 
						empty = -1;						
						flag = 1; 
					}
				}
				first = second = empty = -1;
			}
			break;
		}
		case 0x50:{    //�� 
			for(int i=3;i>=0;i--){
				for(int j=3;j>=0;j--){    //�ϲ� 
					if(buff[j][i] != 0 && first == -1){
						first = j;
					} else if(buff[j][i] != 0 && second == -1){
						second = j;
						if(buff[first][i] == buff[second][i]){
							buff[first][i] *= 2;
							buff[second][i] = 0;
							second = first = -1;
							flag = 1; 
						} else {
							first = second;
							second = -1;
						}
					}
				}
				for(int j=3;j>=0;j--){    //��λ 
					if(buff[j][i] == 0 && empty == -1){
						empty = j;
					} else if(buff[j][i] != 0 && empty != -1){
						buff[empty][i] = buff[j][i];
						buff[j][i] = 0;
						j = empty;  //�ӿ�λ����һλ������ 
						empty = -1;
						flag = 1; 
					}
				}
				first = second = empty = -1;
			}
			break;
		}
	}
	return flag;
}

void game2048::createRandValue(){
	int index = -1;
	int randKey = rand()%16;
	int randValue = rand()%4;
	if(randValue >= 2)   
		randValue = 2;
	else if(randValue < 2)
		randValue = 4;
	for(int i=randKey;i<16;i++){
		int rows = i/4;
		int cols = i%4;
		if(buff[rows][cols] == 0){
			index = i;
			break;
		}
	}
	if(index == -1){
		for(int i=randKey;i>=0;i--){
			int rows = i/4;
			int cols = i%4;
			if(buff[rows][cols] == 0){
				index = i;
				break;
			}
		}
		if(index == -1) return;     //16��λ��ȫ����ʱ�򷵻ؿ� 
	}
	buff[index/4][index%4] = randValue;
}

void game2048::printInterface(){
//	printf ("�÷֣�%d\n",mark);
	system("cls");
	cout<<"�������ש����ש����ש�����\n";
	cout<<"��"<<setw(4)<<buff[0][0]<<"��"<<setw(4)<<buff[0][1]<<"��"<<setw(4)<<buff[0][2]<<"��"<<setw(4)<<buff[0][3]<<"��"<<endl;
	cout<<"�ǩ����贈���贈���贈����\n";
	cout<<"��"<<setw(4)<<buff[1][0]<<"��"<<setw(4)<<buff[1][1]<<"��"<<setw(4)<<buff[1][2]<<"��"<<setw(4)<<buff[1][3]<<"��"<<endl;
	cout<<"�ǩ����贈���贈���贈����\n";
	cout<<"��"<<setw(4)<<buff[2][0]<<"��"<<setw(4)<<buff[2][1]<<"��"<<setw(4)<<buff[2][2]<<"��"<<setw(4)<<buff[2][3]<<"��"<<endl;
	cout<<"�ǩ����贈���贈���贈����\n";
	cout<<"��"<<setw(4)<<buff[3][0]<<"��"<<setw(4)<<buff[3][1]<<"��"<<setw(4)<<buff[3][2]<<"��"<<setw(4)<<buff[3][3]<<"��"<<endl;
	cout<<"�������ߩ����ߩ����ߩ�����\n";
	score = 0;
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			score+=buff[i][j];	
	gotoxy(30,2);
	cout<<"��ǰ�÷֣�"<<score;
	gotoxy(30,3);
	cout<<"��ߵ÷֣�"<<mscore;
	gotoxy(0,10);
}
