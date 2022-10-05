#include "FC2DActor.h"
#include "FC2DGameWorld.h"

FC2DActor::FC2DActor() : PosX(0), PosY(0), ParentWorld(nullptr)
{

}

FC2DActor::FC2DActor(int InPosX, int InPosY, FC2DGameWorld* InFC2DGameWorld)
    : PosX(InPosX), PosY(InPosY), ParentWorld(InFC2DGameWorld)
{

}

void FC2DActor::SetPosition(int InPosX, int InPosY)
{
    PosX = InPosX;
    PosY = InPosY;
}

void FC2DActor::Move(EMoveDirection Direction)
{
    switch (Direction)
    {
        case EMoveDirection::North:
        {
            int newPosY = PosY - 1;
            int* prevMapTile = ParentWorld->GetMapTile(PosX, PosY);
            int* nextMapTile = ParentWorld->GetMapTile(PosX, newPosY);
            if (*nextMapTile == (int)EMapType::Floor)
            {
                ParentWorld->SwapMapTile(prevMapTile, nextMapTile);
                PosY = newPosY;
            }
            break;
        }
        case EMoveDirection::East:
        {
            int newPosX = PosX + 1;
            int* prevMapTile = ParentWorld->GetMapTile(PosX, PosY);
            int* nextMapTile = ParentWorld->GetMapTile(newPosX, PosY);
            if (*nextMapTile == (int)EMapType::Floor)
            {
                ParentWorld->SwapMapTile(prevMapTile, nextMapTile);
                PosX = newPosX;
            }
            break;
        }
        case EMoveDirection::South:
        {
            int newPosY = PosY + 1;
            int* prevMapTile = ParentWorld->GetMapTile(PosX, PosY);
            int* nextMapTile = ParentWorld->GetMapTile(PosX, newPosY);
            if (*nextMapTile == (int)EMapType::Floor)
            {
                ParentWorld->SwapMapTile(prevMapTile, nextMapTile);
                PosY = newPosY;
            }
            break;
        }
        case EMoveDirection::West:
        {
            int newPosX = PosX - 1;
            int* prevMapTile = ParentWorld->GetMapTile(PosX, PosY);
            int* nextMapTile = ParentWorld->GetMapTile(newPosX, PosY);
            if (*nextMapTile == (int)EMapType::Floor)
            {
                ParentWorld->SwapMapTile(prevMapTile, nextMapTile);
                PosX = newPosX;
            }
            break;
        }
    }
}