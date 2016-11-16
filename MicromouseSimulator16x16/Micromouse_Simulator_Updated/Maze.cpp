#include "Maze.h"
#include "Cell.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <string>

using namespace std;

Maze::Maze() {
}

//sets a wall in between two cells
void Maze::setCellWallL(int i, int j) {
	maze[i][j].setWallL();
	if (i != 0)
		maze[i - 1][j].setWallR();
};

void Maze::setCellWallU(int i, int j) {
	maze[i][j].setWallU();
	if (j != 15)
		maze[i][j + 1].setWallD();
};

void Maze::setCellWallR(int i, int j) {
	maze[i][j].setWallR();
	if (i != 15)
		maze[i + 1][j].setWallL();
};

void Maze::setCellWallD(int i, int j) {
	maze[i][j].setWallD();
	if (j != 0)
		maze[i][j - 1].setWallU();
};

void Maze::setMaze(Cell passthrough[16][16]) {
	//opens maze file, sets a variable to be input in
	std::string txtLine;
	ifstream mazeFile;
	mazeFile.open("maze.txt");

	//creates a map of walls, and rows of walls (to be input into)
	string arrayOfWalls[16][16];
	string lineOfWalls[16];

	//starts filling up arrayOfWalls from text document
	int y = 15;
	while (getline(mazeFile, txtLine) && y > -1) {
		//retrieves line data
		stringstream ssin(txtLine);

		//creates a column array w/ all data from one line
		int i = 0;
		while (ssin.good() && i < 16) {
			ssin >> lineOfWalls[i];
			i++;
		}

		//inputs that column array into map of walls
		for (int x = 0; x < 16; x++) {
			arrayOfWalls[x][y] = lineOfWalls[x];
		}
		y--;
	}

	//creates an ID for each string;
	string ID;
	//maps the ID of wall to properties of Cells in maze array
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			ID = arrayOfWalls[i][j];
			if (ID == "|<") {
				setCellWallL(i, j);
			}
			if (ID == "_^") {
				setCellWallU(i, j);
			}
			if (ID == "|>") {
				setCellWallR(i, j);
			}
			if (ID == "_v") {
				setCellWallD(i, j);
			}
			if (ID == "Lv") {
				setCellWallU(i, j);
				setCellWallR(i, j);
			}
			if (ID == "L^") {
				setCellWallU(i, j);
				setCellWallL(i, j);
			}
			if (ID == "L<") {
				setCellWallD(i, j);
				setCellWallL(i, j);
			}
			if (ID == "L>") {
				setCellWallD(i, j);
				setCellWallR(i, j);
			}
			if (ID == "=") {
				setCellWallU(i, j);
				setCellWallD(i, j);
			}
			if (ID == "||") {
				setCellWallL(i, j);
				setCellWallR(i, j);
			}
			if (ID == "N") {
				setCellWallU(i, j);
				setCellWallL(i, j);
				setCellWallR(i, j);
			}
			if (ID == "C") {
				setCellWallU(i, j);
				setCellWallD(i, j);
				setCellWallL(i, j);
			}
			if (ID == "U") {
				setCellWallD(i, j);
				setCellWallL(i, j);
				setCellWallR(i, j);
			}
			if (ID == "J") {
				setCellWallU(i, j);
				setCellWallD(i, j);
				setCellWallR(i, j);
			}
			if (ID == ".") {}
		}
	}

	for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 16; y++) {
			passthrough[x][y] = maze[x][y];
		}
	}
	//closes maze file
	mazeFile.close();
}

Cell Maze::getCell(int i, int j) {
	//returns cell
	return maze[i][j];
}

void Maze::printMaze(int x, int y) {
	char mouse = '#';
	for (int j = 15; j > -1; j--) {
		for (int i = 0; i < 16; i++) {
			cout << "+ ";
			if (maze[i][j].getWallU() == true) {
				cout << "= ";
			}
			else {
				cout << "  ";
			}
		}
		cout << "+\n";
		for (int i = 0; i < 16; i++) {
			if (maze[i][j].getWallL() == true) {
				cout << "| ";
			}
			else {
				cout << "  ";
			}
			if (i == x && j == y) {
				cout << mouse << " ";
			}
			else {
				cout << "  ";
			}
		}
		cout << "|\n";
	}
	for (int j = 0; j < 16; j++) {
		cout << "+ = ";
	}
	cout << "+" << endl;
}
