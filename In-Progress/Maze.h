#ifndef MAZE_H
#define MAZE_H

#define ROW_NUMBER 16
#define COLUMN_NUMBER 16
#include "Cell.h"
#include "Wall.h"
#include "Common.h"
#include <list>

class Maze
{
public:
	Maze();

	void setMaze();
	void setCellWall(int i, int j, Direction ID);

	Cell getCell(int i, int j);
	void printMaze(int x, int y);

private:
	Cell m_maze[COLUMN_NUMBER][ROW_NUMBER];
    list<Wall> m_wallList;
};

#endif // MAZE_H
