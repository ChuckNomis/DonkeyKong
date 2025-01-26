#include "BigGhost.h"
// Moves the ghost based on its direction and interactions with the board
void BigGhost::move() {
	_dir.x *= chooseBiasedRandomDir();
	int newX = _pos.x + _dir.x;
	int newY = _pos.y + _dir.y;
	if (_dir.x!=0 &&(_pBoard->getCharFromCurrentBoard(newX, newY) == SpecialCharacters::GHOST ||
		_pBoard->getCharFromCurrentBoard(newX, newY) == SpecialCharacters::BIG_GHOST ||
		_pBoard->getCharFromCurrentBoard(newX, newY) == SpecialCharacters::BORDER||
		_pBoard->getCharFromCurrentBoard(newX, newY + 1) == SpecialCharacters::SPACE)
		){
		flipDir();
		_pos.x += _dir.x;
		_pos.y += _dir.y;
	}
	else if (_dir.x !=0 &&
		_pBoard->getCharFromCurrentBoard(newX, newY) == SpecialCharacters::LADDER && 
		(_pBoard->getCharFromCurrentBoard(newX, newY + 1) == SpecialCharacters::FLOOR ||
		_pBoard->getCharFromCurrentBoard(newX, newY + 1) == SpecialCharacters::FLOOR_LEFT ||
		_pBoard->getCharFromCurrentBoard(newX, newY + 1) == SpecialCharacters::FLOOR_RIGHT)) {
		int x = chooseBiasedRandomForClimbingLadder();
		if (x == 1) {
			_dir.y = -1;
			_pos.x += _dir.x;
			_dir.x = 0;
			_pos.y += _dir.y;
		}
		else {
			_pos.x += _dir.x;
			_pos.y += _dir.y;
		}
	}
	else if (_pBoard->getCharFromCurrentBoard(newX, newY) == SpecialCharacters::FLOOR ||
		_pBoard->getCharFromCurrentBoard(newX, newY) == SpecialCharacters::FLOOR_LEFT ||
		_pBoard->getCharFromCurrentBoard(newX, newY) == SpecialCharacters::FLOOR_RIGHT) {
		int newDirX = getRandomDirx();
		if (_dir.y == -1) {
			_dir.y = 0;
			_pos.y -= 2;
			_dir.x = newDirX;
		}
		else {
			_dir.y = 0;
			_dir.x = newDirX;
			_pos.x += _dir.x;
		}
	}
		
	else if(_dir.x!=0 &&_pBoard->getCharFromCurrentBoard(newX, newY+2) == SpecialCharacters::LADDER){
		int x = chooseBiasedRandomForClimbingLadder();
		if (x == 1) {
			_dir.y = 1;
			_pos.x += _dir.x;
			_dir.x = 0;
			_pos.y += 2;
		}
		else {
			_pos.x += _dir.x;
			_pos.y += _dir.y;
		}

	}
	else {
		_pos.x += _dir.x;
		_pos.y += _dir.y;
	}
}

int BigGhost::chooseBiasedRandomForClimbingLadder() {
	int randomValue = rand() % 100; // Generate a random number between 0 and 99
	if (randomValue < 30) {         // 95% chance for 1
		return 1;
	}
	else {                        // 5% chance for -1
		return -1;
	}
}