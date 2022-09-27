#pragma once

//전방선언
class FPlayer;

class FWall
{
public:
    int X;
    int Y;
    char Shape;
    bool DoCollision(FPlayer Player);
};

