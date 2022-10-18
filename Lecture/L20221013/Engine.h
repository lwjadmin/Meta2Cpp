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
    //상속을 위한 virtual 처리(소멸자는 virtual 권장)
    virtual ~Engine();
    virtual void BeginPlay();
    virtual void EndPlay();
    //abstract
    virtual void Initialize() = 0;
    //abstract
    virtual void Terminalize() = 0;
    //무한루프 시작
    void Run();
    //무한루프 종료
    void QuitGame();
    //레벨에 있는 모든 액터 가져오기
    vector<class AActor*>& GetAllActors();
    //SDL(Simple DirectMedia Layer) 윈도우 & 렌더러 메모리 로드
    void SDLInitialize(int tileSize, int XSize, int YSize);
    //SDL(Simple DirectMedia Layer) 윈도우 & 렌더러 메모리 제거
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
    //맵 로딩
    bool LoadLevel(string MapFilename);
    void UnloadLevel();
    //ZOrder로 액터 정렬
    void SortActor();
    //월드 포인터 (이 엔진은 하나의 월드만 가진다.)
    FWorld* MyWorld;
    //엔진 무한루프 Exit용 플래그
    bool bIsRunning;

    Uint64 LastTick;
    Uint64 DeltaSeconds;
public:
    inline const Uint64 GetWorldDeltaSeconds() { return DeltaSeconds; }
};


