#include "barrel.h"
#include "utils.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "board.h"

void barrel::fall() {
	// Falling 
	while (pBoard->getChar(barrelPos.x, barrelPos.y + 1) != '=' &&
		pBoard->getChar(barrelPos.x, barrelPos.y + 1) != '>' &&
		pBoard->getChar(barrelPos.x, barrelPos.y + 1) != 'W' &&
		pBoard->getChar(barrelPos.x, barrelPos.y + 1) != '<') {
		erase();
		++barrelPos.y;
		draw();
		Sleep(SLEEP_DURATION);
		erase();
	} 
}


void barrel::move() {
	fall();
	if (pBoard->getChar(barrelPos.x, barrelPos.y + 1) == '<')
		dir.x = -1;
	else if (pBoard->getChar(barrelPos.x, barrelPos.y + 1) == '>')
		dir.x = 1;
	int newX = barrelPos.x + dir.x;
	int newY = barrelPos.y + dir.y;
	// Check for walls
	if (pBoard->getChar(newX, newY) == 'W' ||
		pBoard->getChar(newX, newY) == '=' ||
		pBoard->getChar(newX, newY) == '>' ||
		pBoard->getChar(newX, newY) == '<') {
		dir = { 0, 0 };
	}
	else {
		barrelPos.x = newX;
		barrelPos.y = newY;
	}
}


