#include "Actor.h"
#include <iostream>
#include <Windows.h>

using namespace std;

AActor::AActor() : X(1), Y(1), Shape(' ')
{
	/*-----------------
	X = 1;
	Y = 1;
	Shape = ' ';
	-----------------*/
}

AActor::~AActor()
{

}

void AActor::Draw()
{
	COORD Current;
	Current.X = X;
	Current.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Current);

	cout << Shape;
}

void AActor::Tick()
{

}

void AActor::Move(int NewX, int NewY)
{
	X = NewX;
	Y = NewY;
}
