#include "barrel.h"
#include "utils.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "board.h"

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


