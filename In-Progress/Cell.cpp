#include "Cell.h"
#include "Wall.h"
#include "Common.h"

Cell::Cell()
{
    Wall* m_leftWall = NULL;
    Wall* m_rightWall = NULL;
    Wall* m_upWall = NULL;
    Wall* m_downWall = NULL;

    Cell* m_leftCell = NULL;
    Cell* m_rightCell = NULL;
    Cell* m_upCell = NULL;
    Cell* m_downCell = NULL;
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
    return;
}
};

//returns a pointer to linked wall or NULL in the direction of ID
Wall getWall(Direction ID)
{
    switch(ID)
{
    case LEFT:
        return m_leftWall;
    case RIGHT:
        return m_rightWall;
    case UP:
        return m_upWall;
    case DOWN:
        return m_downWall;
    return NULL;
}
}

//links another cell to the cell
void Cell::setWall(Wall* cell, Direction ID)
    switch(ID)
{
    case LEFT:
        m_leftCell = cell;
        break;
    case RIGHT:
        m_rightCell = cell;
        break;
    case UP:
        m_upCell = cell;
        break;
    case DOWN:
        m_downCell = cell;
        break;
    return;
}
};


//returns a pointer to linked cell or NULL in the direction of ID
Wall getCell(Direction ID)
{
    switch(ID)
{
    case LEFT:
        return m_leftCell;
    case RIGHT:
        return m_rightCell;
    case UP:
        return m_upCell;
    case DOWN:
        return m_downCell;
    return NULL;
}
}
