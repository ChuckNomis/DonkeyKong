#pragma once
#include <iostream>
#include "utils.h"
#include <cstring>
#include "board.h"

class barrel
{
	const int SLEEP_DURATION = 50; // Duration (in milliseconds) between each step
	//if w check jump or ladder move acording 
	Pos barrelPos{ 63,6 };	
	Direction dir{ 0,0 };
	board* pBoard= nullptr;
	char ch = 'O';
	void draw(char c) const {
		gotoxy(barrelPos.x, barrelPos.y);
		pBoard->changePixel(barrelPos, 'O');
		std::cout << c;
	}
public:
	bool checkLadder() {
		if (pBoard->getChar(barrelPos.x, barrelPos.y) == 'H')
			return true;
		return false;
	}
	void setBarrelOnBoard(board& board) {
		pBoard = &board;
		barrelPos.x = 53;
		barrelPos.y = 6;
	}
	void erase() {
		pBoard->changePixel(barrelPos, ' ');
		draw(' ');
	}
	void draw() const {
		pBoard->changePixel(barrelPos, 'O');
		draw(ch);
	}
	void eraseOnLadder() {
		pBoard->changePixel(barrelPos, 'H');
		draw('H');
	}
	void fall();
	void move();
};

