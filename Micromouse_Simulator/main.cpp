#include "Common.h"
#include "MicroMouseSim.h"

//add libraries starting here
#include <iostream>
#include <queue>
#include <cstdlib>
#include <cstdint>
#include <ctime>
//and ending here

using namespace std;
MicroMouseSim world;

//add global variables starting here
int currentX;
int currentY;
Direction currentDirection;
struct mapCell
{
	bool upWall;
	bool downWall;
	bool rightWall;
	bool leftWall;
	uint16_t floodFillValue;
};

mapCell map[COLUMN_NUMBER][ROW_NUMBER];
bool discoveredCells[COLUMN_NUMBER][ROW_NUMBER];
uint16_t currentFloodFillValue;

mapCell* tempCell;
int tempX;
int tempY;

queue <mapCell*> breadthFirstSearchQ;
queue <int> tempXQ;
queue <int> tempYQ;
//and ending here

//declare functions here
void floodFillHelper()
{
	discoveredCells[tempX][tempY] = true;
	map[tempX][tempY].floodFillValue = currentFloodFillValue;
	breadthFirstSearchQ.push(&(map[tempX][tempY]));
	tempXQ.push(tempX);
	tempYQ.push(tempY);
}
void floodFill()
{
	for (int i = 0; i < COLUMN_NUMBER; ++i)
		for (int j = 0; j < ROW_NUMBER; ++j)
			discoveredCells[i][j] = false;

	discoveredCells[tempX][tempY] = true;
	tempX = COLUMN_NUMBER / 2;
	tempY = COLUMN_NUMBER / 2;
	currentFloodFillValue = 0;

	floodFillHelper();

	while (!breadthFirstSearchQ.empty())
	{
		currentFloodFillValue = (breadthFirstSearchQ.front())->floodFillValue + 1;
		tempX = tempXQ.front();
		tempY = tempYQ.front();
		breadthFirstSearchQ.pop();
		tempXQ.pop();
		tempYQ.pop();

		//for each possible direction
		if (!(map[tempX][tempY].leftWall) && !discoveredCells[tempX - 1][tempY]) {
			--tempX;
			floodFillHelper();
			++tempX;
		}
		if (!(map[tempX][tempY].downWall) && !discoveredCells[tempX][tempY - 1]) {
			--tempY;
			floodFillHelper();
			++tempY;
		}
		if (!(map[tempX][tempY].rightWall) && !discoveredCells[tempX + 1][tempY]) {
			++tempX;
			floodFillHelper();
			--tempX;
		}
		if (!(map[tempX][tempY].upWall) && !discoveredCells[tempX][tempY + 1]) {
			++tempY;
			floodFillHelper();
			--tempY;
		}
	}
}
Direction rotateRight(Direction ID)
{
	switch (ID){
	case (Direction::UP):
		return Direction::RIGHT;
	case (Direction::DOWN):
		return Direction::LEFT;
	case (Direction::RIGHT):
		return Direction::DOWN;
	case (Direction::LEFT):
		break;
	}
	return Direction::UP;
}
uint16_t getFloodFillValue(Direction ID)
{
	switch (ID) {
	case (Direction::UP):
		if (currentY == ROW_NUMBER)
			return 0xFFFF;
		return map[currentX][currentY+1].floodFillValue;
	case (Direction::DOWN):
		if (currentY == 0)
			return 0xFFFF;
		return map[currentX][currentY-1].floodFillValue;
	case (Direction::RIGHT):
		if (currentX == COLUMN_NUMBER)
			return 0xFFFF;
		return map[currentX+1][currentY].floodFillValue;
	case (Direction::LEFT):
		if (currentX == 0)
			return 0xFFFF;
		break;
	}
	return map[currentX - 1][currentY].floodFillValue;
}
Direction decideMove()
{
	floodFill();
	uint16_t min_floodFillVal = 0xFFFF;
	Direction bestMove = currentDirection;
	uint16_t tempFloodFillVal;
	for (int i = 0; i < 4; ++i){
		tempFloodFillVal = getFloodFillValue(currentDirection);
		if (min_floodFillVal > tempFloodFillVal && !world.checkWall(currentDirection)) {
			bestMove = currentDirection;
			min_floodFillVal = tempFloodFillVal;
		}
		currentDirection = rotateRight(currentDirection);
	}
	return bestMove;
}
void updateLocation(Direction ID)
{
	switch (ID) {
	case (Direction::UP):
		++currentY;
		break;
	case (Direction::DOWN):
		--currentY;
		break;
	case (Direction::RIGHT):
		++currentX;
		break;
	case (Direction::LEFT):
		--currentX;
	}
}
//and ending here

int main()
{
    cin.ignore(10000, '\n'); //removes new line if prgrm ran from terminal
	//add setup() code here
	currentDirection = Direction::UP;
	currentX = 0;
	currentY = 0;
	for (int i = 0; i < COLUMN_NUMBER; ++i)
		for (int j = 0; j < ROW_NUMBER; ++j) {
			map[i][j].upWall = false;
			map[i][j].downWall = false;
			map[i][j].rightWall = false;
			map[i][j].leftWall = false;
			if (i == COLUMN_NUMBER - 1)
				map[i][j].rightWall = true;
			if (i == 0)
				map[i][j].leftWall = true;
			if (j == ROW_NUMBER - 1)
				map[i][j].upWall = true;
			if (j == 0)
				map[i][j].downWall = true;
		}
	//and ending here

	while (!world.displayMaze())
	{
		//add loop() code here
		if (world.checkWall(Direction::UP)) {
			if (currentY != ROW_NUMBER - 1)
				map[currentX][currentY + 1].downWall = true;
			map[currentX][currentY].upWall = true;
		}
		if (world.checkWall(Direction::DOWN)) {
			if (currentY != 0)
				map[currentX][currentY - 1].upWall = true;
			map[currentX][currentY].downWall = true;
		}
		if (world.checkWall(Direction::RIGHT)) {
			if (currentX != COLUMN_NUMBER - 1)
				map[currentX + 1][currentY].leftWall = true;
			map[currentX][currentY].rightWall = true;
		}
		if (world.checkWall(Direction::LEFT)) {
			if (currentX != 0)
				map[currentX - 1][currentY].rightWall = true;
			map[currentX][currentY].leftWall = true;
		}
		currentDirection = decideMove();
		if( world.moveMouse(currentDirection) )
			updateLocation(currentDirection);
		if (world.isEnd()) {
			currentX = 0;
			currentY = 0;
			continue;
		}
		cout << "Calculated Location: (" << currentX << ", " << currentY << ")   " << endl;
        //and ending here
    }
    return 0;
}
