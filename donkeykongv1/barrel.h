#pragma once
#include <iostream>
#include "utils.h"
#include <cstring>
#include "board.h"

class barrel
{
	int fallCounter = 0;
	bool exist = false;
	Pos barrelPos{ 0, 0 };	
	Direction dir{ 0, 0 };
	board* pBoard= nullptr;
	char ch = 'O';
	void draw(char c) const {
		gotoxy(barrelPos.x, barrelPos.y);
		std::cout << c;
	}
public:
	int getFallCounter () {
		return fallCounter;
	}
	void resetFallCounter() {
		fallCounter = 0;
	}
	void increaseFallCounter() {
		fallCounter++;
	}
	void setExist(bool b) {
		exist = b;
	}
	bool isExist() {
		return exist;
	}
	bool checkLadder() {
		if (pBoard->getCharFromOriginalBoard(barrelPos.x, barrelPos.y) == 'H')
			return true;
		return false;
	}
	void setBarrelBoard(board& board) {
		pBoard = &board;
	}
	void setBarrelInSpawnPos() {
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
	void move();
	bool isBarrelFalling();
	void setDirY(int y) {
		dir.y = y;
	}
	void setDirX(int x) {
		dir.x = x;
	}
	bool explode();

};

