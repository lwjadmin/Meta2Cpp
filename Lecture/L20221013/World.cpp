#include <algorithm>
#include <fstream>
#include <iostream>

#include "World.h"
#include "Actor.h"
#include "Wall.h"
#include "Floor.h"
#include "Player.h"
#include "Goal.h"

FWorld::FWorld()
{

}

FWorld::~FWorld()
{
    DestroyAllActors();
}

void FWorld::SpawnActor(AActor* NewActor)
{
    if (NewActor)
    {
        ActorList.push_back(NewActor);
    }
}

void FWorld::DestroyAllActors()
{
    for (auto value : ActorList)
    {
        if (value != nullptr)
        {
            delete value;
        }
    }
    ActorList.clear();
}

void FWorld::DestroyActor(AActor* DeleteActor)
{
    if (DeleteActor)
    {
        //STL Find¹®
        ActorList.erase(find(ActorList.begin(), ActorList.end(), DeleteActor));
        delete DeleteActor;
        //STL For¹®
        //for (auto it = ActorList.begin(); it != ActorList.end(); it++)
        //{
        //    if (*it == DeleteActor)
        //    {
        //        ActorList.erase(it);
        //        delete DeleteActor;
        //        break;
        //    }
        //}
    }
}

void FWorld::Render()
{
    for (auto value : ActorList)
    {
        auto obj = dynamic_cast<AWall*>(value);
        if (obj) { obj->Draw(); }
    }
    for (auto value : ActorList)
    {
        auto obj = dynamic_cast<AFloor*>(value);
        if (obj) { obj->Draw(); }
    }
    for (auto value : ActorList)
    {
        auto obj = dynamic_cast<AGoal*>(value);
        if (obj) { obj->Draw(); }
    }
    for (auto value : ActorList)
    {
        auto obj = dynamic_cast<APlayer*>(value);
        if (obj) { obj->Draw(); }
    }
    //for (auto value : ActorList)
    //{
    //    if (value != nullptr)
    //    {
    //        value->Draw();
    //    }
    //}
}

void FWorld::Tick()
{
    for (auto value : ActorList)
    {
        if (value)
        {
            value->Tick();
        }
    }
}

void FWorld::Load(string MapFileName)
{
    ifstream MapFile(MapFileName);
    char Data[100] = { 0, };
    int Y = 0;
    if (MapFile.fail())
    {
        cout << "MapFile Load Failed!" << endl;
        return;
    }
    while (MapFile.getline(Data, sizeof(Data)))
    {
        for (int X = 0; X < strlen(Data); X++)
        {
            char& element = Data[X];
            switch (element)
            {
                case '*':
                {
                    SpawnActor(new AWall(X, Y));
                    break;
                }
                case ' ':
                {
                    SpawnActor(new AFloor(X, Y));
                    break;
                }
                case 'P':
                {
                    SpawnActor(new APlayer(X, Y));
                    break;
                }
                case 'G':
                {
                    SpawnActor(new AGoal(X, Y));
                    break;
                }
            }
        }
        Y++;
    }
    MapFile.close();
}
