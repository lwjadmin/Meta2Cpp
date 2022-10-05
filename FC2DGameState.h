#pragma once
#include "EC2DDefine.h"

class FC2DGameState
{
public:
    EGameStatus GameStatus;
    FC2DGameState()
    {
        GameStatus = EGameStatus::UNKNOWN;
    }
};
