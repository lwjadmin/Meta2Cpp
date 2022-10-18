#pragma once
#include <string>

#include "Actor.h"
#include "SDL_mixer.h"


class ASoundActor : public AActor
{
public:
    ASoundActor();
    ASoundActor(string InFileName, bool InIsLoop);
    ~ASoundActor();
    

    string FileName;
    int Volume;
    bool bIsLoop;

    void Play();
    void Stop();

    virtual void BeginPlay() override;
    virtual void Render() override;
    virtual void Tick() override;
    Mix_Music* Music; //������ ���� ��
    Mix_Chunk* Sound; //�Ҹ�
    Uint64 ElapsedTime = 0;
    Uint64 ExecuteTime = 0;
};

