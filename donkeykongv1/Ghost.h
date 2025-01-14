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
	//Constructor
	Ghost(Direction newDir, Pos newPos, board* Board) : Enemy(newDir, newPos, Board, SpecialCharacters::GHOST) {}
	
	void move();

	bool hammerHitG(Pos marioPos, int dirX);

	void flipDir() {
		_dir.x *= -1;
	}
	
	int chooseBiasedRandomDir();
};

