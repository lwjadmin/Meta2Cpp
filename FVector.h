#pragma once

class FVector
{
public:
    int PosX; //0~255
    int PosY; //0~255

    FVector()
        : PosX(0), PosY(0)
    {
    }

    FVector(int InPosX, int InPosY) 
        : PosX(InPosX), PosY(InPosY)
    {

    }
};