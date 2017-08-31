#include "Maze.h"
#include "Cell.h"
#include "Common.h"
#include "MicroMouseSim.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <string>
#include <chrono>
#include <thread>

//sets up constants and maze; gets ready to print to console
MicroMouseSim::MicroMouseSim()
{
    std::cout.setf(std::ios::boolalpha);

    Maze maze;
    maze.setMaze();
    int m_mouseX = 0;
    int m_mouseY = 0;
    int m_moves = 0;
    int m_trainCount = 0;
    bool m_moveLock = false;

    std::cout << "Maze: " << std::endl;
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
bool MircoMouseSim::canMove(Direction ID)
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
    if (m_moveLock || !canMove(ID)){
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
    COORD coord;
    coord.X = 0;
    coord.Y = 0;

    //prints maze
    maze.printMaze(m_mouseX, m_mouseY);
    std::cout << "\nCurrent Location: (" << m_mouseX << ", " << m_mouseY ")\n"
        << "Current Move Number: " << m_moves << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    //checks if mouse is at end
    if ((m_mouseX == COLUMN_NUMBER/2 && (m_mouseY == ROW_NUMBER/2 || m_mouseY == ROW_NUMBER/2+1))
            || (m_mouseX == COLUMN_NUMBER/2+1 && (m_mouseY == ROW_NUMBER/2 || m_mouseY == ROW_NUMBER/2+1)))
    {
        //print out an ending screen
        showConsoleCursor(true);
        std::cout << "\nTotal Move Number: " << m_moves << "moves"
            << "\nNumbers of Attempts: " << m_trainCount << " out of " << m_maxTrainCount
            << "\npress any key to continue" << std::endl;
        system("pause");
	
        //resets constants
        m_moves = 0;
        m_mouseX = 0;
        m_mouseY = 0;
        ++m_trainCount;
        return true;
    }
    m_moveLock = false;
    return false;
}

//helper function to print on terminal
void showConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
