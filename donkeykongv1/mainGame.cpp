
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "mainGame.h"
#include "board.h"
#include "utils.h"
#include "barrel.h"
#include "barrelGroup.h"


void mainGame::startGame() {

	bool marioWin = false;
	marioLifes = 3;

	while (marioLifes > 0 && !marioWin) {

		_mario.setDir(0, 0);
		_board.setGame();
		_board.print();
		_mario.setMarioOnBoard(_board);
		_BG.resetAll();
		_BG.setBarrelsBoard(_board);
		printLifes();

		int gameIteration = 0;
		int barrelSum = 0;
		int fallCounter = 0;
		int jumps = 0;
		bool fall = false;
		bool ladder = false;
		bool downLadder = false;


		while (true) {

			//Spawn barrel every 40 iterations
			if (gameIteration % 40 == 0) {
				_BG.spawnBarrel(barrelSum%10);
				barrelSum++;
			}
			if (_mario.checkLadder()) {
				_mario.drawOnLadder();
			}
			else {
				_mario.draw();
			}
			_BG.drawBarrels();

			if (_mario.isMarioHitBarrel()) {
				marioLoseLife();
				break;
			}

			if ((_kbhit()) && (jumps == 0) && fall == false && ladder == false) {
				char key = _getch();
				if (key == 27) {
					pauseGame();
				}
				_mario.keyPressed(key);
				if (std::tolower(key) == 'w' && !_mario.isMarioFalling()) {
					_mario.up(jumps, ladder);
				}
				if (std::tolower(key) == 'x') {
					_mario.down(downLadder,ladder);
				}
			}

			_mario.isMarioOnLastLadder(downLadder,ladder);
			_mario.isMarioOnFirstLadder(downLadder, ladder);



			if (_mario.isMarioFalling() && jumps==0 && ladder == false) {
				fall = true;
				_mario.setDirY(1);
				fallCounter++;
			}

			if (_BG.barrelsFalling()) {
				marioLoseLife();
				break;
			}

			if (!_mario.isMarioFalling() && fall == true) {
				_mario.setDirY(0);
				fall = false;
				if (fallCounter >= 5) {
					_mario.draw();
					Sleep(10);
					marioLoseLife();
					break;
				}
				else {
				fallCounter = 0;
				}
			}
			Sleep(100); 

		

			if (_mario.checkLadder()) {
				_mario.eraseOnLadder();
			}
			else {
				_mario.erase();
			}

			_mario.move();

			if (_mario.isMarioWin()) {
				marioWin = true;
				break;
			} 

			if (_mario.isMarioHitBarrel()) {
				marioLoseLife();
				break;
			}

			_BG.eraseBarrels();
			_BG.moveBarrels();


			if (jumps == 2) {
				jumps = 0;
				_mario.setDirY(0);
			}
			if (jumps == 1) {
				jumps++;
			}
			
			gameIteration++;
		}
	}
	if (marioWin) {
		gameWin();
	}
	else {
		gameOver();
	}

}
void mainGame::printLifes() {
	gotoxy(12, 2);
	std::cout << marioLifes;	
}
void mainGame::pauseGame() {
	while (true) {
		if (_kbhit()) {
			char Esc = _getch();
			if (Esc == 27) {
				break;
			}
		}
	}
}
void mainGame::gameWin() {
	_board.setWin();
	_board.print();
	while (true) {
		if (_kbhit()) {
			char Esc = _getch();
			if (Esc == 27) {
				break;
			}
		}
	}
}
void mainGame::gameOver() {
	_board.setLose();
	_board.print();
	while (true) {
		if (_kbhit()) {
			char Esc = _getch();
			if (Esc == 27) {
				break;
			}
		}
	}
}
