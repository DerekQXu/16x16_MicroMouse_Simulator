#include "Maze.h"
#include "Cell.h"
#include "Sample_AI.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <string>

using namespace std;

void ShowConsoleCursor(bool showFlag);
bool isEnd(int xLocation, int yLocation);

int main()
{
	std::cout.setf(std::ios::boolalpha);

	Maze maze;
	Cell passthrough[16][16];
	maze.setMaze(passthrough);

	int XLocation = 0;
	int YLocation = 0;
	int moves = 0;

	cout << "Maze: " << endl;
	maze.printMaze(XLocation,YLocation);

	int trainCount;
	cout << "How many times do you want to run the AI?" << endl;
	cin >> trainCount;

	Sample_AI ai;
	ai.setAI();

	COORD coord; 
	coord.X = 0;
	coord.Y = 0;
	system("cls");
	for (int i = 0; i < trainCount; ++i) {
		ShowConsoleCursor(false);
		moves = 0;
		while (!isEnd(XLocation, YLocation)) {
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

			ai.getNewLocation(passthrough, XLocation, YLocation);
			maze.printMaze(XLocation, YLocation);
			cout << "\nlocation: (" << XLocation << ", " << YLocation << ")     " << endl;

			Sleep(50);
			++moves;
		}
		ShowConsoleCursor(true);
		//ai.printFinishInfo();
		cout << "end reached in " << moves << " moves."
			<< "\npress any key to continue";
		system("pause");
		XLocation = 0;
		YLocation = 0;
		ai.resetAI();
	}

	return 0;
}

bool isEnd(int xLocation, int yLocation) 
{
	if (xLocation == 7 && yLocation == 7)
		return true;
	if (xLocation == 7 && yLocation == 8)
		return true;
	if (xLocation == 8 && yLocation == 7)
		return true;
	if (xLocation == 8 && yLocation == 8)
		return true;
	return false;
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
