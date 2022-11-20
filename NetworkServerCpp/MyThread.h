#pragma once
#include <Windows.h> //for HANDLE
#include <process.h> //for CRT-Thread

typedef unsigned(__stdcall* lpThreadFunc)(void*);

enum class MyThreadState : int
{
    UNKNOWN = 0,
    READY = 1,
    START = 2
};

class MyThread
{
public:
    //스레드 핸들
    HANDLE mThreadHandle;
    //스레드 현재상태
    MyThreadState mThreadState;
    //스레드 동작상태(while-true)
    bool mThreadRunning;
    //스레드 ID
    unsigned int mThreadID;
    //스레드 함수
    lpThreadFunc mThreadFunc;
    //스레드 함수 파라미터 
    void* mThreadArgs;

    MyThread();
    ~MyThread();
    void Init(lpThreadFunc InThreadFunc, void* InArgs);
    bool Start();
    bool Finish();
    void Sleep(int milliseconds);
};