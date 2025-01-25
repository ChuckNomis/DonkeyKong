#include "BigGhostGroup.h"
#include "board.h"
#include "utils.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include "Ghost.h"
// Sets all the ghosts on the board
void BigGhostGroup::setBigGhostOnBoard(board& board, Pos ghostPos) {
	Direction ghostDir = getEvenRandomDir();
	BigGhost mewGhost = BigGhost(ghostDir, ghostPos, &board);
	_BigGhostGroup.push_back(mewGhost);
}
// Moves all the ghosts in the group
void  BigGhostGroup::moveBigGhosts() {
	for (BigGhost& ghost : _BigGhostGroup) {
		ghost.move();
	}
}
// Draws all the ghosts on the board
void BigGhostGroup::drawBigGhosts() {
	for (BigGhost& ghost : _BigGhostGroup) {
		ghost.draw();
	}
}
// Erases all the ghosts from the board
void BigGhostGroup::eraseBigGhosts() {
	for (BigGhost& ghost : _BigGhostGroup) {
		if (ghost.checkLadder()) {
			ghost.eraseOnLadder();
		}
		else if (ghost.checkHammer()) {
			ghost.eraseOnHammer();
		}
		else if (ghost.checkDkong()) {
			ghost.eraseOnKong();
		}
		else if (ghost.checkPauline()) {
			ghost.eraseOnPauline();
		}
		else {
			ghost.erase();
		}
	}
}


bool BigGhostGroup::hammerHitBGG(Pos marioPos, int dirX, int& gameScore) {
	for (auto it = _BigGhostGroup.begin(); it != _BigGhostGroup.end(); ) {
		if (it->hammerHitG(marioPos, dirX)) {
			it = _BigGhostGroup.erase(it); // Erase and get the next valid iterator
			gameScore += 400;
			return true;
		}
		else {
			++it; // Move to the next element only if not erased
		}
	}
}
