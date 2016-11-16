#pragma once
#ifndef MAZE_H
#define MAZE_H
#include "Cell.h"
#include <windows.h>
#include <string>

class Maze
{
public:
	Maze();

	void setMaze(Cell passthrough[16][16]);
	void setCellWallL(int i, int j);
	void setCellWallR(int i, int j);
	void setCellWallU(int i, int j);
	void setCellWallD(int i, int j);

	Cell getCell(int i, int j);
	void printMaze(int x, int y);

protected:
	Cell maze[16][16];
};

#endif // MAZE_H
