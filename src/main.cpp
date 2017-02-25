#include "machine.h"
#include "game.h"
#include "admin.h"
#include "fiveChess.h"
#include "game2048.h"
#include "greedySnake.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	system("mode con cols=120 lines=30");
	machine m;
	fiveChess f;
	game2048 g2048;
	greedySnake s;
	game *g;
	g = &f;
	m.appendGame("五子棋", g);
	g = &g2048;
	m.appendGame("2048", g);
	g = &s;
	m.appendGame("贪吃蛇", g);
	m.readData(); 
	m.openMachine();  //开机动画 
	while(1){
		m.show();
	}
	return 0;
}
