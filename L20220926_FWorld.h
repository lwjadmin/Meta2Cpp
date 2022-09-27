#pragma once
//
//#include "L20220926_FPlayer.h"
//#include "L20220926_FWall.h"
//#include "L20220926_FGoal.h"
//#include "L20220926_FFloor.h"
//

#include <vector>
class FPlayer;
class FWall;
class FFloor;
class FGoal;

using namespace std;

class FWorld
{
public:
    FPlayer* Player;
    vector<FWall> Walls;
    vector<FFloor> Floors;
    FGoal* Goal;
};

