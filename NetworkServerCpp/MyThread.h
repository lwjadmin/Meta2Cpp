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
    //������ �ڵ�
    HANDLE mThreadHandle;
    //������ �������
    MyThreadState mThreadState;
    //������ ���ۻ���(while-true)
    bool mThreadRunning;
    //������ ID
    unsigned int mThreadID;
    //������ �Լ�
    lpThreadFunc mThreadFunc;
    //������ �Լ� �Ķ���� 
    void* mThreadArgs;

    MyThread();
    ~MyThread();
    void Init(lpThreadFunc InThreadFunc, void* InArgs);
    bool Start();
    bool Finish();
    void Sleep(int milliseconds);
};