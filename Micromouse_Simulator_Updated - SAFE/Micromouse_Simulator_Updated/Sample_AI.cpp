#include "Sample_AI.h"
#include "Maze.h"
#include "Cell.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <string>
using namespace std;

Sample_AI::Sample_AI() {}

int Sample_AI::getX() {
	return location[0];
}
int Sample_AI::getY() {
	return location[0];
}
//stores an integer for adjacent cells in 'memory' array to remember adjacent walls
void Sample_AI::scanMaze(int memory[][MAZE_SIZE], Cell passthrough[][MAZE_SIZE]) {
	int i = location[0];
	int j = location[1];

	// 5,7,11,13 : U,D,L,R
	if (passthrough[i][j].getWallU() && j < (MAZE_SIZE - 1) && (memory[i][j] % 5) != 0)
	{
		memory[i][j] = memory[i][j] * 5;
		memory[i][j + 1] = memory[i][j + 1] * 7;
	}
	if (passthrough[i][j].getWallD() && j > 0 && (memory[i][j] % 7) != 0)
	{
		memory[i][j] = memory[i][j] * 7;
		memory[i][j - 1] = memory[i][j - 1] * 5;
	}
	if (passthrough[i][j].getWallL() && i > 0 && (memory[i][j] % 11) != 0)
	{
		memory[i][j] = memory[i][j] * 11;
		memory[i - 1][j] = memory[i - 1][j] * 13;
	}
	if (passthrough[i][j].getWallR() && i < (MAZE_SIZE-1) && (memory[i][j] % 13) != 0)
	{
		memory[i][j] = memory[i][j] * 13;
		memory[i + 1][j] = memory[i + 1][j] * 11;
	}
};

//clears everything in 'floodfill' array, except destination cells
void Sample_AI::clearMaze(int floodfill[][16]) {
	for (int i = 0; i < MAZE_SIZE; ++i)
		for (int j = 0; j < MAZE_SIZE; ++j) 
			floodfill[i][j] = -1;

	floodfill[7][7] = 0;
	floodfill[7][8] = 0;
	floodfill[8][7] = 0;
	floodfill[8][8] = 0;
}

//applies logic to see whether or not 'floodfill' cell should be stacked
void Sample_AI::setCell(int i, int j, int val, int floodfill[][MAZE_SIZE]) {
	if (i > 0 && floodfill[i - 1][j] == -1 && memory[i][j] % 11 != 0)
		floodfill[i - 1][j] = val;

	if (i < 15 && floodfill[i + 1][j] == -1 && memory[i][j] % 13 != 0)
		floodfill[i + 1][j] = val;

	if (j > 0 && floodfill[i][j - 1] == -1 && memory[i][j] % 7 != 0)
		floodfill[i][j - 1] = val;

	if (j < 15 && floodfill[i][j + 1] == -1 && memory[i][j] % 5 != 0)
		floodfill[i][j + 1] = val;
}

//recursively stacks the 'floodfill'
void Sample_AI::createMaze(int val, int target, int floodfill[][MAZE_SIZE]) {
	bool open = false;
	for (int j = MAZE_SIZE-1; j >= 0; --j)
		for (int i = 0; i < MAZE_SIZE; ++i)
			if (floodfill[i][j] == target) {
				setCell(i, j, val, floodfill);
				open = true;
			}

	if (!open)
		return;

	++val;
	++target;
	createMaze(val, target, floodfill);
}

/*gets next location with following logic:
	follow lowest floodfill number
		if direction shift, remember new orientation/direction of mouse
	if two floodfills are the same continue in same direction
	returns the new location
*/
void Sample_AI::findNewLocation(int location[], int direction[]) {
	int i = location[0];
	int j = location[1];
	bool movement[4] = { true, true, true, true };
	//UP DOWN LEFT RIGHT
	int min_value = 256;

	if (memory[i][j] % 5 == 0) {
		movement[0] = false;
	}
	if (memory[i][j] % 7 == 0) {
		movement[1] = false;
	}
	if (memory[i][j] % 11 == 0) {
		movement[2] = false;
	}
	if (memory[i][j] % 13 == 0) {
		movement[3] = false;
	}

	if (memory[i][j] % 5 != 0) {
		min_value = floodfill[i][j + 1];
	}
	else {
		movement[0] = false;
	}
	if (floodfill[i][j - 1] < min_value && memory[i][j] % 7 != 0) {
		movement[0] = false;
		min_value = floodfill[i][j - 1];
	}
	else {
		movement[1] = false;
	}
	if (floodfill[i - 1][j] < min_value && memory[i][j] % 11 != 0) {
		movement[0] = false;
		movement[1] = false;
		min_value = floodfill[i - 1][j];
	}
	else {
		movement[2] = false;
	}
	if (floodfill[i + 1][j] < min_value && memory[i][j] % 13 != 0) {
		movement[0] = false;
		movement[1] = false;
		movement[2] = false;
		min_value = floodfill[i + 1][j];
	}
	else {
		movement[3] = false;
	}

	int checker = 0;
	int turn = -1;

	for (int n = 0; n < 4; n++) {
		if (movement[n] == true) {
			checker++;
			turn = n;
		}
	}

	if (checker > 1) {
		location[0] += direction[0];
		location[1] += direction[1];
	}

	else {
		if (turn == 0) {
			location[1]++;
			direction[0] = 0;
			direction[1] = 1;
		}
		if (turn == 1) {
			location[1]--;
			direction[0] = 0;
			direction[1] = -1;
		}
		if (turn == 2) {
			location[0]--;
			direction[0] = -1;
			direction[1] = 0;
		}
		if (turn == 3) {
			location[0]++;
			direction[0] = 1;
			direction[1] = 0;
		}
	}
}

void Sample_AI::getNewLocation(Cell passthrough[][MAZE_SIZE], int& outputX, int& outputY) {
	cout << "start location: ( " << location[0] << ", " << location[1] << " )       " << endl;

	scanMaze(memory, passthrough);
	clearMaze(floodfill);
	createMaze(1, 0, floodfill);
	findNewLocation(location, direction);

	cout << "end location: ( " << location[0] << ", " << location[1] << " )       " 
		<< "\n=====================================" << endl;

	outputX = location[0];
	outputY = location[1];
}

void Sample_AI::setAI() {
	//sets up blank memory and floodfill
	for (int x = 0; x < MAZE_SIZE; x++) {
		for (int y = 0; y < MAZE_SIZE; y++) {
			memory[x][y] = 1;
			floodfill[x][y] = -1;
		}
	}

	//sets up outer edges of maze (because mouse doesn't want to leave 16x16 maze)
	for (int x = 0; x < MAZE_SIZE; x++) {
		memory[x][0] *= 7;
		memory[x][MAZE_SIZE-1] *= 5;
	}
	for (int y = 0; y < MAZE_SIZE; y++) {
		memory[0][y] *= 11;
		memory[MAZE_SIZE-1][y] *= 13;
	}

	location[0] = 0;
	location[1] = 0;
	direction[0] = 0;
	direction[1] = 1;
}

void Sample_AI::resetAI() {
	//sets up blank floodfill
	for (int x = 0; x < MAZE_SIZE; x++) {
		for (int y = 0; y < MAZE_SIZE; y++) {
			floodfill[x][y] = -1;
		}
	}

	location[0] = 0;
	location[1] = 0;
	direction[0] = 0;
	direction[1] = 1;
}
