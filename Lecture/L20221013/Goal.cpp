#include "Goal.h"

AGoal::AGoal()
{
	Shape = 'G';
}

AGoal::AGoal(int InX, int InY) : AGoal()
{
	X = InX;
	Y = InY;
}


AGoal::~AGoal()
{
}