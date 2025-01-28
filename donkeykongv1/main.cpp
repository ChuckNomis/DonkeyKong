#include <iostream>
#include <windows.h>
#include <conio.h>
#include "menu.h"
#include "utils.h"

int main(int argc, char** argv) {
	bool isLoad = argc > 1 && std::string(argv[1]) == "-load";
	bool isSave = argc > 1 && std::string(argv[1]) == "-save";
	bool isSilent = isLoad && argc > 2 && std::string(argv[2]) == "-silent";
	// Hide the console cursor
	ShowConsoleCursor(false);

	// Create the menu and start it
	Menu menu;
	menu.start(isLoad,isSilent,isSave);
}
