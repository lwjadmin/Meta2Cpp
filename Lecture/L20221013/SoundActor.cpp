#include "SoundActor.h"
#include "World.h"
#include "MyEngine.h"

ASoundActor::ASoundActor() : Volume(100), bIsLoop(false)
{
    Music = nullptr;
    Sound = nullptr;
    Volume = 30;
    ExecuteTime = 200;
    ElapsedTime = 0;
}

ASoundActor::~ASoundActor()
{

}

ASoundActor::ASoundActor(string InFileName, bool InIsLoop)
{
    FileName = InFileName;
    bIsLoop = InIsLoop;
    if (InIsLoop)
    {
        Music = Mix_LoadMUS(FileName.c_str());
    }
    else
    {
        Sound = Mix_LoadWAV(FileName.c_str());
    }
}

void ASoundActor::Play()
{
    if (Music)
    {
        Mix_PlayMusic(Music, bIsLoop);
    }
    if (Sound)
    {
        Mix_PlayChannel(-1,Sound,false);
    }
}

void ASoundActor::Stop()
{
    if (Music)
    {
        Mix_HaltMusic();
    }
    if (Sound)
    {
        Mix_HaltChannel(-1);
    }
}

void ASoundActor::BeginPlay()
{
    if (Music) 
    {
        Play();
    }
    if (Sound)
    {
        Play();
    }
}

void ASoundActor::Render()
{
}

void ASoundActor::Tick()
{
    ElapsedTime += GEngine->GetWorldDeltaSeconds();
    if (!bIsLoop && ElapsedTime > ExecuteTime)
    {
        ElapsedTime = 0;
        GEngine->GetWorld()->DestroyActor(this);
    }
}
