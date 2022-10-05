#pragma once
#include "EC2DDefine.h"
#include "FC2DActor.h"

class FC2DMonster : public FC2DActor
{
public:
    int HP;
    int Gold;
    int Force;
    bool isAlive;
    EMonsterType MonsterType;

    FC2DMonster(FC2DGameWorld* InFC2DGameWorld);

    void InitMonster
    (
        int InHP,
        int InGold,
        int InForce,
        EMonsterType InMonsterType
    );
};