#pragma once
#include "board.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <filesystem>

// Menu class to handle the main menu of the game
class Menu {
public:
    // Starts the menu interaction loop
    void start();

	// Get all the file names in the screens folder
	int getAllBoardFileNames(std::vector<std::string>& vec_to_fill);

	

};