#pragma once
#include <iostream>
#include "utils.h"
#include <cstring>
#include "board.h"


class mario
{
	const int SLEEP_DURATION = 50; // Duration (in milliseconds) between each step
	//if w check jump or ladder move acording 
	const int JUMP_HEIGHT = 2; // Define how high mario can jump
	static constexpr char keys[] = {'a', 'd', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);
	// the directions array order is exactly the same as the keys array - must keep it that way
	static constexpr Direction directions[] = {{-1, 0}, {1, 0},{0, 0}};

	Pos marioPos{ 18,22 };
	Direction dir { 0, 0 } ; // Starting direction: dir.x, dir.y
	char ch = '@';
	board* pBoard = nullptr;
	void draw(char c) const {
		gotoxy(marioPos.x, marioPos.y);
		std::cout << c;
	}
public:
	void draw() const {
		draw(ch);
	}
	void drawOnLadder() const {
		draw('%');
	}
	void drawChar(char c) const {
		draw(c);
	}
	void erase() {
		draw(' ');
	}
	void eraseOnLadder() {
		draw('H');
	}
	void fall();
	void up();
	bool checkLadder() {
		if (pBoard->getChar(marioPos.x, marioPos.y) == 'H')
			return true;
		return false;
	}
	void keyPressed(char key);
	void move();
	void setMarioOnBoard(board& board) {
		pBoard = &board;
		marioPos.x = 40;
		marioPos.y = 6;
		dir.x = 0;
		dir.y = 0;
	}
};