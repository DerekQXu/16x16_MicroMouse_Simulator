#include "Cell.h"
#include "Wall.h"
#include "Common.h"

Cell::Cell()
{
    Wall* m_leftWall = NULL;
    Wall* m_rightWall = NULL;
    Wall* m_upWall = NULL;
    Wall* m_downWall = NULL;
}

//links a wall to the cell
void Cell::setWall(Wall* wall, Direction ID)
    switch(ID)
{
    case LEFT:
        m_leftWall = wall;
        break;
    case RIGHT:
        m_rightWall = wall;
        break;
    case UP:
        m_upWall = wall;
        break;
    case DOWN:
        m_downWall = wall;
        break;
}
    return;
};

//returns a pointer to linked wall or NULL in the direction of ID
bool getWall(Direction ID)
{
    switch(ID)
{
    case LEFT:
        if (m_leftWall == NULL)
            return false;
        break;
    case RIGHT:
        if (m_rightWall == NULL)
            return false;
        break;
    case UP:
        if (m_upWall == NULL)
            return false;
        break;
    case DOWN:
        if (m_downWall == NULL)
            return false;
}
    return true;
}
