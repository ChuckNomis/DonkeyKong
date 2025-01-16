
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "mainGame.h"
#include "board.h"
#include "utils.h"
#include "barrel.h"
#include "barrelGroup.h"

// Main game loop
int mainGame::startGame(int screenNumber, int numOfFiles) {
	int filesToLoad = numOfFiles - screenNumber + 1;
	bool marioWin = false;
	bool isGameOver = false;
	marioLives = 3;
	
	while (filesToLoad > 0 && !isGameOver) {
		_board.setScreen(screenNumber);
		if (!_board.isScreenOk(screenNumber)) {
			errorScreenNotGood(screenNumber);
			screenNumber++;
			filesToLoad--;
		}
		else {

			marioWin = false;
			while (marioLives > 0 && !marioWin) {

				setALL();
				_board.setScreen(screenNumber);
				_board.print();
				legendsNeverDie(&_board);

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
					_GG.drawGhosts();

					// Check if Mario is hit by a barrel
					if (_mario.isMarioHitBarrel()) {
						marioLoseLife();
						break;
					}
					// Check if mario is hit by a ghost
					if (_mario.isMarioHitGhost()) {
						marioLoseLife();
						break;
					}

					// Handle keyboard input
					if ((_kbhit()) && (jumps == 0) && fall == false && ladder == false) {
						char key = _getch();
						if (key == KeyCode::KEY_ESC) {
							pauseGame();
						}
						if (std::tolower(key) == KeyCode::KEY_HAMMER && _mario.isHammerTime()) {
							itsHammerTime(gameScore);
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

					_mario.checkHammer();

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
					// Check again if Mario is hit by a ghost
					if (_mario.isMarioHitGhost()) {
						marioLoseLife();
						break;
					}

					// Move and erase barrels
					_BG.eraseBarrels();
					_GG.eraseGhosts();
					_BG.moveBarrels();
					_GG.moveGhosts();

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

			if (marioWin) {
				screenNumber++;
				filesToLoad--;
				gameScore += 500;
			}
			else {
				isGameOver = true;
			}
		}
		
	}
	int tempScore;
	// End game states
	if (isGameOver) {
		gameOver(gameScore);
		tempScore = gameScore;
		gameScore = 0;
		return tempScore;
	}
	else {
		gameWin(gameScore);
		tempScore = gameScore;
		gameScore = 0;
		return tempScore;
	}

}

//Switch to error screen 
void mainGame::errorScreenNotGood(int screenNumber) {
	_board.setScreenError();
	_board.print();
	gotoxy(36, 7);
	std::cout << screenNumber;
	while (true) {
		if (_kbhit()) {
			char key = _getch();
			if (key == KeyCode::KEY_ENTER) {
				break;
			}
		}
	}
}

// Display the number of lives left
void mainGame::printLives() const{
	gotoxy(12, 2);
	std::cout << marioLives;
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
void mainGame::gameWin(int const gameScore) {
	_board.setWin();
	_board.print();
	gotoxy(43, 9);
	std::cout << gameScore;
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
void mainGame::gameOver(int const gameScore) {
	_board.setLose();
	_board.print();
	gotoxy(44, 9);
	std::cout << gameScore;
	while (true) {
		if (_kbhit()) {
			char Esc = _getch();
			if (Esc == KeyCode::KEY_ESC) {
				break;
			}
		}
	}
}

// Set all game objects on the board
bool mainGame::setALL() {
	Pos donkeyKongPos = _board.searchChar(SpecialCharacters::KONG);
	if (donkeyKongPos.x == -1 || donkeyKongPos.y == -1) {
		return false;
	}
	_BG.resetAll();
	_BG.setBarrelsBoard(_board, donkeyKongPos);

	Pos marioPos = _board.searchChar(SpecialCharacters::MARIO);
	if (marioPos.x == -1 || marioPos.y == -1) {
		return false;
	}
	_mario.setMarioOnBoard(_board, marioPos);
	_mario.setDir(0, 0);

	std::vector<Pos> ghostPos = _board.getGhostsLocations();
	_GG.clearAll();
	for (Pos pos : ghostPos) {
		_GG.setGhostOnBoard(_board, pos);
	}
}


// its Hammer Time !!!
void mainGame::itsHammerTime(int& gameScore) {
	if (_BG.hammerHitBG(_mario.getMarioPos(), _mario.getDirX(), gameScore)){
		updateLegend();
	}
	if(_GG.hammerHitGG(_mario.getMarioPos(), _mario.getDirX(), gameScore)){
		updateLegend();
	}
}

void mainGame::legendsNeverDie(board* _pBoard) {
	Pos lPos = _pBoard->searchChar(SpecialCharacters::LEGEND);
	gotoxy(lPos.x, lPos.y);
	std::cout << ' ';
	lPos.y++;
	gotoxy(lPos.x, lPos.y);
	legendPos = lPos;
	std::cout << "Lives:" << marioLives << " Score:" << gameScore;
}
void mainGame::updateLegend() {
	gotoxy(legendPos.x, legendPos.y);
	std::cout << "Lives:" << marioLives << " Score:" << gameScore;
}