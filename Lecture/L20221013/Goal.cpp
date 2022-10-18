#include "Goal.h"
#include "MyEngine.h"
#include "Player.h"
#include <iostream>
#include "Text.h"
using namespace std;

AGoal::AGoal()
{
	Shape = 'G';
	ZOrder = 30;
	CollisionType = ECollisionType::QueryOnly;
	MyColor = { 255, 255, 0, 0 };
	LoadBMP("Data/coin.bmp");
	isComplete = false;
	ElapsedTime = 0;
	ExecuteTime = 3000;
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
	if (!isComplete)
	{
		for (AActor* Actor : GEngine->GetAllActors())
		{
			//���͵��� ��ġ�߿��� �÷��̾ ���� ���� ��ġ�� ���� ��� �¸�
			if (X == Actor->X && Y == Actor->Y && dynamic_cast<APlayer*>(Actor))
			{
				string content = GEngine->MyGameState->GetCurrentLevelName() + " Ŭ����!";
				GEngine->SpawnActor(new AText(100, 100, content.c_str(), 30));
				GEngine->MyGameState->bPlayerCanMove = false;
				isComplete = true;
				break;
			}
		}
	}
	else
	{
		ElapsedTime += GEngine->GetWorldDeltaSeconds();
		if (ElapsedTime > ExecuteTime)
		{
			if (!GEngine->LoadNextLevel())
			{
				cout << "YOU WIN!" << endl;
				GEngine->QuitGame();
			}
		}
	}
}
