#pragma once
#include "EC2DDefine.h"
#include "FC2DGameWorld.h"

class FC2DActor
{
public:
    EActorType ActorType;
    int PosX;
    int PosY;
    FC2DGameWorld* ParentWorld;

    FC2DActor();
    FC2DActor(EActorType InActorType, int InPosX, int InPosY, FC2DGameWorld* InFC2DGameWorld);
    void SetPosition(int InPosX, int InPosY);
    void Move(EMoveDirection Direction);
    void Destroy()
    {
        *ParentWorld->GetMapTile(PosX, PosY) = (int)EActorType::Floor;
    }
};