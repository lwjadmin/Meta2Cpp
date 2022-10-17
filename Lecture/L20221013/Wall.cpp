#include "Wall.h"

AWall::AWall()
{
	Shape = '*';
}

AWall::AWall(int InX, int InY) : AWall()
{
	X = InX;
	Y = InY;
}

AWall::~AWall()
{
}

