#pragma once
#include <iostream>
#include "utils.h" 
#include "board.h"

class barrel
{
	int fallCounter;
	bool exist;
	Pos barrelPos;
	Pos spawnPos;
	Direction dir;
	board* pBoard;
	char ch;

	// Draw the barrel at current position
	void draw(char c) const {
		gotoxy(barrelPos.x, barrelPos.y);
		std::cout << c;
	}

public:
	//Constructor
	barrel(int fallCounter = 0, bool exist = false, Pos barrelPos = { 0, 0 }, Direction dir = { 0, 0 }, board* pBoard = nullptr, char ch = SpecialCharacters::BARREL)
		: fallCounter(fallCounter), exist(exist), barrelPos(barrelPos), dir(dir), pBoard(pBoard), ch(ch) {
	}

	bool hammerHitB(Pos marioPos,int dirX);

	// Get fall counter value
	int getFallCounter() const {
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
	bool isExist() const {
		return exist;
	}

	// Check if the barrel is on a ladder
	bool checkLadder() const {
		if (pBoard->getCharFromOriginalScreen(barrelPos.x, barrelPos.y) == SpecialCharacters::LADDER)
			return true;
		return false;
	}

	bool checkDkong() const {
		if (pBoard->getCharFromOriginalScreen(barrelPos.x, barrelPos.y) == SpecialCharacters::KONG)
			return true;
		return false;
	}

	// Set the board pointer for the barrel
	void setBarrelBoard(board& board, Pos newPos) {
		pBoard = &board;
		spawnPos = newPos;
		barrelPos = newPos;
	}

	// Set barrel to spawn position
	void setBarrelInSpawnPos() {
		barrelPos = spawnPos;
	}

	// Erase the barrel from the board
	void erase() {
		pBoard->changePixel(barrelPos, SpecialCharacters::SPACE);
		draw(SpecialCharacters::SPACE);
	}

	// Draw the barrel on the board
	void draw() {
		pBoard->changePixel(barrelPos, SpecialCharacters::BARREL);
		draw(ch);
	}

	// Erase the barrel from the ladder
	void eraseOnLadder() {
		pBoard->changePixel(barrelPos, SpecialCharacters::LADDER);
		draw(SpecialCharacters::LADDER);
	}
	// Erase the barrel from the donkey kong
	void ereaseOnDkong() {
		pBoard->changePixel(barrelPos, SpecialCharacters::KONG);
		draw(SpecialCharacters::KONG);
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
