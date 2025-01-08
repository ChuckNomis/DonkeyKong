#pragma once
#include "board.h"
#include "utils.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

class Ghost
{

	Pos _ghostPos;
	Direction _ghostDir;
	board* _pBoard;

	void draw(char c) const {
		gotoxy(_ghostPos.x, _ghostPos.y);
		std::cout << c;
	}
public:
	//Constructor
	Ghost(Direction newDir,Pos newPos, board* Board): _ghostDir(newDir), _pBoard(Board),_ghostPos(newPos) {}

	void move();
	void draw() {
		_pBoard->changePixel(_ghostPos, SpecialCharacters::GHOST);
		draw(SpecialCharacters::GHOST);
	}
	void erase() {
		_pBoard->changePixel(_ghostPos, SpecialCharacters::SPACE);
		draw(SpecialCharacters::SPACE);
	}
	void eraseOnLadder() {
		_pBoard->changePixel(_ghostPos, SpecialCharacters::LADDER);
		draw(SpecialCharacters::LADDER);
	}
	Pos getPos() {
		return _ghostPos;
	}
	void flipDir() {
		_ghostDir.x *= -1;
	}
	bool checkLadder() {
		if (_pBoard->getCharFromOriginalScreen(_ghostPos.x, _ghostPos.y) == SpecialCharacters::LADDER)
			return true;
		return false;
	}
	int chooseBiasedRandomDir();
};

