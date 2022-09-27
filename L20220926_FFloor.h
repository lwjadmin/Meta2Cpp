#pragma once

class FPlayer;

class FFloor
{
public:
    int X;
    int Y;
    char Shape;

    bool IsOverlapPlayer(FPlayer Player);
};

