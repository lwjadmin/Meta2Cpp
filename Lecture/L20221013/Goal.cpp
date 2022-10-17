#include "Goal.h"
#include "MyEngine.h"
#include "Player.h"
#include <iostream>

using namespace std;

AGoal::AGoal()
{
	Shape = 'G';
	ZOrder = 30;
	CollisionType = ECollisionType::QueryOnly;
	MyColor = { 255, 255, 0, 0 };
	LoadBMP("Data/coin.bmp");

}

AGoal::AGoal(int NewX, int NewY)
	: AGoal()
{
	X = NewX;
	Y = NewY;
}

AGoal::~AGoal()
{
}

void AGoal::Tick()
{
	for (AActor* Actor : GEngine->GetAllActors())
	{
		//액터들의 위치중에서 플레이어가 나와 같은 위치에 있을 경우 승리
		if (X == Actor->X && Y == Actor->Y &&
			dynamic_cast<APlayer*>(Actor))
		{
			cout << "Complete" << endl;
			GEngine->QuitGame();
		}
	}
}
