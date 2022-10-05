#pragma once
#include "EC2DDefine.h"

class FC2DPlayer;
class FC2DMonster;
class FC2DGameState;

class FC2DGameWorld
{
public:
    int* Map;
    int MapYRows;
    int MapXCols;
    FC2DPlayer* Player;
    vector<FC2DMonster> MonsterPool;
    string ProcessAFMessage;
    int Tick;

    FC2DGameWorld();
    void Init();
    void SpawnMonster();
    void SpawnCharacter();
    void Draw();
    int* GetMapTile(int posX, int posY);
    void SwapMapTile(int* A, int* B);
    void Process(char InputKey, FC2DGameState& GameState);
    ~FC2DGameWorld();
};