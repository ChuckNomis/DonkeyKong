#pragma once
#include "barrelGroup.h"
#include "menu.h"
#include "mario.h"
#include "board.h"
#include "barrel.h"
class mainGame
{
	int marioLifes = 3 ;
	board _board;
	mario _mario;
	barrel barrel;
	barrelGroup _BG;
	
public:
	bool isMarioDead() {
		return marioLifes == 0;
	}
	void marioLoseLife() {
		marioLifes--;
	}

	void printLifes();
	void pauseGame();
	void startGame(); 
	void gameOver();
	void gameWin();
};

