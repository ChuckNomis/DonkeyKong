

#include <iostream>
#include <windows.h>
#include <conio.h>
#include "utils.h"
#include "mario.h"
#include "board.h"

void mario::up(int& jumps, bool& ladder) {
	if (checkLadder()){
		dir = { 0,-1 };
		ladder = true;
	}
	else {
		if (jumps == 0) {
			dir.y = -1;
		}
		jumps++;
	}
}

void mario::down(bool& downLadder, bool& ladder) {
	if (pBoard->getCharFromCurrentBoard(marioPos.x, marioPos.y + 2) == 'H') {
		ladder = true;
		downLadder = true;
		dir = { 0,1 };
		erase();
		marioPos.y += 2;
	}
}
void mario::isMarioOnFirstLadder(bool& downLadder, bool& ladder) {
	if ((pBoard->getCharFromCurrentBoard(marioPos.x, marioPos.y + 1) == '>' ||
		pBoard->getCharFromCurrentBoard(marioPos.x, marioPos.y + 1) == '<' ||
		pBoard->getCharFromCurrentBoard(marioPos.x, marioPos.y + 1) == '=') &&
		ladder == true &&
		downLadder == true) {
		dir = { 0,0 };
		ladder = false;
		downLadder = false;
	}
}
void mario::isMarioOnLastLadder(bool& downLadder, bool& ladder) {
	if ((pBoard->getCharFromCurrentBoard(marioPos.x, marioPos.y - 1) == '>' ||
		pBoard->getCharFromCurrentBoard(marioPos.x, marioPos.y - 1) == '<' ||
		pBoard->getCharFromCurrentBoard(marioPos.x, marioPos.y - 1) == '=') &&
		ladder == true &&
		downLadder == false) {
		eraseOnLadder();
		marioPos.y -= 2;
		dir = { 0,0 };
		ladder = false;
	}
}
bool mario::isMarioFalling() {
	if (pBoard->getCharFromCurrentBoard(marioPos.x, marioPos.y + 1) != '>' &&
		pBoard->getCharFromCurrentBoard(marioPos.x, marioPos.y + 1) != '<' &&
		pBoard->getCharFromCurrentBoard(marioPos.x, marioPos.y + 1) != '=') {
		return  true;
	}
	return false;
}
bool mario::checkLadder() {
	if (pBoard->getCharFromCurrentBoard(marioPos.x, marioPos.y) == 'H')
		return true;
	return false;
}

void mario::keyPressed(char key) {
	for (size_t i = 0; i < numKeys; ++i) {
		if (std::tolower(key) == keys[i]) {
			dir = directions[i];
			return;
		}
	}
}

bool mario::isMarioHitBarrel() {
	if (pBoard->getCharFromCurrentBoard(marioPos.x, marioPos.y) == 'O') {
		return true;
	}
	return false;
}

void mario::move() {
	int newX = marioPos.x + dir.x;
	int newY = marioPos.y + dir.y;
	
	// Check for walls
	if (pBoard->getCharFromCurrentBoard(newX, newY) == 'Q'||
		pBoard->getCharFromCurrentBoard(newX, newY) == '='||
		pBoard->getCharFromCurrentBoard(newX, newY) == '>'||
		pBoard->getCharFromCurrentBoard(newX, newY) == '<') {
		dir = { 0, 0 };
	}
	else {
		marioPos.x = newX;
		marioPos.y = newY;
	}

}