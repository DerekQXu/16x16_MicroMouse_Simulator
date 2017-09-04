#ifndef MICROMOUSESIM_H
#define MICROMOUSESIM_H
#include "Maze.h"
#include "Cell.h"
#include "Common.h"

class MicroMouseSim
{
    public:
        MicroMouseSim();
        bool displayMaze();
		bool isEnd();
        bool moveMouse(Direction ID);
        bool checkWall(Direction ID);
    private:
        int m_mouseX;
        int m_mouseY;
        int m_moves;
        int m_trainCount;
        int m_maxTrainCount;
        bool m_moveLock;
		Maze maze;
        void showConsoleCursor(bool showFlag);
        bool canMove(Direction ID);
};

#endif // MICROMOUSESIM_H
