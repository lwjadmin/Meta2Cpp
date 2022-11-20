#include "MyThread.h"


MyThread::MyThread()
{
    mThreadHandle = nullptr;
    mThreadState = MyThreadState::UNKNOWN;
    mThreadRunning = false;
    mThreadID = 0;
    mThreadFunc = nullptr;
    mThreadArgs = nullptr;
}

MyThread::~MyThread()
{
    Finish();
    CloseHandle(mThreadHandle);
}

void MyThread::Init(lpThreadFunc InThreadFunc, void* InArgs)
{
    mThreadFunc = InThreadFunc;
    mThreadArgs = InArgs;
    mThreadState = MyThreadState::READY;
}

bool MyThread::Start()
{
    if (mThreadFunc == nullptr || mThreadArgs == nullptr ||
        mThreadState != MyThreadState::READY)
    {
        return false;
    }
    if (mThreadHandle) { CloseHandle(mThreadHandle); }
    mThreadHandle = (HANDLE)_beginthreadex(nullptr, 0, mThreadFunc, mThreadArgs, CREATE_SUSPENDED, &mThreadID);
    if (mThreadHandle)
    {
        //if Thread Creation Success...
        mThreadState = MyThreadState::START;
        mThreadRunning = true;
        ResumeThread(mThreadHandle);
        //cout << "[Thread] Started!!" << endl;
    }
    return true;
}

bool MyThread::Finish()
{
    bool WaitCheckForever = false;
    if (mThreadState == MyThreadState::START)
    {
        mThreadRunning = false;
        if (WaitCheckForever)
        {
            //������ ���������� ������ ��ٸ���..
            WaitForSingleObject(mThreadHandle, INFINITE);
            //cout << "[Thread] Safe Stopped!!" << endl;
        }
        else
        {
            //�����尡 ���������� 1�� ��ٸ���, ���� �ȳ����ٸ� ���������Ѵ�.
            if (WaitForSingleObject(mThreadHandle, 1000) != WAIT_OBJECT_0)
            {
                TerminateThread(mThreadHandle, -1);
                //cout << "[Thread] Force Stopped!!" << endl;
            }
        }
        mThreadState = MyThreadState::READY;
        return true;
    }
    return false;
}

void MyThread::Sleep(int milliseconds)
{
    if (mThreadRunning == true)
    {
        WaitForSingleObject(mThreadHandle, milliseconds);
    }
}