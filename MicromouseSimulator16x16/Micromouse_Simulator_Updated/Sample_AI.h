#ifndef Sample_AI_H
#define Sample_AI_H
#include "Maze.h"
#include "Cell.h"
#include <string>
const int MAZE_SIZE = 16;

class Sample_AI : public Maze
{
public:
	Sample_AI();
	void setAI();
	void resetAI();
	void getNewLocation(Cell passthrough[][MAZE_SIZE], int &outputX, int &outputY);

	void scanMaze(int memory[][MAZE_SIZE], Cell passthrough[][MAZE_SIZE]);
	void clearMaze(int floodfill[][16]);
	void setCell(int i, int j, int val, int floodfill[][MAZE_SIZE]);
	void createMaze(int val, int target, int floodfill[][MAZE_SIZE]);

	void findNewLocation(int location[], int direction[]);

	int getX();
	int getY();

private:
	int floodfill[16][16];
	int memory[16][16];
	int location[2];
	int direction[2];
};

#endif // Sample_AI_H
