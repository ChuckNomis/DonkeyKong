#include <iostream>
#include <windows.h>
#include <conio.h>
#include "menu.h"
#include "utils.h"

int main() {
	// Hide the console cursor
	ShowConsoleCursor(false);

	// Create the menu and start it
	Menu menu;
	menu.start();
}
