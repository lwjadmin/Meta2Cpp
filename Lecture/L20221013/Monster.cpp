#include <iostream>

#include "Monster.h"
#include "MyEngine.h"
#include "Player.h"
#include "Goal.h"
#include "Wall.h"

using namespace std;

AMonster::AMonster()
{
	srand((unsigned int)time(nullptr));
	Shape = 'M';
	ZOrder = 45;
	MyColor = { 255, 0, 0, 0 };
	LoadBMP("Data/Slime.bmp");
	CollisionType = ECollisionType::QueryOnly;
	ElapsedTime = 0;
	ExecuteTime = 500 + (Uint64)GEngine->GetRandNumber(-100, 200);
}

AMonster::AMonster(int NewX, int NewY)
	: AMonster()
{
	X = NewX;
	Y = NewY;
}

AMonster::~AMonster()
{
}

void AMonster::Tick()
{
	ElapsedTime += GEngine->GetWorldDeltaSeconds();
	if (ElapsedTime > ExecuteTime)
	{
		ElapsedTime = 0;

		int Direction = GEngine->GetRandNumber(0, 4);

		switch (Direction)
		{
			case 0: //W(UP)
			{
				Y--;
				if (!PredictCanMove())
				{
					Y++;
				}
				break;
			}
			case 1: //A(Left)
			{
				X--;
				if (!PredictCanMove())
				{
					X++;
				}
				break;
			}
			case 2: //S(Right)
			{
				Y++;
				if (!PredictCanMove())
				{
					Y--;
				}
				break;
			}
			case 3: //D(Down)
			{
				X++;
				if (!PredictCanMove())
				{
					X--;
				}
				break;
			}
		}
	}
	for (AActor* Actor : GEngine->GetAllActors())
	{
		if (X == Actor->X && Y == Actor->Y && dynamic_cast<APlayer*>(Actor))
		{
			cout << "YOU LOSE!" << endl;
			GEngine->QuitGame();
		}
	}
}

bool AMonster::PredictCanMove()
{
	for (AActor* Actor : GEngine->GetAllActors())
	{
		if (X == Actor->X && Y == Actor->Y && 
			dynamic_cast<AMonster*>(Actor) == nullptr &&
			dynamic_cast<AMonster*>(Actor) != this)
		{
			if (CheckHit(Actor))
			{
				return false;
			}
		}
	}
	return true;
}

bool AMonster::CheckHit(AActor* Other)
{
	if (dynamic_cast<AWall*>(Other) || dynamic_cast<AGoal*>(Other))
	{
		return true;
	}
	return false;
}


