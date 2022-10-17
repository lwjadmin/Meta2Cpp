#pragma once
#include <string>
#include <vector>

//link SDL(Simple DirectMedia Layer) Library
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2.lib")

//include SDL(Simple DirectMedia Layer) Header
#include "SDL.h"

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

    inline static int GetKeyCode()
    {
        return KeyCode;
    }
    //������ �ִ� ��� ���� ��������
    vector<class AActor*>& GetAllActors();
    //SDL(Simple DirectMedia Layer) ������ & ������ �޸� �ε�
    void SDLInitialize();
    //SDL(Simple DirectMedia Layer) ������ & ������ �޸� ����
    void SDLTerminate();
    SDL_Window* MyWindow;
    SDL_Renderer* MyRenderer;
    SDL_Event MyEvent;
protected:
    virtual void Input();
    virtual void Tick();
    virtual void Render();
    //�� �ε�
    void Load(string MapFileName);
    //ZOrder�� ���� ����
    void SortActor();
    //���� ������ (�� ������ �ϳ��� ���常 ������.)
    FWorld* MyWorld;
    //�Է�Ű�ڵ�(getch��)
    static int KeyCode;
    //���� ���ѷ��� Exit�� �÷���
    bool bIsRunning;

    Uint64 LastTick;
    Uint64 DeltaSeconds;
public:
    inline const Uint64 GetWorldDeltaSeconds() { return DeltaSeconds; }
};


