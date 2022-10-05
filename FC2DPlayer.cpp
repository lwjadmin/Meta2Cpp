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
    for (auto monster = ParentWorld->MonsterPool.begin(); monster != ParentWorld->MonsterPool.end(); monster++)
    {
        double distance = sqrt(pow((this->PosX - monster->PosX), 2) + pow((this->PosY - monster->PosY), 2));
        if (monster->isAlive && (AttackRange > distance))
        {
            monster->isAlive = false;
            MonsterKillCount++;
            this->Gold += monster->Gold;
        }
    }
}