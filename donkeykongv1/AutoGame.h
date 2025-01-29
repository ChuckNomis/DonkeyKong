#pragma once
#include "mainGame.h"
#include "Steps.h"
#include "Results.h"
class AutoGame : public mainGame
{
	bool isSilent;
public:
	// Constructor to initialize the AutoGame object
	AutoGame(bool isSilent) : isSilent(isSilent) {}
	void startGame(int screenNumber, int numOfFiles);

};

