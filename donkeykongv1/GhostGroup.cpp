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
void  GhostGroup::moveGhosts() {
	for (Ghost& ghost : _ghostGroup) {
		ghost.move();
	}
}
// Draws all the ghosts on the board
void GhostGroup::drawGhosts() {
	for (Ghost& ghost : _ghostGroup) {
		ghost.draw();
	}
}
// Erases all the ghosts from the board
void GhostGroup::eraseGhosts() {
	for (Ghost& ghost : _ghostGroup) {
		if (ghost.checkLadder()) {
			ghost.eraseOnLadder();
		}
		else{
			ghost.erase();
		}
	}
}

