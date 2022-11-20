/*---------------------------------------------------------------
    CRT(C Runtime Library) Simple Thread Example
    -- MainThread의 시작(1)/종료(2)에 따라 스레드가 시작/종료된다!
    -- 스레드를 클래스로 만들어보았다! (잘 작동한다!!)
    -- TODO : 프로그램도 클래스로 만들어보자! (싱글톤 패턴 적용!)
---------------------------------------------------------------*/
//CHeader
#include <Windows.h> //for HANDLE
#include <process.h> //for CRT-Thread
#include <conio.h>   //for getch
//CppHeader
#include <iostream>  //for cin/cout
//CustomHeader

using namespace std;

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
    _beginthreadex_proc_type mThreadFunc;
    //스레드 함수 파라미터 
    void* mThreadArgs;

    MyThread()
    {
        mThreadHandle = nullptr;
        mThreadState = MyThreadState::UNKNOWN;
        mThreadRunning = false;
        mThreadID = 0;
        mThreadFunc = nullptr;
        mThreadArgs = nullptr;
    }

    ~MyThread()
    {
        Finish();
        CloseHandle(mThreadHandle);
    }

    void Init(_beginthreadex_proc_type pThreadFunc,void* pArgs)
    {
        mThreadFunc = pThreadFunc;
        mThreadArgs = pArgs;
        mThreadState = MyThreadState::READY;
    }

    void Start()
    {
        if (mThreadFunc == nullptr || mThreadArgs == nullptr ||
            mThreadState != MyThreadState::READY)
        {
            return;
        }
        if (mThreadHandle) { CloseHandle(mThreadHandle); }
        mThreadHandle = (HANDLE)_beginthreadex(nullptr, 0, mThreadFunc, mThreadArgs, CREATE_SUSPENDED, &mThreadID);
        if (mThreadHandle)
        {
            //if Thread Creation Success...
            mThreadState = MyThreadState::START;
            mThreadRunning = true;
            ResumeThread(mThreadHandle);
            cout << "[Thread] Started!!" << endl;
        }
    }

    void Finish()
    {
        bool WaitCheckForever = false;
        if (mThreadState == MyThreadState::START)
        {
            mThreadRunning = false;
            if (WaitCheckForever)
            {
                //스레드 끝날때까지 영원히 기다린다..
                WaitForSingleObject(mThreadHandle, INFINITE);
                cout << "[Thread] Safe Stopped!!" << endl;
            }
            else
            {
                //스레드가 끝날때까지 1초 기다리고, 만약 안끝난다면 강제종료한다.
                if (WaitForSingleObject(mThreadHandle, 1000) != WAIT_OBJECT_0)
                {
                    TerminateThread(mThreadHandle, -1);
                    cout << "[Thread] Force Stopped!!" << endl;
                }
            }
            mThreadState = MyThreadState::READY;
        }
    }

    void Sleep(int milliseconds)
    {
        if (mThreadRunning == true)
        {
            WaitForSingleObject(mThreadHandle, milliseconds);
        }
    }
};

void PrintMenu2()
{
    system("cls");
    cout << "[main] 1. StartThread" << endl;
    cout << "[main] 2. StopThread" << endl;
    cout << "[main] 3. Exit" << endl;
    cout << "[main] Press Buttons : ";
}


unsigned _stdcall ThreadWorker1(void* args)
{
    MyThread* thisThread = (MyThread*)args;
    int repcnt = 0;
    while (thisThread->mThreadRunning)
    {
        cout << "[ThreadWorker1] repcnt = " << repcnt++ << endl;
        thisThread->Sleep(1000);
    }
    return 0;
}

int main(int argc, char* argv[])
{
    int command = 0;
    bool bExitCalled = false;
    bool bProgramRunning = false;
    MyThread* thread1 = new MyThread();

    thread1->Init(ThreadWorker1, thread1);
    while (!bExitCalled)
    {
        if (!bProgramRunning)
        {
            PrintMenu2();
        }
        cin >> command;
        switch (command)
        {
            case 1:
            {
                thread1->Start();
                bProgramRunning = true;
                break;
            }
            case 2:
            {
                thread1->Finish();
                bProgramRunning = false;
                Sleep(1000);
                break;
            }
            case 3:
            {
                if (!bProgramRunning)
                {
                    bExitCalled = true;
                }
                break;
            }
        }
    }

    delete(thread1);
    return 0;
}
