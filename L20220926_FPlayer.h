#pragma once

class FPlayer
{
public:
    int X;
    int Y;
    char Shape;

    void Move(int Direction);
    bool IsCollasped(int X, int Y);
};

