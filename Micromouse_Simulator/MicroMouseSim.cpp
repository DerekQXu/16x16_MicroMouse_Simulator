#include "Maze.h"
#include "Cell.h"
#include "Common.h"
#include "MicroMouseSim.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>

//sets up constants and maze; gets ready to print to console
MicroMouseSim::MicroMouseSim()
{
	std::cout.setf(std::ios::boolalpha);

	maze.setMaze();
	m_mouseX = 0;
	m_mouseY = 0;
	m_moves = 0;
	m_trainCount = 0;
	m_moveLock = false;

	maze.printMaze(m_mouseX, m_mouseY);
	std::cout << "How many times would you like to run the AI?" << std::endl;
	std::cin >> m_maxTrainCount;
}

//returns true if there is a wall in the direction indicated from (m_mouseX, m_mouseY) coordinate
bool MicroMouseSim::checkWall(Direction ID)
{
	return maze.getCell(m_mouseX, m_mouseY)->getWall(ID);
}

//helper function to see if wall is blocking attempted move direction
bool MicroMouseSim::canMove(Direction ID)
{
	switch (ID)
	{
	case UP:
		if (maze.getCell(m_mouseX, m_mouseY)->getWall(Direction::UP))
			return false;
		break;
	case DOWN:
		if (maze.getCell(m_mouseX, m_mouseY)->getWall(Direction::DOWN))
			return false;
		break;
	case RIGHT:
		if (maze.getCell(m_mouseX, m_mouseY)->getWall(Direction::RIGHT))
			return false;
		break;
	case LEFT:
		if (maze.getCell(m_mouseX, m_mouseY)->getWall(Direction::LEFT))
			return false;
		break;
	}
	return true;
}

//returns true if the mouse moved
bool MicroMouseSim::moveMouse(Direction ID)
{
	//exit function if mouse has already attempted move or had an invalid move
	if (m_moveLock)
		return false;
	if (!canMove(ID)) {
		++m_moves;
		m_moveLock = true;
		return false;
	}
	//physically move the mouse
	switch (ID)
	{
	case UP:
		++m_mouseY;
		break;
	case DOWN:
		--m_mouseY;
		break;
	case RIGHT:
		++m_mouseX;
		break;
	case LEFT:
		--m_mouseX;
		break;
	}
	++m_moves;
	m_moveLock = true;
	return true;
}

//returns true if specified train count is over
bool MicroMouseSim::displayMaze()
{
	//after train count is over
	if (m_trainCount == m_maxTrainCount)
		return true;

	//moves mouse
	showConsoleCursor(false);
	clearScreen();

	//prints maze
	maze.printMaze(m_mouseX, m_mouseY);
	std::cout << "\nCurrent Location: (" << m_mouseX << ", " << m_mouseY << ")   \n"
		<< "Current Move Number: " << m_moves << "    " << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_TIME));

	//checks if mouse is at end
	if (m_mouseX == COLUMN_NUMBER / 2 && m_mouseY == ROW_NUMBER / 2)
	{
		//print out an ending screen
		showConsoleCursor(true);
		std::cout << "\n----------------------------\nTotal Move Number: " << m_moves << "moves" << "    "
			<< "\nNumber of Attempt: " << m_trainCount + 1 << " out of " << m_maxTrainCount << std::endl;
        std::cin.ignore( std::numeric_limits< std::streamsize >::max( ), '\n' );

		//resets constants
		m_moves = 0;
		m_mouseX = 0;
		m_mouseY = 0;
		++m_trainCount;
		return false;
	}
	m_moveLock = false;
	return false;
}

bool MicroMouseSim::isEnd()
{
	if (m_mouseX == COLUMN_NUMBER / 2 && m_mouseY == ROW_NUMBER / 2)
		return true;
	return false;
}

////////////////////////////////////////////////////////
//	Clear Screen implementation below
////////////////////////////////////////////////////////

#ifdef _MSC_VER  //  Microsoft Visual C++

#pragma warning(disable : 4005)
#include <windows.h>

void MicroMouseSim::clearScreen()
{
	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void MicroMouseSim::showConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <curses.h>

void MicroMouseSim::clearScreen()  // will just write a newline in an Xcode output window
{
	static const char* term = getenv("TERM");
	if (term == nullptr || strcmp(term, "dumb") == 0)
		std::cout << std::endl;
	else
	{
		static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
		std::cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << std::flush;
	}
}

void MicroMouseSim::showConsoleCursor(bool showFlag)
{
	if (showFlag)
		curs_set(1);
	else
		curs_set(0);
}

#endif
