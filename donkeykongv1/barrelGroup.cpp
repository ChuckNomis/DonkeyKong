#include "barrelGroup.h"
#include "barrel.h"
#include "utils.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "board.h"

// Checks if any barrel is falling and processes them
bool barrelGroup::barrelsFalling() {
	bool deadMario = false;
	for (barrel& b : _barrelGroup) {
		if (b.isExist()) {
			if (b.isBarrelFalling()) {
				b.increaseFallCounter();
				b.setDirY(1);
				b.setDirX(0);
			}
			else {
				if (b.getFallCounter() >= 8) {
					deadMario = (b.explode());
				}
				else {
					b.resetFallCounter();
				}
				b.setDirY(0);
			}
		}
	}
	return deadMario;
}

// Erases barrels from the board
void barrelGroup::eraseBarrels() {
	for (barrel& b : _barrelGroup) {
		if (b.isExist()) {
			if (b.checkLadder()) {
				b.eraseOnLadder();
			}
			else {
				b.erase();
			}
		}
	}
}

// Moves all the barrels in the group
void barrelGroup::moveBarrels() {
	for (barrel& b : _barrelGroup) {
		if (b.isExist()) {
			b.move();
		}
	}
}

// Draws all the barrels on the board
void barrelGroup::drawBarrels() {
	for (barrel& b : _barrelGroup) {
		if (b.isExist()) {
			b.draw();
		}
	}
}

// Sets the board for each barrel
void barrelGroup::setBarrelsBoard(board& board) {
	for (barrel& b : _barrelGroup) {
		b.setBarrelBoard(board);
	}
}

// Spawns a barrel at a specific index
void barrelGroup::spawnBarrel(int i) {
	_barrelGroup[i].setBarrelInSpawnPos();
	_barrelGroup[i].setExist(true);
}

// Resets all barrels in the group
void barrelGroup::resetAll() {
	for (barrel& b : _barrelGroup) {
		b = barrel();
	}
}
