#pragma once
#include "board.h"
#include "barrel.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
class barrelGroup
{
	barrel _barrelGroup[10];

public:
	void setBarrelsBoard(board& board);
	void spawnBarrel(int i);
	bool barrelsFalling();
	void eraseBarrels();
	void moveBarrels();
	void drawBarrels();
	void resetAll();
};

