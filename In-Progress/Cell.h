#ifndef CELL_H
#define CELL_H
#include "Wall.h"

class Cell
{
public:
    Cell();
    void setWall(Wall* wall, Direction ID);
    bool getWall(Direction ID);

private:
    Wall* m_leftWall;
    Wall* m_rightWall;
    Wall* m_upWall;
    Wall* m_downWall;
};

#endif // CELL_H
