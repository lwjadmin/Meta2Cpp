#include "GameState.h"

FGameState::FGameState() : CurrentLevelIndex(0), bPlayerCanMove(true)
{
    
}

FGameState::~FGameState()
{
}

void FGameState::AddLevelList(string levelName)
{
    LevelList.push_back(levelName);
}

void FGameState::RemoveLevelList(string levelName)
{
    LevelList.erase(find(LevelList.begin(),LevelList.end(),levelName));
}

string FGameState::GetCurrentLevelName()
{
    return LevelList[CurrentLevelIndex];
}




