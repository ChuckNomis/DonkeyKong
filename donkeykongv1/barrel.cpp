#include "barrel.h"
#include "utils.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "board.h"


//Check if Hammer hit this barrel
bool barrel::hammerHitB(Pos marioPos, int dirX) {
	if (dirX == -1) {
		if (pBoard->getCharFromCurrentBoard(barrelPos.x + 1, barrelPos.y) == SpecialCharacters::MARIO ||
			pBoard->getCharFromCurrentBoard(barrelPos.x + 1, barrelPos.y) == SpecialCharacters::MARIO_ON_LADDER ||
			pBoard->getCharFromCurrentBoard(barrelPos.x + 2, barrelPos.y) == SpecialCharacters::MARIO ||
			pBoard->getCharFromCurrentBoard(barrelPos.x + 2, barrelPos.y) == SpecialCharacters::MARIO_ON_LADDER) {
			setExist(false);
			resetFallCounter();
			if (checkLadder()) {
				eraseOnLadder();
			}
			else if (checkHammer()) {
				eraseOnHammer();
			}
			else if (checkPauline()) {
				eraseOnPauline();
			}
			else {
				erase();
			}
			return true;
		}
	}
	else if (dirX == 1) {
		if (pBoard->getCharFromCurrentBoard(barrelPos.x - 1, barrelPos.y) == SpecialCharacters::MARIO ||
			pBoard->getCharFromCurrentBoard(barrelPos.x - 1, barrelPos.y) == SpecialCharacters::MARIO_ON_LADDER ||
			pBoard->getCharFromCurrentBoard(barrelPos.x - 2, barrelPos.y) == SpecialCharacters::MARIO ||
			pBoard->getCharFromCurrentBoard(barrelPos.x - 2, barrelPos.y) == SpecialCharacters::MARIO_ON_LADDER) {
			setExist(false);
			resetFallCounter();
			if (checkLadder()) {
				eraseOnLadder();
			}
			else if (checkHammer()) {
				eraseOnHammer();
			}
			else if (checkPauline()) {
				eraseOnPauline();
			}
			else {
				erase();
			}
			return true;
		}
	}
	return false;

}

// Handles the explosion of the barrel and checks if Mario is within the explosion radius
bool barrel::explode() {
	bool marioDead = false;
	setExist(false);
	resetFallCounter();

	// Display explosion effect
	for (int i = barrelPos.x - 2; i < barrelPos.x + 3; i++) {
		for (int j = barrelPos.y - 2; j < barrelPos.y + 3; j++) {
			if (i > 0 && i < 80 && j < 23) {
				gotoxy(i, j);
				std::cout << static_cast<char>(SpecialCharacters::EXPLOSION);

				// Check if Mario is hit by the explosion
				if (pBoard->getCharFromCurrentBoard(i, j) == SpecialCharacters::MARIO)
					marioDead = true;
			}
		}
	}

	erase(); // Erase the barrel
	draw(SpecialCharacters::EXPLOSION); // Draw explosion character
	Sleep(15);

	// Restore the board to its previous state
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

// Checks if the barrel is in a falling state
bool barrel::isBarrelFalling() {
	if (pBoard->getCharFromCurrentBoard(barrelPos.x, barrelPos.y + 1) != SpecialCharacters::FLOOR_RIGHT &&
		pBoard->getCharFromCurrentBoard(barrelPos.x, barrelPos.y + 1) != SpecialCharacters::FLOOR_LEFT &&
		pBoard->getCharFromCurrentBoard(barrelPos.x, barrelPos.y + 1) != SpecialCharacters::FLOOR) {
		return true;
	}
	return false;
}

// Moves the barrel based on its direction and interactions with the board
void barrel::move() {
	// Determine horizontal direction based on board indicators
	if (pBoard->getCharFromCurrentBoard(barrelPos.x, barrelPos.y + 1) == SpecialCharacters::FLOOR_LEFT)
		dir.x = -1;
	else if (pBoard->getCharFromCurrentBoard(barrelPos.x, barrelPos.y + 1) == SpecialCharacters::FLOOR_RIGHT)
		dir.x = 1;

	int newX = barrelPos.x + dir.x;
	int newY = barrelPos.y + dir.y;

	// Check for obstacles
	if (pBoard->getCharFromCurrentBoard(newX, newY) == SpecialCharacters::BORDER ||
		pBoard->getCharFromCurrentBoard(newX, newY) == SpecialCharacters::FLOOR_RIGHT ||
		pBoard->getCharFromCurrentBoard(newX, newY) == SpecialCharacters::FLOOR_LEFT ||
		newX == 0 || newX == 79 || newY == 24 || newY == 0)
	{
		dir = { 0, 0 }; // Stop movement
	}
	else if (pBoard->getCharFromCurrentBoard(newX, newY) == SpecialCharacters::FLOOR) {
		dir.y = 0; // Stop vertical movement
	}
	else {
		barrelPos.x = newX; // Update position
		barrelPos.y = newY;
	}
}
