#ifndef CELL_H
#define CELL_H

class Cell
{
public:
	Cell();

	void setWallL();
	void setWallR();
	void setWallU();
	void setWallD();

	bool getWallL();
	bool getWallR();
	bool getWallU();
	bool getWallD();

private:
	bool wallL;
	bool wallR;
	bool wallU;
	bool wallD;
};

#endif // CELL_H