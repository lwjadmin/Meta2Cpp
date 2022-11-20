#include "MyProgram.h"


static unsigned __stdcall ThreadWorker1(void* pArgs)
{
    MyProgram* thisProgram = (MyProgram*)pArgs;
    MyThread* thisThread = thisProgram->mThreadMap["ThreadWorker1"];

    EnterCriticalSection(&thisProgram->csnumber);
    for (int i = 0; i < 100000; i++)
    {
        thisProgram->number = thisProgram->number - 1;
    }
    LeaveCriticalSection(&thisProgram->csnumber);
    return 0;
}

static unsigned __stdcall ThreadWorker2(void* pArgs)
{
    MyProgram* thisProgram = (MyProgram*)pArgs;
    MyThread* thisThread = thisProgram->mThreadMap["ThreadWorker2"];

    EnterCriticalSection(&thisProgram->csnumber);
    for (int i = 0; i < 100000; i++)
    {
        thisProgram->number = thisProgram->number + 1;
    }
    LeaveCriticalSection(&thisProgram->csnumber);
    return 0;
}

MyProgram::MyProgram()
{
    InitializeCriticalSection(&csnumber);
}
MyProgram::~MyProgram()
{
    DeleteCriticalSection(&csnumber);
}

void MyProgram::Init()
{
    number = 0;
    MyThread* t1 = new MyThread();
    t1->Init(ThreadWorker1, this);
    mThreadMap["ThreadWorker1"] = t1;
    MyThread* t2 = new MyThread();
    t2->Init(ThreadWorker2, this);
    mThreadMap["ThreadWorker2"] = t2;
}

void MyProgram::Start()
{
    for (auto itr = mThreadMap.begin(); itr != mThreadMap.end(); itr++)
    {
        itr->second->Start();
    }
}

void MyProgram::Finish()
{
    for (auto itr = mThreadMap.rbegin(); itr != mThreadMap.rend(); itr++)
    {
        itr->second->Finish();
    }
}
