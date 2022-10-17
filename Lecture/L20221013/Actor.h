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
    //Actor ������
    AActor();
    //Actor ������, X,Y��ǥ ����
    AActor(int NewX, int NewY);
    //Actor �Ҹ���, ����� ���� virtualó��
    virtual ~AActor();
    //Actor Window / Console UI Render
    virtual void Render();
    //Actor �����Ӵ� ó�� �Լ�
    virtual void Tick();
    //Actor �ʱ�ȭ
    virtual void BeginPlay();
    //Actor �Ҹ�
    virtual void EndPlay();

    //X��(0~1920)
    int X;
    //Y��(0~1080)
    int Y;
    //���ü���
    int ZOrder;
    //�ܼ����ø��
    char Shape;
    //Windowâ Actor Ÿ��ũ��(�̹����� ���� ���)
    int TileSize;
    //Windowâ Actor ����
    SDL_Color MyColor;
    //Windowâ Actor ��������(Opacity ó����)
    SDL_Color MyColorKey;
    //Actor Collision Check Type
    ECollisionType CollisionType;
    //RAM(�޸�)�� �ö� �ؽ���
    SDL_Surface* MySurface;
    //VRAM(�׷���ī�� �޸�)�� �ö� �ؽ���
    SDL_Texture* MyTexture; 

    //ZOrder Vector �񱳿���
    bool operator<(AActor& RHS)
    {
        return (this->ZOrder) < (RHS.ZOrder);
    }
    //ZOrder Vector �񱳿���
    static inline bool Compare(AActor* First, AActor* Second)
    {
        return (First->ZOrder) < (Second->ZOrder);
    }
    //���� BMP ���� �ε� �Լ�
    void LoadBMP(string FileName);
    //CollisionCheck �Լ�
    virtual bool CheckHit(AActor* Other);
};


