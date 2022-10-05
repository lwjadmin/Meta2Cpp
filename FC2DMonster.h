#pragma once
#include "EC2DDefine.h"
#include "FC2DActor.h"

class FC2DMonster : public FC2DActor
{
public:
    int HP;
    int Gold;
    int Force;
    int AttackRange;
    bool isAlive;
    EMonsterType MonsterType;

    FC2DMonster(FC2DGameWorld* InFC2DGameWorld);

    void InitMonster
    (
        int InHP,
        int InGold,
        int InForce,
        int AttackRange,
        EMonsterType InMonsterType
    );

    void Attack(FC2DPlayer* Target);
    void Dead() { 

        switch (MonsterType)
        {
            case EMonsterType::Goblin:
                ParentWorld->ProcessAFMessage.append("[SYS]고블린이 죽으며 " + to_string(this->Gold) + " 를 얻었습니다.\n");
                break;
            case EMonsterType::Slime:
                ParentWorld->ProcessAFMessage.append("[SYS]슬라임이 죽으며 " + to_string(this->Gold) + " 를 얻었습니다.\n");
                break;
            case EMonsterType::Hog:
                ParentWorld->ProcessAFMessage.append("[SYS]멧돼지가 죽으며 " + to_string(this->Gold) + " 를 얻었습니다.\n");
                break;
            default:
                break;
        }

        
        this->Destroy();
    }
};