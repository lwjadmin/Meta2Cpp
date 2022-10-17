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
	Load("Level1.txt");
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
