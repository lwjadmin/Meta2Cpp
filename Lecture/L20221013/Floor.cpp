#include "Floor.h"

AFloor::AFloor()
{
	Shape = ' ';
}

AFloor::AFloor(int InX, int InY) : AFloor()
{
	X = InX;
	Y = InY;
}

AFloor::~AFloor()
{

}