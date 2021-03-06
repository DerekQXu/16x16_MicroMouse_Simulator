#ifndef MAZE_H
#define MAZE_H

#include "Common.h"
#include "Cell.h"
#include "Wall.h"
#include <list>

class Maze
{
public:
	Maze();
    ~Maze();

	void setMaze();
	void setCellWall(int i, int j, Direction ID);

	Cell* getCell(int i, int j);
	void printMaze(int x, int y);

private:
	Cell m_maze[COLUMN_NUMBER][ROW_NUMBER];
    std::list<Wall*> m_wallList;
};

#endif // MAZE_H
