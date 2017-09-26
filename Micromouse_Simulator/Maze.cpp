#include "Maze.h"
#include "Cell.h"
#include "Wall.h"
#include "Common.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <string>
#include <list>

Maze::Maze() {}

Maze::~Maze()
{
	for (std::list<Wall*>::iterator itr = m_wallList.begin(); itr != m_wallList.end(); ++itr) {
		Wall* child = *itr;
		delete child;
	}
	m_wallList.clear();
}

void Maze::setCellWall(int i, int j, Direction ID) {
	//push wall onto a list of all walls
	Wall* tempWall = new Wall();
	m_wallList.push_back(tempWall);

	//add wall to Cell in question
	m_maze[i][j].setWall(tempWall, ID);
	//add wall to adjacent Cells that share the same wall
	switch (ID) {
	case UP:
		if (j != ROW_NUMBER - 1)
			m_maze[i][j + 1].setWall(tempWall, Direction::DOWN);
		break;
	case RIGHT:
		if (i != COLUMN_NUMBER - 1)
			m_maze[i + 1][j].setWall(tempWall, Direction::LEFT);
		return;
	}
}

void Maze::setMaze()
{
	//opens maze file
	std::ifstream mazeFile;
	mazeFile.open("maze.txt");

	//fills up wallID_arr with wallID's from text document;
	std::string currentLine;
	std::string wallID_arr[COLUMN_NUMBER][ROW_NUMBER];
	for (int j = ROW_NUMBER - 1; getline(mazeFile, currentLine) && j >= 0; --j) {
		//retrieve line data
		std::stringstream ssin(currentLine);
		//input wallID into wallID_arr
		for (int i = 0; ssin.good() && i < COLUMN_NUMBER; ++i) {
			ssin >> wallID_arr[i][j];
		}
	}

	//add walls to each cell in maze
	std::string wallID;
	for (int j = 0; j < ROW_NUMBER; ++j) {
		for (int i = 0; i < COLUMN_NUMBER; ++i) {
			wallID = wallID_arr[i][j];
			if (wallID == "U") {
				setCellWall(i, j, Direction::UP);
			}
			else if (wallID == "R") {
				setCellWall(i, j, Direction::RIGHT);
			}
			//TODO: concat this to the previous if statements
			else if (wallID == "B") {
				setCellWall(i, j, Direction::UP);
				setCellWall(i, j, Direction::RIGHT);
			}
			// if ID is '.' it means that there are no walls bordering the cell
		}
	}

	//set all the walls that were missed
	for (int j = 0; j < ROW_NUMBER; ++j)
		setCellWall(0, j, Direction::LEFT);
	for (int i = 0; i < COLUMN_NUMBER; ++i)
		setCellWall(i, 0, Direction::DOWN);

	mazeFile.close();
}

Cell* Maze::getCell(int i, int j)
{
	return &(m_maze[i][j]);
}

void Maze::printMaze(int x, int y)
{
	char mouse = '#';
	for (int j = ROW_NUMBER - 1; j > -1; --j) {
		for (int i = 0; i < COLUMN_NUMBER; ++i) {
			std::cout << "+";
			if (m_maze[i][j].getWall(Direction::UP))
				std::cout << "---";
			else
				std::cout << "   ";
		}
		std::cout << "+\n";
		for (int i = 0; i < 16; ++i)
		{
			if (m_maze[i][j].getWall(Direction::LEFT))
				std::cout << "| ";
			else
				std::cout << "  ";
			if (i == x && j == y)
				std::cout << mouse << " ";
			else
				std::cout << "  ";
		}
		std::cout << "|\n";
	}
	for (int i = 0; i < COLUMN_NUMBER; ++i)
		std::cout << "+---";
	std::cout << "+" << std::endl;
}