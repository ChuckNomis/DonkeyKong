#include "barrel.h"
#include "utils.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "board.h"



// Handles the explosion of the barrel and checks if Mario is within the explosion radius

//Check if Hammer hit this barrel
bool barrel::hammerHitB(Pos marioPos, int dirX, int& gameScore) {
	if (dirX == -1) {
		if (_pBoard->getCharFromCurrentBoard(_pos.x + 1, _pos.y) == SpecialCharacters::MARIO ||
			_pBoard->getCharFromCurrentBoard(_pos.x + 1, _pos.y) == SpecialCharacters::MARIO_ON_LADDER ||
			_pBoard->getCharFromCurrentBoard(_pos.x + 2, _pos.y) == SpecialCharacters::MARIO ||
			_pBoard->getCharFromCurrentBoard(_pos.x + 2, _pos.y) == SpecialCharacters::MARIO_ON_LADDER) {

			setExist(false);
			resetFallCounter();
			gameScore += 100;
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
		if (_pBoard->getCharFromCurrentBoard(_pos.x - 1, _pos.y) == SpecialCharacters::MARIO ||
			_pBoard->getCharFromCurrentBoard(_pos.x - 1, _pos.y) == SpecialCharacters::MARIO_ON_LADDER ||
			_pBoard->getCharFromCurrentBoard(_pos.x - 2, _pos.y) == SpecialCharacters::MARIO ||
			_pBoard->getCharFromCurrentBoard(_pos.x - 2, _pos.y) == SpecialCharacters::MARIO_ON_LADDER) {

			setExist(false);
			resetFallCounter();
			gameScore += 100;

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

bool barrel::explode() {
	bool marioDead = false;
	setExist(false);
	resetFallCounter();

	// Display explosion effect
	for (int i = _pos.x - 2; i < _pos.x + 3; i++) {
		for (int j = _pos.y - 2; j < _pos.y + 3; j++) {
			if (i > 0 && i < 80 && j < 23) {
				gotoxy(i, j);
				std::cout << static_cast<char>(SpecialCharacters::EXPLOSION);

				// Check if Mario is hit by the explosion
				if (_pBoard->getCharFromCurrentBoard(i, j) == SpecialCharacters::MARIO)
					marioDead = true;
			}
		}
	}

	erase(); // Erase the barrel
	draw(SpecialCharacters::EXPLOSION); // Draw explosion character
	Sleep(15);

	// Restore the board to its previous state
	for (int i = _pos.x - 2; i < _pos.x + 3; i++) {
		for (int j = _pos.y - 2; j < _pos.y + 3; j++) {
			if (i > 0 && i < 80 && j < 23) {
				gotoxy(i, j);
				std::cout << (_pBoard->getCharFromCurrentBoard(i, j));
			}
		}
	}
	return marioDead;
}

// Checks if the barrel is in a falling state
bool barrel::isBarrelFalling() {
	if (_pBoard->getCharFromCurrentBoard(_pos.x, _pos.y + 1) != SpecialCharacters::FLOOR_RIGHT &&
		_pBoard->getCharFromCurrentBoard(_pos.x, _pos.y + 1) != SpecialCharacters::FLOOR_LEFT &&
		_pBoard->getCharFromCurrentBoard(_pos.x, _pos.y + 1) != SpecialCharacters::FLOOR) {
		return true;
	}
	return false;
}

// Moves the barrel based on its direction and interactions with the board
void barrel::move() {
	// Determine horizontal direction based on board indicators
	if (_pBoard->getCharFromCurrentBoard(_pos.x, _pos.y + 1) == SpecialCharacters::FLOOR_LEFT)
		_dir.x = -1;
	else if (_pBoard->getCharFromCurrentBoard(_pos.x, _pos.y + 1) == SpecialCharacters::FLOOR_RIGHT)
		_dir.x = 1;

	int newX = _pos.x + _dir.x;
	int newY = _pos.y + _dir.y;

	// Check for obstacles
	if (_pBoard->getCharFromCurrentBoard(newX, newY) == SpecialCharacters::BORDER ||
		_pBoard->getCharFromCurrentBoard(newX, newY) == SpecialCharacters::FLOOR_RIGHT ||
		_pBoard->getCharFromCurrentBoard(newX, newY) == SpecialCharacters::FLOOR_LEFT ||
		newX == 0 || newX == 79 || newY == 24 || newY == 0)
	{
		_dir = { 0, 0 }; // Stop movement
		setExist(false);
		resetFallCounter();
		erase();
	}
	else if (_pBoard->getCharFromCurrentBoard(newX, newY) == SpecialCharacters::FLOOR) {
		_dir.y = 0; // Stop vertical movement
	}
	else {
		_pos.x = newX; // Update position
		_pos.y = newY;
	}
}
