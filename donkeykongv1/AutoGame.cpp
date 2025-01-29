#include "AutoGame.h"
void AutoGame::startGame(int screenNumber, int numOfFiles) {
	int filesToLoad = numOfFiles - screenNumber + 1;
	bool marioWin = false;
	bool isGameOver = false;
	marioLives = 3;
	bool midExit = false;
	while (filesToLoad > 0 && !isGameOver) {
		_board.setScreen(screenNumber);
		Steps steps = Steps::loadSteps("dkong_" + std::to_string(screenNumber) + "steps.txt");
		Results results = Results::loadResults("dkong_" + std::to_string(screenNumber) + "results.txt");
		gameScore = results.getScore();
		marioLives = results.getLives();
		size_t nextDeath = results.getNextDeathIteration();
		long randomSeed = steps.getRandomSeed();
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
				if (!isSilent) {
					_board.print();
				}
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
						_mario.drawOnLadder(isSilent);
					}
					else {
						if (!isSilent) {
							_mario.draw(isSilent);
						}
					}
					if (!isSilent) {
						_BG.drawBarrels(isSilent);
						_GG.drawGhosts(isSilent);
						_BGG.drawBigGhosts(isSilent);
					}

					// Check if Mario is hit by a barrel
					if (_mario.isMarioHitBarrel()) {
						marioLoseLife();
						if (nextDeath != gameIteration) {
							system("cls");
							std::cout << "Mario death iteration " << gameIteration << " doesnt match the result death iteration " << nextDeath << std::endl;
							std::cout << "In screen " << screenNumber << std::endl;
							return;
						}
						else {
							results.popResult();
							nextDeath = results.getNextDeathIteration();
						}
						break;
					}
					// Check if mario is hit by a ghost
					if (_mario.isMarioHitGhost()) {
						marioLoseLife();
						if (nextDeath != gameIteration) {
							system("cls");
							std::cout << "Mario death iteration " << gameIteration << " doesnt match the result death iteration " << nextDeath << std::endl;
							std::cout << "In screen " << screenNumber << std::endl;
							return;
						}
						else {
							results.popResult();
							nextDeath = results.getNextDeathIteration();
						}
						break;
					}

					// Handle keyboard input
					if (steps.isNextStepOnIteration(gameIteration)) {
						char key = steps.popStep();
						if (std::tolower(key) == KeyCode::KEY_HAMMER && _mario.isHammerTime()) {
							itsHammerTime(gameScore,isSilent);
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
					_mario.isMarioOnLastLadder(downLadder, ladder, isSilent);
					_mario.isMarioOnFirstLadder(downLadder, ladder);

					// Handle falling logic
					if (_mario.isMarioFalling() && jumps == 0 && ladder == false) {
						fall = true;
						_mario.setDirY(1);
						fallCounter++;
					}

					// Check if barrels are falling
					if (_BG.barrelsFalling(isSilent)) {
						marioLoseLife();
						if (nextDeath != gameIteration) {
							system("cls");
							std::cout << "Mario death iteration " << gameIteration << " doesnt match the result death iteration " << nextDeath << std::endl;
							std::cout << "In screen " << screenNumber << std::endl;
							return;
						}
						else {
							results.popResult();
							nextDeath = results.getNextDeathIteration();
						}
						break;
					}

					// Stop falling when Mario lands
					if (!_mario.isMarioFalling() && fall == true) {
						_mario.setDirY(0);
						fall = false;
						if (fallCounter >= 5) {
							if (!isSilent) {
								_mario.draw(isSilent);
								Sleep(10);
							}
							marioLoseLife();
							if (nextDeath != gameIteration) {
								system("cls");
								std::cout << "Mario death iteration " << gameIteration << " doesnt match the result death iteration " << nextDeath << std::endl;
								std::cout << "In screen " << screenNumber << std::endl;
								return;
							}
							else {
								results.popResult();
								nextDeath = results.getNextDeathIteration();
							}
							break;
						}
						else {
							fallCounter = 0;
						}
					}
					
					Sleep(!isSilent? 30 : 0);

					// Erase Mario's previous position
					if (_mario.checkLadder()) {
						_mario.eraseOnLadder(isSilent);
					}
					else {
						_mario.erase();
					}

					// Move Mario
					_mario.move();

					_mario.checkHammer();

					// Check win condition
					if (_mario.isMarioWin()) {
						marioWin = true;
						break;
					}

					// Check again if Mario is hit by a barrel
					if (_mario.isMarioHitBarrel()) {
						marioLoseLife();
						if (nextDeath != gameIteration) {	
							system("cls");
							std::cout << "Mario death iteration " <<gameIteration<<" doesnt match the result death iteration " << nextDeath << std::endl;
							std::cout << "In screen " << screenNumber << std::endl;
							return;
						}
						else {
							results.popResult();
							nextDeath = results.getNextDeathIteration();
						}
						break;
					}
					// Check again if Mario is hit by a ghost
					if (_mario.isMarioHitGhost()) {
						
						marioLoseLife();
						if (nextDeath != gameIteration) {	
							system("cls");
							std::cout << "Mario death iteration - " << gameIteration << ", doesnt match the result death iteration - " << nextDeath << std::endl;
							std::cout << "In screen " << screenNumber << std::endl;
							return;
						}
						else {
							results.popResult();
							nextDeath = results.getNextDeathIteration();
						}
						break;
					}

					// Move and erase barrels

					_BG.eraseBarrels(isSilent);
					_GG.eraseGhosts(isSilent);
					_BGG.eraseBigGhosts(isSilent);
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
					if (nextDeath == gameIteration) {
						results.popResult();
						nextDeath = results.getNextDeathIteration();
						system("cls");
						std::cout << "Mario was supose to be dead in this iteration - " << gameIteration << std::endl;
						std::cout << "In screen " << screenNumber << std::endl;
						return;
					}
					
					if (results.isFinishedBy(gameIteration) && !results.isMoreDeaths()) {
						system("cls");
						std::cout << "Screen was supose to be finshed in this iteration  - " << gameIteration << std::endl;
						std::cout << "In screen " << screenNumber << std::endl;
						return;
					}
					gameIteration++;
				}

			}
			screenNumber++;
			filesToLoad--;
		
		}


	}
	
	_board.setEndLoad();
	_board.print();
	return;
}
