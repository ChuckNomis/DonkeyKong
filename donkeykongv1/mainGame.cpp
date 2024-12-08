
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "mainGame.h"
#include "board.h"
#include "utils.h"
#include "barrel.h"

void mainGame::startGame() {

	while (marioLifes > 0) {
		board.setGame();
		board.print();
		mario.setMarioOnBoard(board);
		barrel.setBarrelOnBoard(board);
		printLifes();

		int fallCounter = 0;
		int jumps=0;
		bool fall = false;
		bool ladder = false;
		bool downLadder = false;


		while (true) {
			mario.draw();
			barrel.draw();

			if (mario.isMarioHitBarrel()) {
				marioLoseLife();
				break;
			}

			if ((_kbhit()) && (jumps == 0) && fall == false && ladder == false) {
				char key = _getch();
				if (key == 27) break;
				mario.keyPressed(key);
				if (std::tolower(key) == 'w' && !mario.isMarioFalling()) {
					mario.up(jumps, ladder);
				}
				if (std::tolower(key) == 'x') {
					mario.down(downLadder,ladder);
				}
			}


			mario.isMarioOnLastLadder(downLadder,ladder);
			mario.isMarioOnFirstLadder(downLadder, ladder);


			if (mario.isMarioFalling() && jumps==0 && ladder == false) {
				fall = true;
				mario.setDirY(1);
				fallCounter++;
			}

			if (barrel.isBarrelFalling()) {
				barrel.setDirY(1);
				barrel.setDirX(0);
			}
			else {
				barrel.setDirY(0);
			
			}
			if (!mario.isMarioFalling() && fall == true) {
				mario.setDirY(0);
				fall = false;
				if (fallCounter >= 5) {
					marioLoseLife();
					break;
				}
				else {
				fallCounter = 0;
				}
			}
			Sleep(100); 

			if (mario.isMarioHitBarrel()) {
				marioLoseLife();
				break;
			}

			if (mario.checkLadder()) {
				mario.eraseOnLadder();
			}
			else {
				mario.erase();
			}

			mario.move();

			if (mario.isMarioHitBarrel()) {
				marioLoseLife();
				break;
			}


			if (barrel.checkLadder()) {
				barrel.eraseOnLadder();
			}
			else {
				barrel.erase();
			}

			barrel.move();



			if (jumps == 2) {
				jumps = 0;
				mario.setDirY(0);
			}
			if (jumps == 1) {
				jumps++;
			}
		}
	}
	
	//gameOver();
	
}
void mainGame::printLifes() {
	gotoxy(12, 2);
	std::cout << marioLifes;	
}