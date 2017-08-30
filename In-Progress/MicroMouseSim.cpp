#include "Maze.h"
#include "Cell.h"
#include "Common.h"
#include "MicroMouseSim.cpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <string>

MicroMouseSim::MicroMouseSim()
{
    std::cout.setf(std::ios::boolalpha);

    Maze maze;
    maze.setMaze();
    int m_mouseX = 0;
    int m_mouseY = 0;
    int m_maxTrainCount;
    int m_moves = 0;
    int m_trainCount = 0;
    bool can_move = true;

    std::cout << "Maze: " << std::endl;
    maze.printMaze(m_mouseX, m_mouseY);
    std::cout << "How many times would you like to run the AI?" << std::endl;
    std::cin >> m_maxTrainCount;
}

bool MicroMouseSim::isWall(Direction ID)
{
    return maze.getCell(m_mouseX, m_mouseY)->getWall(ID);
}

bool MircoMouseSim::cannotMove(Direction ID)
{
    switch (ID)
    {
        case UP:
            if (maze.getCell(m_mouseX, m_mouseY)->getWall(Direction::UP))
                return true;
            break;
        case DOWN:
            if (maze.getCell(m_mouseX, m_mouseY)->getWall(Direction::DOWN))
                return true;
            break;
        case RIGHT:
            if (maze.getCell(m_mouseX, m_mouseY)->getWall(Direction::RIGHT))
                return true;
            break;
        case LEFT:
            if (maze.getCell(m_mouseX, m_mouseY)->getWall(Direction::LEFT))
                return true;
            break;
    }
    return false;
}

bool MicroMouseSim::moveMouse(Direction ID)
{
    bool hasMoved = true;
    switch (ID)
    {
        case UP:
            if (m_mouseY >= ROW_NUMBER-1 || cannotMove(ID))
                hasMoved = false;
            else
                ++m_mouseY;
            break;
        case DOWN:
            if (m_mouseY <= 0 || cannotMove(ID))
                hasMoved = false;
            else
                --m_mouseY;
            break;
        case RIGHT:
            if (m_mouseX >= COLUMN_NUMBER-1 || cannotMove(ID))
                hasMoved = false;
            else
                ++m_mouseX;
            break;
        case LEFT:
            if (m_mouseX <= 0 || cannotMove(ID))
                hasMoved = false;
            else
                --m_mouseX;
            break;
    }
    ++m_moves;
    return hasMoved;
}

//returns true if mouse is at end
bool MicroMouseSim::displayMaze()
{
    //after train count is over
    if (m_trainCount == m_maxTrainCount)
        return true;

    //moves mouse
    ShowConsoleCursor(false);
    COORD coord;
    coord.X = 0;
    coord.Y = 0;

    //prints maze
    maze.printMaze(m_mouseX, m_mouseY);
    std::cout << "\nCurrent Location: (" << m_mouseX << ", " << m_mouseY ")\n"
        << "Current Move Number: " << m_moves << std::endl;
    Sleep(50);

    //checks if mouse is at end
    if (m_mouseX == COLUMN_NUMBER/2
            && (m_mouseY == ROW_NUMBER/2 || m_mouseY == ROW_NUMBER/2+1)
            || m_mouseX == COLUMN_NUMBER/2+1
            && (m_mouseY == ROW_NUMBER/2 || m_mouseY == ROW_NUMBER/2+1))
    {
        //print out an ending screen
        system("cls");
        ShowConsoleCursor(true);
        std::cout << "Total Move Number: " << m_moves << "moves"
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
    return false;
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
