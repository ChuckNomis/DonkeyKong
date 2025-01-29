#include "ManualGame.h"

int ManualGame::startGame(int screenNumber, int numOfFiles) {
	int filesToLoad = numOfFiles - screenNumber + 1;
	bool marioWin = false;
	bool isGameOver = false;
	marioLives = 3;

	while (filesToLoad > 0 && !isGameOver) {
		_board.setScreen(screenNumber);
		long randomSeed;
		randomSeed = static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count());
		Steps steps;
		Results results;
		results.changeLives(marioLives);
		steps.setRandomSeed(randomSeed);
		if (!_board.isScreenOk(screenNumber)) {
			errorScreenNotGood(screenNumber);
			screenNumber++;
			filesToLoad--;
		}
		else {
			marioWin = false;
			while (marioLives > 0 && !marioWin) {
				setALL();
				_board.setScreen(screenNumber);
				_board.print();
				legendsNeverDie(&_board);

				int gameIteration = 0;
				int barrelSum = 0;
				int fallCounter = 0;
				int jumps = 0;
				bool fall = false;
				bool ladder = false;
				bool downLadder = false;

				while (true) {
					// Spawn a new barrel every 40 iterations
					if (gameIteration % 40 == 0) {
						_BG.spawnBarrel(barrelSum % 10);
						barrelSum++;
					}

					// Draw Mario's current state (on ladder or normal)
					if (_mario.checkLadder()) {
						_mario.drawOnLadder(false);
					}
					else {
						_mario.draw(false);
					}
					_BG.drawBarrels(false);
					_GG.drawGhosts(false);
					_BGG.drawBigGhosts(false);

					// Check if Mario is hit by a barrel
					if (_mario.isMarioHitBarrel()) {
						marioLoseLife();
						results.addResult(gameIteration, Results::loseLife);
						break;
					}
					// Check if mario is hit by a ghost
					if (_mario.isMarioHitGhost()) {
						marioLoseLife();
						results.addResult(gameIteration, Results::loseLife);
						break;
					}

					// Handle keyboard input
					if ((_kbhit()) && (jumps == 0) && fall == false && ladder == false) {
						char key = _getch();
						if (isSave) {
							steps.addStep(gameIteration, key);
						}
						if (key == KeyCode::KEY_ESC) {
							pauseGame();
						}
						if (std::tolower(key) == KeyCode::KEY_HAMMER && _mario.isHammerTime()) {
							itsHammerTime(gameScore, false);
						}
						_mario.keyPressed(key);
						if (std::tolower(key) == KeyCode::KEY_UP && !_mario.isMarioFalling()) {
							_mario.up(jumps, ladder);

						}
						if (std::tolower(key) == KeyCode::KEY_DOWN) {
							_mario.down(downLadder, ladder);
						}
					}

					// Check Mario's ladder state
					_mario.isMarioOnLastLadder(downLadder, ladder, false);
					_mario.isMarioOnFirstLadder(downLadder, ladder);

					// Handle falling logic
					if (_mario.isMarioFalling() && jumps == 0 && ladder == false) {
						fall = true;
						_mario.setDirY(1);
						fallCounter++;
					}

					// Check if barrels are falling
					if (_BG.barrelsFalling(false)) {
						marioLoseLife();
						results.addResult(gameIteration, Results::loseLife);
						break;
					}

					// Stop falling when Mario lands
					if (!_mario.isMarioFalling() && fall == true) {
						_mario.setDirY(0);
						fall = false;
						if (fallCounter >= 5) {
							_mario.draw(false);
							Sleep(10);
							marioLoseLife();
							results.addResult(gameIteration, Results::loseLife);
							break;
						}
						else {
							fallCounter = 0;
						}
					}
					Sleep(100);

					// Erase Mario's previous position
					if (_mario.checkLadder()) {
						_mario.eraseOnLadder(false);
					}
					else {
						_mario.erase();
					}

					// Move Mario
					_mario.move();

					_mario.checkHammer();

					// Check win condition
					if (_mario.isMarioWin()) {
						results.addResult(gameIteration, Results::finished);
						marioWin = true;
						break;
					}

					// Check again if Mario is hit by a barrel
					if (_mario.isMarioHitBarrel()) {
						results.addResult(gameIteration, Results::loseLife);
						marioLoseLife();
						break;
					}
					// Check again if Mario is hit by a ghost
					if (_mario.isMarioHitGhost()) {
						results.addResult(gameIteration, Results::loseLife);
						marioLoseLife();
						break;
					}

					// Move and erase barrels

					_BG.eraseBarrels(false);
					_GG.eraseGhosts(false);
					_BGG.eraseBigGhosts(false);
					GhostCollision();
					_BG.moveBarrels();
					_GG.moveGhosts();
					_BGG.moveBigGhosts();

					// Handle jumping logic
					if (jumps == 2) {
						jumps = 0;
						_mario.setDirY(0);
					}
					if (jumps == 1) {
						jumps++;
					}

					gameIteration++;
				}
			}
			if (isSave) {
				steps.saveSteps("dkong_" + std::to_string(screenNumber) + "steps.txt");
				if (marioWin) {
					results.changeScore(gameScore + 500);
				}
				else {
					results.changeScore(gameScore);
				}
				results.saveResults("dkong_" + std::to_string(screenNumber) + "results.txt");
			}
			
			if (marioWin) {
				screenNumber++;
				filesToLoad--;
				gameScore += 500;
			}
			else {
				isGameOver = true;
			}
		}

	}
	int tempScore;
	// End game states
	if (isGameOver) {
		gameOver(gameScore);
		tempScore = gameScore;
		gameScore = 0;
		return tempScore;
	}
	else {
		gameWin(gameScore);
		tempScore = gameScore;
		gameScore = 0;
		return tempScore;
	}

}