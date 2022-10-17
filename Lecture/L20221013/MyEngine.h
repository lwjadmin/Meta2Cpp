#pragma once
#include "Engine.h"
#include <random>

class MyEngine : public Engine
{
private:
    MyEngine();
public:
    //상속을 위한 Virtual 처리
    virtual ~MyEngine();
    virtual void Initialize() override;
    virtual void Terminalize() override;
    //Singleton Pattern, 한번만 생성
    static inline MyEngine* GetEngine()
    {
        if (Instance == nullptr)
        {
            new MyEngine();
        }
        return Instance;
    }
    int GetRandNumber(int MinValue, int MaxValue);
protected:
    //싱글톤 인스턴스, MyEngine.cpp에서 Nullptr로 초기화해준다. 
    static MyEngine* Instance;
};

#define GEngine	MyEngine::GetEngine()

