
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "mainGame.h"
#include "board.h"
#include "utils.h"


// Main game loop
void mainGame::GhostCollision() {
	for (BigGhost& _bg : _BGG._BigGhostGroup) {
		for (Ghost& _g : _GG._ghostGroup) {
			int newBGX = _bg.getPos().x + _bg.getDir().x;
			int newBGY = _bg.getPos().y + _bg.getDir().y;
			int newGX = _g.getPos().x + _g.getDir().x;
			int newGY = _g.getPos().y + _g.getDir().y;
			if (newBGX==newGX&&newBGY==newGY) {
				_bg.flipDir();
				_g.flipDir();
			}
		}
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

	std::vector<Pos> ghostPos = _board.getCharLocations(SpecialCharacters::GHOST);
	_GG.clearAll();
	for (Pos pos : ghostPos) {
		_GG.setGhostOnBoard(_board, pos);
	}

	std::vector<Pos> BigGhostPos = _board.getCharLocations(SpecialCharacters::BIG_GHOST);
	_BGG.clearAll();
	for (Pos pos : BigGhostPos) {
		_BGG.setBigGhostOnBoard(_board, pos);
	}

}
// its Hammer Time !!!
void mainGame::itsHammerTime(int& gameScore,bool isSilent) {
	if (_BG.hammerHitBG(_mario.getMarioPos(), _mario.getDirX(), gameScore, isSilent)){
		updateLegend();
	}
	if(_GG.hammerHitGG(_mario.getMarioPos(), _mario.getDirX(), gameScore, isSilent)){
		updateLegend();
	}
	if (_BGG.hammerHitBGG(_mario.getMarioPos(), _mario.getDirX(), gameScore, isSilent)) {
		updateLegend();
	}
}
// Prints the Legend
void mainGame::legendsNeverDie(board* _pBoard) {
	Pos lPos = _pBoard->searchChar(SpecialCharacters::LEGEND);
	gotoxy(lPos.x, lPos.y);
	std::cout << ' ';
	lPos.y++;
	gotoxy(lPos.x, lPos.y);
	legendPos = lPos;
	std::cout << "Lives:" << marioLives << " Score:" << gameScore;
}
// Update the legend 
void mainGame::updateLegend() {
	gotoxy(legendPos.x, legendPos.y);
	std::cout << "Lives:" << marioLives << " Score:" << gameScore;
}