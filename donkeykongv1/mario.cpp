

#include <iostream>
#include <windows.h>
#include <conio.h>
#include "utils.h"
#include "mario.h"
#include "board.h"

void mario::up() {
	
	if (pBoard->getChar(marioPos.x, marioPos.y) == 'H') {
		while (pBoard->getChar(marioPos.x, marioPos.y) == 'H') {
			eraseOnLadder();
			marioPos.y -= 1;
			drawOnLadder();
			Sleep(SLEEP_DURATION);
		}
		erase();
		draw(pBoard->getChar(marioPos.x, marioPos.y));
		marioPos.y -= 1;
		draw();
		dir = { 0,0 };
	}
	else {
		// Simulate upward motion
		for (int i = 0; i < JUMP_HEIGHT; ++i) {
			if (pBoard->getChar(marioPos.x, marioPos.y - 1) == 'W' ||
				pBoard->getChar(marioPos.x, marioPos.y - 1) == '>' ||
				pBoard->getChar(marioPos.x, marioPos.y - 1) == '=' ||
				pBoard->getChar(marioPos.x, marioPos.y - 1) == '<') { // Check if mario hits a ceiling
				break;
			}
			erase();
			--marioPos.y; // Move up
			draw();
			Sleep(SLEEP_DURATION);
		}
	}
}
void mario::fall() {
	// Falling 
	while (pBoard->getChar(marioPos.x + dir.x, marioPos.y + 1) != '=' &&
		pBoard->getChar(marioPos.x + dir.x, marioPos.y + 1) != '>' &&
		pBoard->getChar(marioPos.x + dir.x, marioPos.y + 1) != 'W' &&
		pBoard->getChar(marioPos.x + dir.x, marioPos.y + 1) != '<') { // Check if mario hits the ground
		if (checkLadder()) {
			eraseOnLadder();
		}
		else {
			erase();
		}
		++marioPos.y; // Move down
		marioPos.x += dir.x;
		draw();
		Sleep(SLEEP_DURATION);
		if (checkLadder()) {
			eraseOnLadder();
		}
		else {
			erase();
		}
	}
}
void mario::keyPressed(char key) {
	for (size_t i = 0; i < numKeys; ++i) {
		if (std::tolower(key) == keys[i]) {
			dir = directions[i];
			return;
		}
	}
	if (std::tolower(key) == 'w') { // 'w' for jump
		up();
	}
}
void mario::move() {
	fall();
	int newX = marioPos.x + dir.x;
	int newY = marioPos.y + dir.y;
	
	// Check for walls
	if (pBoard->getChar(newX, newY) == 'W'||
		pBoard->getChar(newX, newY) == '='||
		pBoard->getChar(newX, newY) == '>'||
		pBoard->getChar(newX, newY) == '<') {
		dir = { 0, 0 };
	}
	else {
		marioPos.x = newX;
		marioPos.y = newY;
	}

}