#pragma once
#include "menu.h"
#include "mario.h"
#include "board.h"
#include "barrel.h"
class mainGame
{
	board board;
	mario mario;
	barrel barrel;
	
public:
	void startGame(); 
};

