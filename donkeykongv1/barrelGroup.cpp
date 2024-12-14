#include "barrelGroup.h"
#include "barrel.h"
#include "utils.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "board.h"

bool barrelGroup::barrelsFalling() {
	bool deadMario = false;
	for(barrel& b : _barrelGroup) {
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
void barrelGroup::moveBarrels() {
	for (barrel& b : _barrelGroup) {
		if (b.isExist()) {
			b.move();
		}
	}
}
void barrelGroup::drawBarrels() {
	for (barrel& b : _barrelGroup) {
		if (b.isExist()) {
			b.draw();
		}
	}
}
void barrelGroup::setBarrelsBoard(board& board) {
	for (barrel& b : _barrelGroup) {
		b.setBarrelBoard(board);
	}
}
void barrelGroup::spawnBarrel(int i) {
	_barrelGroup[i].setBarrelInSpawnPos();
	_barrelGroup[i].setExist(true);
}
void barrelGroup::resetAll() {
	for (barrel& b : _barrelGroup) {
		b = barrel();
	}
}