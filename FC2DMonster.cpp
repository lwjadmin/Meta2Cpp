#pragma once
#include "EC2DDefine.h"
#include "FC2DMonster.h"
#include "FC2DGameWorld.h"


FC2DMonster::FC2DMonster(FC2DGameWorld* InFC2DGameWorld)
{
    this->ParentWorld = InFC2DGameWorld;
    HP = 0;
    Gold = 0;
    Force = 0;
    isAlive = true;
    MonsterType = EMonsterType::UnDefined;
}

void FC2DMonster::InitMonster
(
    int InHP,
    int InGold,
    int InForce,
    EMonsterType InMonsterType
)
{
    HP = InHP;
    Gold = InGold;
    Force = InForce;
    MonsterType = InMonsterType;
    isAlive = true;
}

void Attack()
{

    //Target->HP -= Force;
    //if (Target->isAlive && Target->HP < 0)
    //{
    //    Target->isAlive = false;
    //    Target->HP = 0;
    //    Gold += Target->Gold;
    //}
}