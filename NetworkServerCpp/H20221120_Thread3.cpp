/*---------------------------------------------------------------
    CRT(C Runtime Library) Simple Thread Example
    -- MainThread�� ����(1)/����(2)�� ���� �����尡 ����/����ȴ�!
    -- �����带 Ŭ������ �����Ҵ�! (�� �۵��Ѵ�!!)
    -- TODO : ���α׷��� Ŭ������ ������! (�̱��� ���� ����!)
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
    //������ �ڵ�
    HANDLE mThreadHandle;
    //������ �������
    MyThreadState mThreadState;
    //������ ���ۻ���(while-true)
    bool mThreadRunning; 
    //������ ID
    unsigned int mThreadID;
    //������ �Լ�
    _beginthreadex_proc_type mThreadFunc;
    //������ �Լ� �Ķ���� 
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
                //������ ���������� ������ ��ٸ���..
                WaitForSingleObject(mThreadHandle, INFINITE);
                cout << "[Thread] Safe Stopped!!" << endl;
            }
            else
            {
                //�����尡 ���������� 1�� ��ٸ���, ���� �ȳ����ٸ� ���������Ѵ�.
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
