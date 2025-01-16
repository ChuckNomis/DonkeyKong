#pragma once
#include <iostream>
#include "utils.h" 
#include "board.h"
#include "Enemy.h"

class barrel: public Enemy
{
	int fallCounter;
	bool exist;
	Pos spawnPos;


public:
	//Constructor
	barrel(int fallCounter = 0, bool exist = false, Pos newPos = { 0, 0 }, Direction newDir = { 0, 0 }, board* Board = nullptr)
		: fallCounter(fallCounter), exist(exist), Enemy(newDir, newPos, Board, SpecialCharacters::BARREL) {}

	bool hammerHitB(Pos marioPos, int dirX, int& gameScore);

	// Get fall counter value
	int getFallCounter() const {
		return fallCounter;
	}

	// Reset fall counter
	void resetFallCounter() {
		fallCounter = 0;
	}

	// Increase fall counter
	void increaseFallCounter() {
		fallCounter++;
	}

	// Set barrel existence status
	void setExist(bool b) {
		exist = b;
	}

	// Check if the barrel exists
	bool isExist() const {
		return exist;
	}

	// Set the board pointer for the barrel
	void setBarrelBoard(board& board, Pos newPos) {
		_pBoard = &board;
		spawnPos = newPos;
		_pos = newPos;
	}

	// Set barrel to spawn position
	void setBarrelInSpawnPos() {
		_pos = spawnPos;
	}

	// Move the barrel
	void move();

	// Check if the barrel is falling
	bool isBarrelFalling();

	// Set vertical direction of the barrel
	void setDirY(int y) {
		_dir.y = y;
	}

	// Set horizontal direction of the barrel
	void setDirX(int x) {
		_dir.x = x;
	}

	// Handle barrel explosion
	bool explode();
};
