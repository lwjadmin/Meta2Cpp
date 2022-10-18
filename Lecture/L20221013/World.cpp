#include "World.h"
#include "Actor.h"
#include <algorithm>


FWorld::FWorld() : bTerminateCalled(false)
{
}

FWorld::~FWorld()
{
    Terminate();
}

void FWorld::Terminate()
{
    bTerminateCalled = true;
    for (int i = 0; i < ActorList.size(); i++)
    {
        if (ActorList[i]) { delete ActorList[i]; }
    }
    ActorList.clear();
}

void FWorld::SpawnActor(AActor* NewActor)
{
    if (NewActor && !bTerminateCalled)
    {
        ActorList.push_back(NewActor);
    }
}

void FWorld::DestroyActor(AActor* DeleteActor)
{
    if (DeleteActor && !bTerminateCalled)
    {
        ActorList.erase(find(ActorList.begin(), ActorList.end(), DeleteActor));
        delete DeleteActor;
    }
}

void FWorld::Render()
{
    if (!bTerminateCalled)
    {
        for (int i = 0; i < ActorList.size(); i++)
        {
            if (ActorList[i]) { ActorList[i]->Render(); }
            if (bTerminateCalled) { break; }
        }
    }
}

void FWorld::Tick()
{
    if (!bTerminateCalled)
    {
        for (int i = 0; i < ActorList.size(); i++)
        {
            if (ActorList[i]) { ActorList[i]->Tick(); }
            if (bTerminateCalled) { break; }
        }
    }
}

void FWorld::BeginPlay()
{
    if (!bTerminateCalled)
    {
        for (int i = 0; i < ActorList.size(); i++)
        {
            if (ActorList[i]) { ActorList[i]->BeginPlay(); }
            if (bTerminateCalled) { break; }
        }
    }
}

void FWorld::EndPlay()
{
    if (!bTerminateCalled)
    {
        for (int i = 0; i < ActorList.size(); i++)
        {
            if (ActorList[i]) { ActorList[i]->EndPlay(); }
            if (bTerminateCalled) { break; }
        }
    }
}
