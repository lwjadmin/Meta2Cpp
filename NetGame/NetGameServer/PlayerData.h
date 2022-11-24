#pragma once
class PlayerData
{
public:
    SOCKET MySocket;
    int X;
    int Y;

    PlayerData()
    {
        MySocket = NULL;
        X = 0;
        Y = 0;
    }

    bool operator==(const PlayerData& RHS)
    {
        return MySocket == RHS.MySocket ? true : false;
    }

};