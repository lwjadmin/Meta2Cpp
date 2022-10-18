#pragma once
#include <string>
#include <vector>
using namespace std;

class FGameState
{
public:
    FGameState();
    ~FGameState();

    void AddLevelList(string levelName);
    void RemoveLevelList(string levelName);
    string GetCurrentLevelName();
    vector<string> LevelList;
    int CurrentLevelIndex;
    bool bPlayerCanMove;
};