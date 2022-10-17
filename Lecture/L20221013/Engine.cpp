#include <conio.h>
#include "Engine.h"
#include "World.h"
#include "Player.h"

Engine::Engine()
{
    World = new FWorld();
}

Engine::~Engine()
{
    delete World;
}

void Engine::Run()
{
    bool bCalledOnce = false;

    while (true)
    {
        if (!bCalledOnce)
        {
            Render();
            bCalledOnce = true;
        }
        Input(); //�Է¹ޱ�
        TickProcess(); //����ó��, ��ġó��
        Render(); //�׸���
    }
}

void Engine::Input()
{
    int KeyCode = _getch();
    for (auto it = World->ActorList.begin(); it != World->ActorList.end(); it++)
    {
        APlayer* p = dynamic_cast<APlayer*>(*it);
        if (p) { p->OnPressKey(KeyCode); break; }
    }
}

void Engine::TickProcess()
{
    World->Tick();
}

void Engine::Render()
{
    World->Render();
}


void MyEngine::Initialize()
{
    World->Load("Level1.txt");
}

void MyEngine::Terminalize()
{

}

