#pragma once

class FPlayer;

class FGoal
{
public:
    int X;
    int Y;
    char Shape;
    bool IsOverlapPlayer(FPlayer Player);
};

