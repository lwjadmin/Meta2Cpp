#include "Player.h"
#include <iostream>

APlayer::APlayer()
{
	Shape = 'P';
    InputKeyCode = 0;
}

APlayer::APlayer(int InX, int InY) : APlayer()
{
	X = InX;
	Y = InY;
}

void APlayer::Tick()
{
    switch (InputKeyCode)
    {
        case 'w':
        {
            Y--;
            break;
        }
        case 'a':
        {
            X--;
            break;
        }
        case 's':
        {
            Y++;
            break;
        }
        case 'd':
        {
            X++;
            break;
        }
    }
}


void APlayer::OnPressKey(int KeyCode)
{
    InputKeyCode = KeyCode;
}

void APlayer::CollisionCheck(int newX, int newY)
{

}

APlayer::~APlayer()
{
}