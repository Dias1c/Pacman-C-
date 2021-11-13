//
//	Main.cpp
//

#include <iostream>
#include <time.h>  // clock(), time()
#include <conio.h> // _kbhit()  _getch()
#include <Windows.h>
#include <vector>
#include <string>

#include "Win10.h";
#include "Menu.h";
#include "Pacman.h";
#include "Game.cpp"; // Измени!

struct LC
{
	LC() { srand((unsigned)time(0)); }
	~LC() { system("pause > nul"); }
} _lc;

int main()
{
	ShowStartTitle(1500, "< - = PACMAN = - >", 3, 6, true);
	Game Pacman;
	Pacman.ShowMainMenu();
}