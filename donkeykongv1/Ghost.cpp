#include "Ghost.h"
// Moves the ghost based on its direction and interactions with the board
void Ghost::move(){
	_dir.x *= chooseBiasedRandomDir();
	int newX = _pos.x + _dir.x;
	int newY = _pos.y + _dir.y;
	if (_pBoard->getCharFromCurrentBoard(newX, newY) == SpecialCharacters::GHOST){
		flipDir();
	}
	else if (_pBoard->getCharFromCurrentBoard(newX, newY+1) == SpecialCharacters::SPACE) {
		flipDir();
		_pos.x += _dir.x;
		_pos.y += _dir.y;
	}
	else {
		_pos.x += _dir.x;
		_pos.y += _dir.y;
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
//Check if Hammer hit this ghost
bool Ghost::hammerHitG(Pos marioPos, int dirX) {
	if (dirX == -1) {
		if (_pBoard->getCharFromCurrentBoard(_pos.x + 1, _pos.y) == SpecialCharacters::MARIO ||
			_pBoard->getCharFromCurrentBoard(_pos.x + 1, _pos.y) == SpecialCharacters::MARIO_ON_LADDER ||
			_pBoard->getCharFromCurrentBoard(_pos.x + 2, _pos.y) == SpecialCharacters::MARIO ||
			_pBoard->getCharFromCurrentBoard(_pos.x + 2, _pos.y) == SpecialCharacters::MARIO_ON_LADDER) {


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

