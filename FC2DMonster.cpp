#pragma once
#include "EC2DDefine.h"
#include "FC2DMonster.h"
#include "FC2DGameWorld.h"
#include "FC2DPlayer.h"


FC2DMonster::FC2DMonster(FC2DGameWorld* InFC2DGameWorld)
{
    HP = 0;
    Gold = 0;
    Force = 0;
    isAlive = true;
    MonsterType = EMonsterType::UnDefined;
    ParentWorld = InFC2DGameWorld;
    ActorType = EActorType::Monster;
}

void FC2DMonster::InitMonster
(
    int InHP,
    int InGold,
    int InForce,
    int InAttackRange,
    EMonsterType InMonsterType
)
{
    HP = InHP;
    Gold = InGold;
    Force = InForce;
    AttackRange = InAttackRange;
    isAlive = true;
    MonsterType = InMonsterType;
}

void FC2DMonster::Attack(FC2DPlayer* Player)
{
    double distance = sqrt(pow((this->PosX - Player->PosX), 2) + pow((this->PosY - Player->PosY), 2));
    if (Player->isAlive && (AttackRange > distance))
    {
        Player->HP -= Force;
        if (Player->HP < 0)
        {
            Player->HP = 0;
            Player->isAlive = false;
        }
    }
}