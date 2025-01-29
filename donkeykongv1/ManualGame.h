#pragma once
#include "mainGame.h"
#include "Steps.h"
#include "Results.h"
class ManualGame : public mainGame
{
	bool isSave;

public:
	// Constructor to initialize the ManualGame object
	ManualGame(bool isSave) : isSave(isSave) {}
	int startGame(int screenNumber, int numOfFiles);

};

