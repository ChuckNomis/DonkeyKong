#pragma once
#include "board.h"
#include "utils.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

class Enemy {


protected:

	Pos _pos;
	Direction _dir;
	board* _pBoard;
	char c;
	void draw(char c) const {
		gotoxy(_pos.x, _pos.y);
		std::cout << c;
	}
public:

	Enemy(Direction newDir, Pos newPos, board* Board, char ch) :_dir(newDir), _pos(newPos), _pBoard(Board) { c = ch; }

	void draw() {
		_pBoard->changePixelInCurrBoard(_pos, c);
		draw(c);
	}
	void erase() {
		_pBoard->changePixelInCurrBoard(_pos, SpecialCharacters::SPACE);
		draw(SpecialCharacters::SPACE);
	}
	void eraseOnLadder() {
		_pBoard->changePixelInCurrBoard(_pos, SpecialCharacters::LADDER);
		draw(SpecialCharacters::LADDER);
	}
	void eraseOnHammer() {
		_pBoard->changePixelInCurrBoard(_pos, SpecialCharacters::HAMMER);
		draw(SpecialCharacters::HAMMER);
	}
	void eraseOnKong() {
		_pBoard->changePixelInCurrBoard(_pos, SpecialCharacters::KONG);
		draw(SpecialCharacters::KONG);
	}
	void eraseOnPauline() {
		_pBoard->changePixelInCurrBoard(_pos, SpecialCharacters::PAULINE);
		draw(SpecialCharacters::PAULINE);

	}
	Pos getPos() {
		return _pos;
	}
	bool checkLadder() {
		if (_pBoard->getCharFromOriginalScreen(_pos.x, _pos.y) == SpecialCharacters::LADDER)
			return true;
		return false;
	}
	bool checkHammer() {
		if (_pBoard->getCharFromOriginalScreen(_pos.x, _pos.y) == SpecialCharacters::HAMMER)
			return true;
		return false;
	}
	bool checkPauline() {
		if (_pBoard->getCharFromOriginalScreen(_pos.x, _pos.y) == SpecialCharacters::PAULINE)
			return true;
		return false;
	}
	bool checkDkong() {
		if (_pBoard->getCharFromOriginalScreen(_pos.x, _pos.y) == SpecialCharacters::KONG)
			return true;
		return false;
	}
};
