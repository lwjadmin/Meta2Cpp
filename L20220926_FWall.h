#pragma once

//���漱��
class FPlayer;

class FWall
{
public:
    int X;
    int Y;
    char Shape;
    bool DoCollision(FPlayer Player);
};

