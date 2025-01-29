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
	Ghost(Direction newDir, Pos newPos, board* Board,char c = SpecialCharacters::GHOST) : Enemy(newDir, newPos, Board, c) {}
	// Move func
	virtual void move();
	// Checks if Hammer hit this ghost
	bool hammerHitG(Pos marioPos, int dirX,bool isSilent);
	// Choose a Random number between 
	int chooseBiasedRandomDir();
};

