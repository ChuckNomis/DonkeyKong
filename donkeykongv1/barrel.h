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
	board* pBoard = nullptr;
	char ch = 'O';

	// Draw the barrel at current position
	void draw(char c) const {
		gotoxy(barrelPos.x, barrelPos.y);
		std::cout << c;
	}

public:
	// Get fall counter value
	int getFallCounter() {
		return fallCounter;
	}

	// Reset fall counter
	void resetFallCounter() {
		fallCounter = 0;
	}

	// Increase fall counter
	void increaseFallCounter() {
		fallCounter++;
	}

	// Set barrel existence status
	void setExist(bool b) {
		exist = b;
	}

	// Check if the barrel exists
	bool isExist() {
		return exist;
	}

	// Check if the barrel is on a ladder
	bool checkLadder() {
		if (pBoard->getCharFromOriginalBoard(barrelPos.x, barrelPos.y) == 'H')
			return true;
		return false;
	}

	// Set the board pointer for the barrel
	void setBarrelBoard(board& board) {
		pBoard = &board;
	}

	// Set barrel to spawn position
	void setBarrelInSpawnPos() {
		barrelPos.x = 53;
		barrelPos.y = 6;
	}

	// Erase the barrel from the board
	void erase() {
		pBoard->changePixel(barrelPos, ' ');
		draw(' ');
	}

	// Draw the barrel on the board
	void draw() const {
		pBoard->changePixel(barrelPos, 'O');
		draw(ch);
	}

	// Erase the barrel from the ladder
	void eraseOnLadder() {
		pBoard->changePixel(barrelPos, 'H');
		draw('H');
	}

	// Move the barrel
	void move();

	// Check if the barrel is falling
	bool isBarrelFalling();

	// Set vertical direction of the barrel
	void setDirY(int y) {
		dir.y = y;
	}

	// Set horizontal direction of the barrel
	void setDirX(int x) {
		dir.x = x;
	}

	// Handle barrel explosion
	bool explode();
};
