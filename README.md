## Overview

A micro-mouse simulation program. User may run their own algorithms by altering code in main.cpp (a sample flood-fill algorithm is provided). Program runs user’s algorithm in a 16x16 size maze, prints number of moves take, and allows repeated runs.

## Usage

To view the simulation, simply run the main.cpp file. Note, currently works only on Windows platform.

## Editing Code

To edit algorithm, open Micromouse_Simulator/main.cpp. Add code in the spaces labeled as follows (Code is structured as if it was being run on an Arduino):
```C
#include "Common.h"
#include "MicroMouseSim.h"

//add libraries starting here
. . .
//and ending here

using namespace std;
MicroMouseSim world;

//add global variables starting here
. . .
//and ending here

//declare functions here
. . .
//and ending here

int main()
{
	//add setup() code here
	. . .
	//and ending here

	while (!world.displayMaze()){
		//add loop() code here
		. . .
        	//and ending here
	}
	return 0;
}
```

Use the following to move the mouse or retrieve information about surroundings:
```C
//Variables used to specify direction
Direction::UP
Direction::DOWN
Direction::LEFT
Direction::RIGHT
//returns true if there is a wall in given DIRECTION
world.checkWall(DIRECTION)
//moves mouse in given DIRECTION (can only be used once per loop)
world.moveMouse(DIRECTION)
//returns true if mouse has completed maze (used to reset variables between runs)
world.isEnd()
```
Note: main.cpp currently contains a sample algorithm already written.

## Editing other parts of maze

To edit the maze, please edit the maze.txt file:
The file is a 16 by 16 sequence of codes denoted by the following:
```C
U	- there is an upper wall*
R	- there is a right wall*
B	- there is an upper and a right wall*
.	- there are no walls*
*adjacent to cell
```  <br />
To edit the size of the maze, open Micromouse_Simulator/Common.h and alter:
```C
#define ROW_NUMBER 16
#define COLUMN_NUMBER 16
```
Note: the finish is always located at (COLUMN_NUMBER/2, ROW_NUMBER/2), rounded down. The grid convention is that (0,0) is located in the bottom left corner.<br />
To edit the speed the mouse is moving, open Micromouse_Simulator/Common.h and alter:
```C
#define DELAY_TIME 10
```
Note: delay time is time in miliseconds between each move.
