#include "MyEngine.h"

MyEngine* MyEngine::Instance = nullptr;

MyEngine::MyEngine()
{
	Instance = this;
}

MyEngine::~MyEngine()
{
	Instance = nullptr;
}

void MyEngine::Initialize()
{
	MyGameState->AddLevelList("Level1.txt");
	MyGameState->AddLevelList("Level2.txt");
	MyGameState->AddLevelList("Level3.txt");
	LoadLevel(MyGameState->LevelList[MyGameState->CurrentLevelIndex]);
}

void MyEngine::Terminalize()
{

}

int MyEngine::GetRandNumber(int MinValue, int MaxValue)
{
	std::random_device rd;
	std::mt19937 mersentwisterrandom(rd());
	std::uniform_int_distribution<int> GetRandomInt32(MinValue, MaxValue);
	return GetRandomInt32(mersentwisterrandom);
}

bool MyEngine::LoadNextLevel()
{
	bool bLoadSuccess = false;
	if (MyGameState->CurrentLevelIndex < MyGameState->LevelList.size() - 1)
	{
		MyGameState->CurrentLevelIndex++;
		LoadLevel(MyGameState->LevelList[MyGameState->CurrentLevelIndex].c_str());
		bLoadSuccess = true;
	}
	return bLoadSuccess;
}

bool MyEngine::LoadCurrentLevel()
{
	return LoadLevel(MyGameState->LevelList[MyGameState->CurrentLevelIndex].c_str());
}
