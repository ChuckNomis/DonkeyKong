#include <iostream>
#include <windows.h>
#include <conio.h>
#include "mainGame.h"
#include "board.h"
#include "utils.h"
#include "barrel.h"
#include "barrelGroup.h"

// Main game loop
void mainGame::startGame(int screenNumber) {



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
			// Spawn a new barrel every 40 iterations
			if (gameIteration % 40 == 0) {
				_BG.spawnBarrel(barrelSum % 10);
				barrelSum++;
			}

			// Draw Mario's current state (on ladder or normal)
			if (_mario.checkLadder()) {
				_mario.drawOnLadder();
			}
			else {
				_mario.draw();
			}
			_BG.drawBarrels();

			// Check if Mario is hit by a barrel
			if (_mario.isMarioHitBarrel()) {
				marioLoseLife();
				break;
			}

			// Handle keyboard input
			if ((_kbhit()) && (jumps == 0) && fall == false && ladder == false) {
				char key = _getch();
				if (key == KeyCode::KEY_ESC) {
					pauseGame();
				}
				_mario.keyPressed(key);
				if (std::tolower(key) == KeyCode::KEY_UP && !_mario.isMarioFalling()) {
					_mario.up(jumps, ladder);
				}
				if (std::tolower(key) == KeyCode::KEY_DOWN) {
					_mario.down(downLadder, ladder);
				}
			}

			// Check Mario's ladder state
			_mario.isMarioOnLastLadder(downLadder, ladder);
			_mario.isMarioOnFirstLadder(downLadder, ladder);

			// Handle falling logic
			if (_mario.isMarioFalling() && jumps == 0 && ladder == false) {
				fall = true;
				_mario.setDirY(1);
				fallCounter++;
			}

			// Check if barrels are falling
			if (_BG.barrelsFalling()) {
				marioLoseLife();
				break;
			}

			// Stop falling when Mario lands
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

			// Erase Mario's previous position
			if (_mario.checkLadder()) {
				_mario.eraseOnLadder();
			}
			else {
				_mario.erase();
			}

			// Move Mario
			_mario.move();

			// Check win condition
			if (_mario.isMarioWin()) {
				marioWin = true;
				break;
			}

			// Check again if Mario is hit by a barrel
			if (_mario.isMarioHitBarrel()) {
				marioLoseLife();
				break;
			}

			// Move and erase barrels
			_BG.eraseBarrels();
			_BG.moveBarrels();

			// Handle jumping logic
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

	// End game states
	if (marioWin) {
		gameWin();
	}
	else {
		gameOver();
	}
}

// Display the number of lives left
void mainGame::printLifes() const {
	gotoxy(12, 2);
	std::cout << marioLifes;
}

// Pause the game until ESC is pressed again
void mainGame::pauseGame() const {
	while (true) {
		if (_kbhit()) {
			char Esc = _getch();
			if (Esc == KeyCode::KEY_ESC) {
				break;
			}
		}
	}
}

// Display the win screen
void mainGame::gameWin() {
	_board.setWin();
	_board.print();
	while (true) {
		if (_kbhit()) {
			char Esc = _getch();
			if (Esc == KeyCode::KEY_ESC) {
				break;
			}
		}
	}
}

// Display the game over screen
void mainGame::gameOver() {
	_board.setLose();
	_board.print();
	while (true) {
		if (_kbhit()) {
			char Esc = _getch();
			if (Esc == KeyCode::KEY_ESC) {
				break;
			}
		}
	}
}
