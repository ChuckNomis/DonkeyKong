#include <iostream>
#include <windows.h>
#include <conio.h>
#include "menu.h"
#include "utils.h"
int main() {
	ShowConsoleCursor(false);
	Menu menu;
	menu.start();
}