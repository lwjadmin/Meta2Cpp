#pragma once
#include "Actor.h"
#include "Enum.h"

class APlayer : public AActor
{
public:
	APlayer();
	APlayer(int InX, int InY);
	void Tick();
	void OnPressKey(int KeyCode);
	void Move(MoveDirection direction);
	void CollisionCheck(int newX, int newY);
	virtual ~APlayer();
private:
	int InputKeyCode;
};

