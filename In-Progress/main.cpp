#include "Common.h"
#include "MicroMouseSim.h"

//add needed libraries starting here
#include <iostream>
#include <cstdlib> 
#include <ctime> 
//and ending here

using namespace std;

int main()
{
	//add needed global variables starting here
	Direction ID;
	int randNumber;
	//and ending here

	//add setup() code here
	srand((unsigned)time(0));
	//and ending here

    MicroMouseSim world;
    while (!world.displayMaze())
    {
        //add loop() code here
		do {
			randNumber = rand() % 4;
			switch (randNumber) {
			case (0):
				ID = Direction::UP;
				break;
			case (1):
				ID = Direction::DOWN;
				break;
			case (2):
				ID = Direction::LEFT;
				break;
			case (3):
				ID = Direction::RIGHT;
				break;
			}
		} while (world.checkWall(ID));
		world.moveMouse(ID);
		cout << "Random Number: " << randNumber << endl;
        //and ending here
    }
    return 0;
}
