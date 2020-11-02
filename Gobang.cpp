/*
**	五子棋基本版 
*/ 

#include <iostream>
#include <cstdlib>
#include <conio.h>

using namespace std;

#define BOARD_WIDTH 16
#define BOARD_HEIGHT 16

int BOARD[BOARD_WIDTH][BOARD_HEIGHT];

int cursorX,cursorY;
int turn; 
bool over = false;

enum {
	DIRECT_UP,
	DIRECT_UP_RIGHT,
	DIRECT_UP_LEFT,
	DIRECT_RIGHT,
	DIRECT_LEFT,
	DIRECT_DOWN,
	DIRECT_DOWN_RIGHT,
	DIRECT_DOWN_LEFT,
	DIRECT_MAX
};

enum {
	COLOR_NONE = -1,
	COLOR_BLACK = 0,
	COLOR_WHITE = 1
};

int directions[][2]{
	{0,-1},		//DIRECT_UP
	{1,-1},		//DIRECT_UP_RIGHT
	{-1,-1},	//DIRECT_UP_LEFT
	{1,0},		//DIRECT_RIGHT
	{-1,0},		//DIRECT_LEFT
	{0,1},		//DIRECT_DOWN
	{1,1},		//DIRECT_DOWN_RIGHT
	{-1,1}		//DIRECT_DOWN_LEFT
};

char colorName[][5+1] = {
	"BLACK","WHITE"
};

void initialBoard(void);
void printBoard(void);

bool chkPut(int,int);

bool chkWin(int,int,int);

int main(void){
	initialBoard();
	
	while(true){
		system("cls");		//Clear Window
		printBoard();
		
		//cout << "x=" << cursorX << ",y=" << cursorY << endl;
		//cout << colorName[turn] << " turn." << endl;
		switch(getch()){
			case 'w':
				if(cursorY != 0) cursorY--;
				break;
			case 's':
				if(cursorY < BOARD_HEIGHT - 1) cursorY++;
				break;
			case 'a':
				if(cursorX != 0) cursorX--;
				break;
			case 'd':
				if(cursorX < BOARD_WIDTH - 1) cursorX++;
				break;
			case 13:
				if(chkPut(cursorX,cursorY)){
					BOARD[cursorY][cursorX] = turn;
					
					if(chkWin(cursorX,cursorY,turn)){
						system("cls");		//Clear Window
						printBoard();
						over = true;
					}
					turn ^= 1;
				}
				break;
		}
		if(over == true){
			cout << "GAME SET" << endl;
			cout << colorName[turn ^ 1] << " WIN" << endl;
			break;
		}
	}
	system("PAUSE");
	return 0;
}

void initialBoard(void){
	turn = COLOR_BLACK;
	for(int y = 0;y < BOARD_HEIGHT;y++){
		for(int x = 0;x < BOARD_WIDTH;x++){
			BOARD[y][x] = COLOR_NONE;
		}
	}
}

void printBoard(void){
	for(int y = 0;y < BOARD_HEIGHT;y++){
		for(int x = 0;x < BOARD_WIDTH;x++){
			if(x == cursorX && y == cursorY){
				cout << "◎";
			}
			else{
				switch(BOARD[y][x]){
					case -1:
						cout << "．" ;
						break;
					case 0:
						cout << "◆";
						break;
					case 1:
						cout << "◇";
						break;
				}
			}
		}
		cout << endl;
	}
}

bool chkPut(int _x,int _y){
	if(BOARD[_y][_x] == COLOR_NONE){
		return true;
	}
	return false;
}

bool chkWin(int _x,int _y,int _turn){
	cout << _x << "," << _y << endl;
	for(int i = 0;i < DIRECT_MAX;i++){
		int countChess = 1;
		int aftX,aftY;
		aftX = _x + directions[i][0];
		aftY = _y + directions[i][1];

		while(true){
			if(aftX < 0 || aftY < 0 || aftX > BOARD_WIDTH || aftY > BOARD_HEIGHT) {
				break;
			}
			if(BOARD[aftY][aftX] == COLOR_NONE || BOARD[aftY][aftX] == (_turn ^ 1)) {
				break;
			}

			countChess++;
			if(countChess == 5) return true;
			aftX += directions[i][0];
			aftY += directions[i][1];
		}
	}
	return false;
}
