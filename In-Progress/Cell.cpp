#include "Cell.h"
#include "Wall.h"
#include "Common.h"
#include <cstddef>

Cell::Cell()
{
    m_leftWall = (Wall*) nullptr;
    m_rightWall = (Wall*) nullptr;
    m_upWall = (Wall*) nullptr;
    m_downWall = (Wall*) nullptr;
}

//links a wall to the cell
void Cell::setWall(Wall* wall, Direction ID)
{
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
bool Cell::getWall(Direction ID)
{
    switch(ID)
{
    case LEFT:
        if (m_leftWall == (Wall*) nullptr)
            return false;
        break;
    case RIGHT:
        if (m_rightWall == (Wall*) nullptr)
            return false;
        break;
    case UP:
        if (m_upWall == (Wall*) nullptr)
            return false;
        break;
    case DOWN:
        if (m_downWall == (Wall*) nullptr)
            return false;
}
    return true;
}
