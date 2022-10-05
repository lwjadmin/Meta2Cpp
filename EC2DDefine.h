#pragma once
#include <conio.h>

#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <map>


using namespace std;

enum class EMoveDirection : int
{
    North = 0,
    East = 90,
    South = 180,
    West = 270,
};

enum class EMonsterType : int
{
    UnDefined = 0,
    Goblin = 1,
    Slime = 2,
    Hog = 3,
};

enum class EActorType : int
{
    Unknown = 0,
    Wall = 1,
    Floor = 2,
    Player = 3,
    Monster = 4
};

enum class EGameStatus : int
{
    UNKNOWN = 0,
    INIT = 1,
    PLAY = 2,
    STOP = 3,
    END = 4
};

#define SAFE_DELETE(x) { if(x){delete(x); (x) = nullptr;} } 
#define SAFE_DELETE_ARRAY(x) { if(x){delete[](x); (x)=nullptr;} }