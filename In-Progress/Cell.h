#ifndef CELL_H
#define CELL_H

class Cell
{
public:
	Cell();
	void setWall(Wall* wall, Direction ID);
	Wall* getWall(Direction ID);
    void setCell(Cell* cell, Direction ID);
    Cell* getCell(Direction ID);

private:
    Wall* m_leftWall;
    Wall* m_rightWall;
    Wall* m_upWall;
    Wall* m_downWall;

    Cell* m_leftCell;
    Cell* m_rightCell;
    Cell* m_upCell;
    Cell* m_downCell;
};

#endif // CELL_H
