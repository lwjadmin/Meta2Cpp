#include <fstream>
#include <algorithm>
#include <iostream>

#include "Engine.h"
#include "World.h"
#include "Player.h"
#include "Floor.h"
#include "Wall.h"
#include "Goal.h"
#include "Monster.h"
#include "Text.h"
#include "SoundActor.h"

using namespace std;

Engine::Engine()
    :
    MyWindow(nullptr),
    MyRenderer(nullptr),
    MyGameState(nullptr),
    MyWorld(nullptr),
    bIsRunning(false),
    LastTick(0),
    DeltaSeconds(0)
{
    do
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { break; }
        if (TTF_Init() != 0) { break; }
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) { break; }
        bIsRunning = true;
    } while (false);

    if (!bIsRunning)
    {
        SDL_Log("SDL Loading Failed. Engine Unloaded.");
        exit(-1);
    }
    else
    {
        MyGameState = new FGameState();
    }
}

void Engine::SDLInitialize(int TilePixelSize, int XWidth, int YHeight)
{
	/*------------------------------------------------------------------------
	SDL_WINDOW_VULKAN : Vulkan 사용
	SDL_WINDOW_OPENGL : OpenGL 사용
	------------------------------------------------------------------------*/
	MyWindow = SDL_CreateWindow("2DSpriteGame", 100, 100, (TilePixelSize * XWidth), (TilePixelSize * YHeight), SDL_WINDOW_VULKAN);
	
	/*-----------------------------------------------------------------------
	SDL_RENDERER_SOFTWARE    : CPU 렌더링
	SDL_RENDERER_ACCELERATED : GPU 렌더링
	-----------------------------------------------------------------------*/
	MyRenderer = SDL_CreateRenderer(MyWindow, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_TARGETTEXTURE);
}

void Engine::SDLTerminate()
{
	SDL_DestroyRenderer(MyRenderer); //SAFE_DELETE 내장
	SDL_DestroyWindow(MyWindow); //SAFE_DELETE 내장
}

void Engine::SpawnActor(AActor* NewActor)
{
    if (MyWorld)
    {
        MyWorld->SpawnActor(NewActor);
    }
}

Engine::~Engine()
{
    if (MyWorld) { delete MyWorld; MyWorld = nullptr; SDLTerminate(); }
    if (MyGameState) { delete MyGameState; MyGameState = nullptr; }
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}

void Engine::BeginPlay()
{
    if (bIsRunning) { MyWorld->BeginPlay(); }
}

void Engine::EndPlay()
{
    if (bIsRunning) { MyWorld->EndPlay(); }
}

void Engine::Run()
{
    BeginPlay();
    while (bIsRunning)
    {
        DeltaSeconds = SDL_GetTicks64() - LastTick;
        Input();
        SDL_Log(to_string(MyWorld->ActorList.size()).c_str());
        Tick();
        LastTick = SDL_GetTicks64();
        Render();
    }
    EndPlay();
}

void Engine::QuitGame()
{
	bIsRunning = false;
}

bool GetMapSize(string MapFileName, int* OutXWidth, int* OutYHeight)
{
    ifstream MapFile(MapFileName);
    bool bOpenSuccess = false;
    int XWidth = 0;
    int YHeight = 0;
    if (MapFile.fail())
    {
        cout << "MapFile Not Found, Can't Get MapSize" << endl;
        XWidth = YHeight = -1;
    }
    else
    {
        char Data[100] = { 0, };
        while (MapFile.getline(Data, sizeof(Data)))
        {
            if (YHeight == 0) { XWidth = (int)strlen(Data); }
            YHeight++;
        }
        bOpenSuccess = true;
        *OutXWidth = XWidth;
        *OutYHeight = YHeight;
    }
    return bOpenSuccess;
}

void Engine::UnloadLevel()
{
    SDLTerminate();
    if (MyWorld)
    {
        MyWorld->Terminate();
        delete MyWorld;
    }
    
    
}

bool Engine::LoadLevel(string MapFilename)
{
    bool bLoadSuccess = false;
	int MapXWidth = 0;
	int MapYHeight = 0;

    if (GetMapSize(MapFilename, &MapXWidth, &MapYHeight))
    {
        UnloadLevel();
        char Data[100] = { 0, };
        ifstream MapFile(MapFilename);
        MyWorld = new FWorld();
        SDLInitialize(60, MapXWidth, MapYHeight);
        int Y = 0;
        while (MapFile.getline(Data, sizeof(Data)))
        {
            for (int X = 0; X < strlen(Data); ++X)
            {
                if (Data[X] == '*')
                {
                    MyWorld->SpawnActor(new AWall(X, Y));
                    MyWorld->SpawnActor(new AFloor(X, Y));
                }
                else if (Data[X] == 'P')
                {
                    MyWorld->SpawnActor(new APlayer(X, Y));
                    MyWorld->SpawnActor(new AFloor(X, Y));
                }
                else if (Data[X] == 'G')
                {
                    MyWorld->SpawnActor(new AGoal(X, Y));
                    MyWorld->SpawnActor(new AFloor(X, Y));
                }
                else if (Data[X] == ' ')
                {
                    MyWorld->SpawnActor(new AFloor(X, Y));
                }
                else if (Data[X] == 'M')
                {
                    MyWorld->SpawnActor(new AMonster(X, Y));
                    MyWorld->SpawnActor(new AFloor(X, Y));
                }
            }
            Y++;
        }
        MapFile.close();
        SortActor();
        SpawnActor(new ASoundActor("./data/bgm.mp3", true));
        bLoadSuccess = true;
        MyGameState->bPlayerCanMove = true;
    }
    return bLoadSuccess;
}

void Engine::SortActor()
{
	sort(MyWorld->ActorList.begin(), MyWorld->ActorList.end(), AActor::Compare);
}

vector<AActor*>& Engine::GetAllActors()
{
	return MyWorld->ActorList;
}

void Engine::Input()
{
	SDL_PollEvent(&MyEvent);
}

void Engine::Tick()
{
	if (MyEvent.type == SDL_QUIT)
	{
		bIsRunning = false;
	}
	MyWorld->Tick();
}

void Engine::Render()
{
    SDL_Color BackgroundColor = { 0, 0, 0 ,0 };
    SDL_SetRenderDrawColor(MyRenderer, BackgroundColor.r, BackgroundColor.g, BackgroundColor.b, BackgroundColor.a);
    SDL_RenderClear(MyRenderer);
    if (MyWorld) { MyWorld->Render(); }
    SDL_RenderPresent(MyRenderer);
}
