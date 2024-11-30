
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "mainGame.h"
#include "board.h"
#include "utils.h"
#include "barrel.h"


void mainGame::startGame() {
	board.setGame();
	board.print();
	mario.setMarioOnBoard(board);
	barrel.setBarrelOnBoard(board);
	while (true) {
		mario.draw();
		barrel.draw();
		if (_kbhit()) {
			char key = _getch();
			if (key == 27) break;
			mario.keyPressed(key);
		}
		Sleep(100);
		
		if (mario.checkLadder()) {
			mario.eraseOnLadder();
		}
		else {
			mario.erase();
		}
		if (barrel.checkLadder()) {
			barrel.eraseOnLadder();
		}
		else {
			barrel.erase();
		}
		mario.move();
		barrel.move();
	}
}