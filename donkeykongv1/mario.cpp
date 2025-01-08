#include <iostream>
#include <windows.h>
#include <conio.h>
#include "utils.h"
#include "mario.h"
#include "board.h"

// Check if Mario reaches the goal
bool mario::isMarioWin() const {
	if (pBoard->getCharFromOriginalScreen(marioPos.x, marioPos.y) == SpecialCharacters::PAULINE)
		return true;
	return false;
}

// Handles upward movement for Mario, either climbing a ladder or jumping
void mario::up(int& jumps, bool& ladder) {
	if (checkLadder()) { // If on a ladder, climb
		dir = { 0, -1 };
		ladder = true;
	}
	else {
		if (jumps == 0) { // If not on a ladder, jump
			dir.y = -1;
		}
		jumps++;
	}
}

// Handles downward movement for Mario, either descending a ladder or moving down
void mario::down(bool& downLadder, bool& ladder) {
	if (pBoard->getCharFromCurrentBoard(marioPos.x, marioPos.y + 2) == SpecialCharacters::LADDER) { // Descend a ladder
		ladder = true;
		downLadder = true;
		dir = { 0, 1 };
		erase();
		marioPos.y += 2; // Move Mario down 2 spaces
	}
}

// Check if Mario leaves the first ladder and stops descending
void mario::isMarioOnFirstLadder(bool& downLadder, bool& ladder) {
	if ((pBoard->getCharFromCurrentBoard(marioPos.x, marioPos.y + 1) == SpecialCharacters::FLOOR_RIGHT ||
		pBoard->getCharFromCurrentBoard(marioPos.x, marioPos.y + 1) == SpecialCharacters::FLOOR_LEFT ||
		pBoard->getCharFromCurrentBoard(marioPos.x, marioPos.y + 1) == SpecialCharacters::FLOOR) &&
		ladder == true && downLadder == true) {
		dir = { 0, 0 }; // Stop movement
		ladder = false;
		downLadder = false;
	}
}

// Check if Mario leaves the last ladder and stops climbing
void mario::isMarioOnLastLadder(bool& downLadder, bool& ladder) {
	if ((pBoard->getCharFromCurrentBoard(marioPos.x, marioPos.y - 1) == SpecialCharacters::FLOOR_RIGHT ||
		pBoard->getCharFromCurrentBoard(marioPos.x, marioPos.y - 1) == SpecialCharacters::FLOOR_LEFT ||
		pBoard->getCharFromCurrentBoard(marioPos.x, marioPos.y - 1) == SpecialCharacters::FLOOR) &&
		ladder == true && downLadder == false) {
		eraseOnLadder(); // Erase Mario's position on the ladder
		marioPos.y -= 2; // Move Mario up 2 spaces
		dir = { 0, 0 }; // Stop movement
		ladder = false;
	}
}

// Check if Mario is in a falling state
bool mario::isMarioFalling() const {
	if (pBoard->getCharFromCurrentBoard(marioPos.x, marioPos.y + 1) != SpecialCharacters::FLOOR_RIGHT &&
		pBoard->getCharFromCurrentBoard(marioPos.x, marioPos.y + 1) != SpecialCharacters::FLOOR_LEFT &&
		pBoard->getCharFromCurrentBoard(marioPos.x, marioPos.y + 1) != SpecialCharacters::FLOOR) {
		return true;
	}
	return false;
}

// Check if Mario is currently on a ladder
bool mario::checkLadder() const {
	if (pBoard->getCharFromCurrentBoard(marioPos.x, marioPos.y) == SpecialCharacters::LADDER)
		return true;
	return false;
}

// Process keyboard input to set Mario's direction
void mario::keyPressed(char key) {
	for (size_t i = 0; i < numKeys; ++i) {
		if (std::tolower(key) == keys[i]) {
			dir = directions[i]; // Match key with direction
			return;
		}
	}
}

// Check if Mario collides with a barrel
bool mario::isMarioHitBarrel() const {
	if (pBoard->getCharFromCurrentBoard(marioPos.x, marioPos.y) == SpecialCharacters::BARREL) {
		return true;
	}
	return false;
}
bool mario::isMarioHitGhost() const {
	if (pBoard->getCharFromCurrentBoard(marioPos.x, marioPos.y) == SpecialCharacters::GHOST) {
		return true;
	}
	return false;
}
// Move Mario based on the current direction and interact with the board
void mario::move() {
	int newX = marioPos.x + dir.x;
	int newY = marioPos.y + dir.y;

	// Check for obstacles that block movement
	if (pBoard->getCharFromCurrentBoard(newX, newY) == SpecialCharacters::BORDER ||
		pBoard->getCharFromCurrentBoard(newX, newY) == SpecialCharacters::FLOOR ||
		pBoard->getCharFromCurrentBoard(newX, newY) == SpecialCharacters::FLOOR_RIGHT ||
		pBoard->getCharFromCurrentBoard(newX, newY) == SpecialCharacters::FLOOR_LEFT ||
		pBoard->getCharFromCurrentBoard(newX, newY) == SpecialCharacters::KONG||
		newX == -1 || newX == 80 || newY == 25 || newY == -1) {
		if (dir.y != 0) {
			marioPos.y = newY; // Allow vertical movement
		}
		dir.x = 0; // Stop horizontal movement
	}
	else {
		marioPos.x = newX; // Update Mario's position
		marioPos.y = newY;
	}
}
