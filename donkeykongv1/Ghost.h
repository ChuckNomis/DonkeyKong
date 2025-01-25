#pragma once
#include "board.h"
#include "utils.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Enemy.h"

class Ghost : public Enemy
{
public:
	// Constructor
	Ghost(Direction newDir, Pos newPos, board* Board) : Enemy(newDir, newPos, Board, SpecialCharacters::GHOST) {}
	// Move func
	void move();
	// Checks if Hammer hit this ghost
	bool hammerHitG(Pos marioPos, int dirX);
	// Choose a Random number between 
	int chooseBiasedRandomDir();
};

