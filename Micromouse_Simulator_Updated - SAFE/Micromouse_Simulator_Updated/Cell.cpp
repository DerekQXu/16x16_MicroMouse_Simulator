#include "Cell.h"
#include <iostream>

//sets default value
Cell::Cell()
{
	wallL = false;
	wallR = false;
	wallU = false;
	wallD = false;
}

//sets walls
void Cell::setWallL() {
	wallL = true;
};
void Cell::setWallR() {
	wallR = true;
};
void Cell::setWallU() {
	wallU = true;
};
void Cell::setWallD() {
	wallD = true;
};

//returns walls
bool Cell::getWallL() {
	return wallL;
};
bool Cell::getWallR() {
	return wallR;
};
bool Cell::getWallU() {
	return wallU;
};
bool Cell::getWallD() {
	return wallD;
};