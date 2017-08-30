#ifndef MICROMOUSESIM_H
#define MICROMOUSESIM_H
#include "Maze.h"
#include "Cell.h"
#include "Common.h"

class MicroMouseSim
{
    public:
        MicroMouseSim();
        displayMaze();
        moveMouse(Direction ID);
        isWall(Direction ID);
    private:
        int m_mouseX;
        int m_mouseY;
        int m_maxTrainCount;
        int m_moves;
        int m_trainCount;
        int m_maxTrainCount;
        ShowConsoleCursor(bool showFlag);
        cannotMove(Direction ID);
}

#endif // MICROMOUSESIM_H
