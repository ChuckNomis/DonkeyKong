#pragma once
#include "barrelGroup.h"
#include "menu.h"
#include "mario.h"
#include "board.h"
#include "barrel.h"
#include "GhostGroup.h"
// The mainGame class manages the overall game logic and states
class mainGame
{
    int gameScore = 0;         // Game Scroe 
    int marioLives = 3;        // Tracks Mario's remaining lives
    Pos legendPos;             // The position of the legend
    board _board;              // Game board object
    mario _mario;              // Mario character object
    barrelGroup _BG;           // Group of barrels to manage barrel logic
    GhostGroup _GG;            // Group of ghosts to manage ghost logic

public:
    // Checks if Mario has no remaining lives
    bool isMarioDead() const{
        return marioLives == 0;
    }

    // Increase the Score 
    void addToScore(int const i) {
        gameScore += i;
    }

    int getGameScore() const {
        return gameScore;
    }
    // Decrements Mario's life count
    void marioLoseLife() {
        marioLives--;
    }

    // Prints the remaining lives of Mario
    void printLives() const;

    // Pauses the game until the user resumes
    void pauseGame() const;

    // Starts the main game loop
    int startGame(int screenNumber,int numOfFiles);

    // Handles the game-over state
    void gameOver(int const gameScore);

    // Handles the game-win state
    void gameWin(int const gameScore);

	// Handles the error screen state
	void errorScreenNotGood(int screenNumber);

    // Sets all game pieces
	bool setALL();

    // Checks for hammer hit on ghosts or barrels
    void itsHammerTime(int& gameScore);

    // Prints the Legend
    void legendsNeverDie(board* _pBoard);

    // Update the legend 
    void updateLegend();
};
