#include "Ghost.h"

// Moves the ghost based on its direction and interactions with the board
void Ghost::move(){
	_ghostDir.x *= chooseBiasedRandomDir();
	int newX = _ghostPos.x + _ghostDir.x;
	int newY = _ghostPos.y + _ghostDir.y;

	if (_pBoard->getCharFromCurrentBoard(newX, newY+1) == SpecialCharacters::SPACE) {
		flipDir();
		_ghostPos.x += _ghostDir.x;
		_ghostPos.y += _ghostDir.y;
	}
	else {
		_ghostPos.x += _ghostDir.x;
		_ghostPos.y += _ghostDir.y;
	}
}
// Chooses a biased random direction for the ghost
int Ghost::chooseBiasedRandomDir() {
	int randomValue = rand() % 100; // Generate a random number between 0 and 99
	if (randomValue < 95) {         // 95% chance for 1
		return 1;
	}
	else {                        // 5% chance for -1
		return -1;
	}
}
