#pragma once
#include "EC2DDefine.h"
#include "FC2DActor.h"

class FC2DPlayer : public FC2DActor
{
public:
    int HP;
    int Force;
    int Gold;
    bool isAlive;
    const int AttackRange = 5;
    int MonsterKillCount = 0;
    FC2DGameWorld* InFC2DGameWorld;

    FC2DPlayer(FC2DGameWorld* InFC2DGameWorld);

    void InitPlayer(int InHP,int InForce,int InGold);

    void Attack();
};