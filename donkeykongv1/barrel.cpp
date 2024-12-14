#include "barrel.h"
#include "utils.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "board.h"

bool barrel::explode() {
	bool marioDead = false;
	setExist(false);
	resetFallCounter();
	for (int i = barrelPos.x - 2; i < barrelPos.x + 3; i++) {
		for (int j = barrelPos.y - 2; j < barrelPos.y + 3; j++) {
			if ( i > 0 && i < 80 && j < 23) {
				gotoxy(i, j);
				std::cout << 'X';
				if (pBoard->getCharFromCurrentBoard(i, j) == '@')
					marioDead = true;
			}
		}
	}
	erase();
	draw('X');
	Sleep(15);
	for (int i = barrelPos.x - 2; i < barrelPos.x + 3; i++) {
		for (int j = barrelPos.y - 2; j < barrelPos.y + 3; j++) {
			if (i > 0 && i < 80 && j < 23) {
				gotoxy(i, j);
				std::cout << (pBoard->getCharFromCurrentBoard(i, j));
			}
		}
	}
	return marioDead;
}


bool barrel::isBarrelFalling() {
	if (pBoard->getCharFromCurrentBoard(barrelPos.x, barrelPos.y + 1) != '>' &&
		pBoard->getCharFromCurrentBoard(barrelPos.x, barrelPos.y + 1) != '<' &&
		pBoard->getCharFromCurrentBoard(barrelPos.x, barrelPos.y + 1) != '=') {
		return  true;
	}
	return false;
}

void barrel::move() {
	if (pBoard->getCharFromCurrentBoard(barrelPos.x, barrelPos.y + 1) == '<')
		dir.x = -1;
	else if (pBoard->getCharFromCurrentBoard(barrelPos.x, barrelPos.y + 1) == '>')
		dir.x = 1;
	int newX = barrelPos.x + dir.x;
	int newY = barrelPos.y + dir.y;
	// Check for walls
	if (pBoard->getCharFromCurrentBoard(newX, newY) == 'Q' ||
		pBoard->getCharFromCurrentBoard(newX, newY) == '=' ||
		pBoard->getCharFromCurrentBoard(newX, newY) == '>' ||
		pBoard->getCharFromCurrentBoard(newX, newY) == '<') {
		dir = { 0, 0 };
	}
	else {
		barrelPos.x = newX;
		barrelPos.y = newY;
	}
}


