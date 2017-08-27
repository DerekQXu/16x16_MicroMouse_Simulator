#ifndef CELL_H
#define CELL_H

class Cell
{
public:
    Wall();
    bool isWall();

private:
    bool m_isWall;
};

#endif // CELL_H
