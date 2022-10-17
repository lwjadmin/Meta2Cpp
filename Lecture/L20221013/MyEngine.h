#pragma once
#include "Engine.h"
#include <random>

class MyEngine : public Engine
{
private:
    MyEngine();
public:
    //����� ���� Virtual ó��
    virtual ~MyEngine();
    virtual void Initialize() override;
    virtual void Terminalize() override;
    //Singleton Pattern, �ѹ��� ����
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
    //�̱��� �ν��Ͻ�, MyEngine.cpp���� Nullptr�� �ʱ�ȭ���ش�. 
    static MyEngine* Instance;
};

#define GEngine	MyEngine::GetEngine()

