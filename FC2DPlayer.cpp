#include "FC2DPlayer.h"
#include "FC2DMonster.h"

FC2DPlayer::FC2DPlayer(FC2DGameWorld* InFC2DGameWorld)
{
    HP = 100;
    Force = 10;
    Gold = 0;
    isAlive = true;
    ParentWorld = InFC2DGameWorld;
}

void FC2DPlayer::InitPlayer(int InHP, int InForce, int InGold)
{
    HP = InHP;
    Force = InForce;
    Gold = InGold;
    isAlive = true;
}

void FC2DPlayer::Attack()
{
    //Target->HP -= Force;
    //if (Target->isAlive && Target->HP < 0)
    //{
    //    Target->isAlive = false;
    //    Target->HP = 0;
    //    Gold += Target->Gold;
    //}
}