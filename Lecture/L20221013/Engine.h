#pragma once
#include <string>

class FWorld;

class Engine
{
public:
    Engine();
    virtual ~Engine();
    virtual void Initialize() = 0;
    virtual void Terminalize() = 0;
    void Run();
protected:
    virtual void Input();
    virtual void TickProcess();
    virtual void Render();
    FWorld* World;
};

class MyEngine : public Engine
{
public:
    MyEngine() {}
    ~MyEngine() {}
    virtual void Initialize() override;
    virtual void Terminalize() override;
};
