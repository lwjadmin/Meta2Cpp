#pragma once
#include <string>
#include <vector>
//----------------------------------------------------------------
#include "GameState.h"
//include SDL(Simple DirectMedia Layer) Header
#include "SDL.h"
//include SDL(Simple DirectMedia Layer) Text Plugin Header
#include "SDL_ttf.h"
//include SDL(Simple DirectMedia Layer) Sound Plugin Header
#include "SDL_mixer.h"
//----------------------------------------------------------------
//link SDL(Simple DirectMedia Layer) Library
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2.lib")
//include SDL(Simple DirectMedia Layer) Text Plugin Library
#pragma comment(lib, "SDL2_ttf.lib")
//include SDL(Simple DirectMedia Layer) Sound Plugin Library
#pragma comment(lib, "SDL2_mixer.lib")

using namespace std;

class FWorld;

class Engine
{
public:
    Engine();
    //����� ���� virtual ó��(�Ҹ��ڴ� virtual ����)
    virtual ~Engine();
    virtual void BeginPlay();
    virtual void EndPlay();
    //abstract
    virtual void Initialize() = 0;
    //abstract
    virtual void Terminalize() = 0;
    //���ѷ��� ����
    void Run();
    //���ѷ��� ����
    void QuitGame();
    //������ �ִ� ��� ���� ��������
    vector<class AActor*>& GetAllActors();
    //SDL(Simple DirectMedia Layer) ������ & ������ �޸� �ε�
    void SDLInitialize(int tileSize, int XSize, int YSize);
    //SDL(Simple DirectMedia Layer) ������ & ������ �޸� ����
    void SDLTerminate();
    void SpawnActor(AActor* NewActor);
    SDL_Window* MyWindow;
    SDL_Renderer* MyRenderer;
    SDL_Event MyEvent;
    FGameState* MyGameState;
    FWorld* GetWorld() { return MyWorld; }

protected:
    virtual void Input();
    virtual void Tick();
    virtual void Render();
    //�� �ε�
    bool LoadLevel(string MapFilename);
    void UnloadLevel();
    //ZOrder�� ���� ����
    void SortActor();
    //���� ������ (�� ������ �ϳ��� ���常 ������.)
    FWorld* MyWorld;
    //���� ���ѷ��� Exit�� �÷���
    bool bIsRunning;

    Uint64 LastTick;
    Uint64 DeltaSeconds;
public:
    inline const Uint64 GetWorldDeltaSeconds() { return DeltaSeconds; }
};


