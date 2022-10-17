#pragma once
#include "SDL.h"
#include <string>

using namespace std;

enum class ECollisionType
{
    NoCollision = 0,                             // 0000 0000
    QueryOnly = 1,                               // 0000 0001
    PhysicsOnly = 2,                             // 0000 0010
    CollisionEnable = (QueryOnly | PhysicsOnly), // 0000 0011
};

class AActor
{
public:
    //Actor 생성자
    AActor();
    //Actor 생성자, X,Y좌표 지정
    AActor(int NewX, int NewY);
    //Actor 소멸자, 상속을 위해 virtual처리
    virtual ~AActor();
    //Actor Window / Console UI Render
    virtual void Render();
    //Actor 프레임당 처리 함수
    virtual void Tick();
    //Actor 초기화
    virtual void BeginPlay();
    //Actor 소멸
    virtual void EndPlay();

    //X축(0~1920)
    int X;
    //Y축(0~1080)
    int Y;
    //전시순서
    int ZOrder;
    //콘솔전시모양
    char Shape;
    //Window창 Actor 타일크기(이미지가 없을 경우)
    int TileSize;
    //Window창 Actor 색상
    SDL_Color MyColor;
    //Window창 Actor 반전색상(Opacity 처리할)
    SDL_Color MyColorKey;
    //Actor Collision Check Type
    ECollisionType CollisionType;
    //RAM(메모리)에 올라갈 텍스쳐
    SDL_Surface* MySurface;
    //VRAM(그래픽카드 메모리)에 올라갈 텍스쳐
    SDL_Texture* MyTexture; 

    //ZOrder Vector 비교연산
    bool operator<(AActor& RHS)
    {
        return (this->ZOrder) < (RHS.ZOrder);
    }
    //ZOrder Vector 비교연산
    static inline bool Compare(AActor* First, AActor* Second)
    {
        return (First->ZOrder) < (Second->ZOrder);
    }
    //렌더 BMP 파일 로드 함수
    void LoadBMP(string FileName);
    //CollisionCheck 함수
    virtual bool CheckHit(AActor* Other);
};


