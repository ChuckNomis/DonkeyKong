#include "GhostGroup.h"
#include "board.h"
#include "utils.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include "Ghost.h"

// Sets all the ghosts on the board
void GhostGroup::setGhostOnBoard(board& board, Pos ghostPos) {
	Direction ghostDir = getEvenRandomDir();
	Ghost mewGhost = Ghost(ghostDir,ghostPos, &board);
	_ghostGroup.push_back(mewGhost);
}
// Moves all the ghosts in the group
void GhostGroup::moveGhosts() {
	for (Ghost& ghost : _ghostGroup) {
		ghost.move();
	}
}
// Draws all the ghosts on the board
void GhostGroup::drawGhosts(bool isSilent) {
	for (Ghost& ghost : _ghostGroup) {
		ghost.draw(isSilent);
	}
}
// Erases all the ghosts from the board
void GhostGroup::eraseGhosts(bool isSilent) {
	for (Ghost& ghost : _ghostGroup) {
		if (ghost.checkLadder()) {
			ghost.eraseOnLadder(isSilent);
		}
		else if(ghost.checkHammer()){
			ghost.eraseOnHammer(isSilent);
		}
		else if (ghost.checkDkong()) {
			ghost.eraseOnKong(isSilent);
		}
		else if (ghost.checkPauline()) {
			ghost.eraseOnPauline(isSilent);
		}
		else {
			ghost.erase();
		}
	}
}
bool GhostGroup::hammerHitGG(Pos marioPos, int dirX, int& gameScore,bool isSilent) {
	for (auto it = _ghostGroup.begin(); it != _ghostGroup.end(); ) {
		if (it->hammerHitG(marioPos, dirX,isSilent)) {
			it = _ghostGroup.erase(it); // Erase and get the next valid iterator
			gameScore += 300;
			return true;
		}
		else {
			++it; // Move to the next element only if not erased
		}
	}
}

