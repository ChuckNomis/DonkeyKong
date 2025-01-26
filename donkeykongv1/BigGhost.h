#pragma once
#include "board.h"
#include "utils.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Ghost.h"
class BigGhost : public Ghost
{
public:
	// Constructor
	BigGhost(Direction newDir, Pos newPos, board* Board): Ghost(newDir, newPos, Board,SpecialCharacters::BIG_GHOST){}
	// Move func
	virtual void move();
	// Choosing a biased random direction for the ghost
	int chooseBiasedRandomForClimbingLadder();
};

