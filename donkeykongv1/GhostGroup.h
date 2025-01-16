#pragma once
#include "board.h"
#include "utils.h"
#include "Ghost.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <cstdlib> // For rand()
class GhostGroup
{
	std::vector<Ghost> _ghostGroup; // Vector to hold the ghosts


public:
	void clearAll() {
		_ghostGroup.clear();
	}
	void setGhostOnBoard(board& board, Pos newPos);
	Direction getEvenRandomDir() {
		int x = (rand() % 2 == 0) ? -1 : 1;
		return { x,0 };
	}
	void moveGhosts();
	void drawGhosts();
	void eraseGhosts();
	bool hammerHitGG(Pos marioPos, int dirX,int& gameScore);

};

