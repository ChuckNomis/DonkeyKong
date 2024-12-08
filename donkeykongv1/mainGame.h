#pragma once
#include "menu.h"
#include "mario.h"
#include "board.h"
#include "barrel.h"
class mainGame
{
	int marioLifes = 3 ;
	board board;
	mario mario;
	barrel barrel;
	
public:
	bool isMarioDead() {
		return marioLifes == 0;
	}
	void marioLoseLife() {
		marioLifes--;
	}

	void printLifes();
	void startGame(); 
	void gameOver();
};

