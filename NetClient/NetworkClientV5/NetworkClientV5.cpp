#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <process.h>

#include <string>
#include <iostream>
#include <map>
#include <queue>

using namespace std;

#pragma comment(lib, "WS2_32.lib") 



typedef unsigned(__stdcall* lpThreadFunc)(void*);
enum class MyThreadState : unsigned short
{
    Unknown = 0,
    Ready = 1,
    Start = 2,
    //Wait = 3, 
    Stop = 4
};

class MyThread
{
public:
    HANDLE mHandle;
    unsigned int mThreadID;
    string mThreadName;
    lpThreadFunc mThreadFunc;
    void* mThreadFuncParam;
    bool mIsRunning;
    MyThreadState mThreadState;

    MyThread()
    {
        mHandle = nullptr;
        mThreadID = 0;
        mThreadName = "";
        mThreadFunc = nullptr;
        mThreadFuncParam = nullptr;
        mIsRunning = false;
        mThreadState = MyThreadState::Unknown;
    }

    MyThread(string InThreadName, lpThreadFunc InThreadFunc, void* InThreadFuncParam) : MyThread()
    {
        Init(InThreadName, InThreadFunc, InThreadFuncParam);
        mHandle = (HANDLE)_beginthreadex(nullptr, 0, mThreadFunc, mThreadFuncParam, CREATE_SUSPENDED, &mThreadID);
        mThreadState = MyThreadState::Ready;
    }

    ~MyThread()
    {
        Stop();
        CloseHandle(mHandle);
    }

    void Init(string InThreadName, lpThreadFunc InThreadFunc, void* InThreadFuncParam)
    {
        mThreadName = InThreadName;
        mThreadFunc = InThreadFunc;
        mThreadFuncParam = InThreadFuncParam;
    }

    void Start()
    {
        if (mThreadState == MyThreadState::Ready || mThreadState == MyThreadState::Stop)
        {
            ResumeThread(mHandle);
            mIsRunning = true;
            mThreadState = MyThreadState::Start;
        }
    }

    //void Wait()
    //{
    //    if (mThreadState == MyThreadState::Start)
    //    {
    //        SuspendThread(mHandle);
    //        mThreadState = MyThreadState::Wait;
    //    }
    //}
    //
    //void Resume()
    //{
    //    if (mThreadState == MyThreadState::Wait)
    //    {
    //        ResumeThread(mHandle);
    //        mThreadState = MyThreadState::Start;
    //    }
    //}

    void Stop(bool ForceStop = false)
    {
        if (mThreadState == MyThreadState::Start)
        {
            mIsRunning = false;
            if (!ForceStop)
            {
                WaitForSingleObject(mHandle, INFINITE);
            }
            else
            {
                //1초만 기다리고 종료해버린다.
                WaitForSingleObject(mHandle, 1000);
                TerminateThread(mHandle, -1);
            }
            mThreadState = MyThreadState::Stop;
        }
    }

    void Sleep(int milliseconds)
    {
        if (mThreadState == MyThreadState::Start && mIsRunning)
        {
            WaitForSingleObject(mHandle, milliseconds);
        }
    }
};

class MyThreadPool
{
public:
    vector<MyThread*> mThreadList;
    MyThreadPool()
    {

    }
    ~MyThreadPool()
    {
        for (int i = mThreadList.size() - 1; i >= 0; --i)
        {
            delete(mThreadList[i]);
        }
    }

    MyThread* operator[](int idx)
    {
        MyThread* retval = nullptr;

        if (idx < 0 || idx >= mThreadList.size())
        {
            retval = mThreadList[idx];
        }
        return retval;
    }

    MyThread* operator[](string InThreadName)
    {
        MyThread* retval = nullptr;
        for (int i = 0; i < mThreadList.size(); ++i)
        {
            if (InThreadName == mThreadList[i]->mThreadName)
            {
                retval = mThreadList[i];
            }
        }
        return retval;
    }

    void Add(string InThreadName, lpThreadFunc InThreadFunc, void* InThreadFuncParam)
    {
        MyThread* thread = new MyThread(InThreadName, InThreadFunc, InThreadFuncParam);
        mThreadList.push_back(thread);
    }

    void Remove(string InThreadName)
    {
        for (int i = 0; i < mThreadList.size(); ++i)
        {
            if (mThreadList[i]->mThreadName == InThreadName)
            {
                mThreadList.erase(mThreadList.begin() + i);
                break;
            }
        }
    }

    void Remove(int idx)
    {
        if (idx < 0 || idx >= mThreadList.size())
        {
            mThreadList.erase(mThreadList.begin() + idx);
        }
    }

    void Start()
    {
        for (int i = 0; i < mThreadList.size(); i++)
        {
            mThreadList[i]->Start();
        }
    }

    void Stop()
    {
        for (int i = 0; i < mThreadList.size(); i++)
        {
            mThreadList[i]->Stop();
        }
    }
};



class MyQueue
{
public:
    queue<pair<int, void*>> mQ;
    CRITICAL_SECTION mCSQ;

    MyQueue()
    {
        InitializeCriticalSection(&mCSQ);
    }
    ~MyQueue()
    {
        if (!IsEmpty()) { Clear(); }
        DeleteCriticalSection(&mCSQ);
    }

    void Push(int InMsgHead, void* InData)
    {
        EnterCriticalSection(&mCSQ);
        mQ.push(make_pair(InMsgHead, InData));
        LeaveCriticalSection(&mCSQ);
    }

    void Pop()
    {
        EnterCriticalSection(&mCSQ);
        mQ.pop();
        LeaveCriticalSection(&mCSQ);
    }

    //메모리 삭제는 쓰는쪽에서 하기!
    pair<int, void*>* Front()
    {
        EnterCriticalSection(&mCSQ);
        pair<int, void*>* val = &mQ.front();
        LeaveCriticalSection(&mCSQ);
        return val;
    }

    bool IsEmpty() {
        return mQ.empty();
    }

    int Size()
    {
        return (int)mQ.size();
    }

    void Clear()
    {
        EnterCriticalSection(&mCSQ);
        while (!mQ.empty()) { 
            pair<int, void*> val = mQ.front();
            delete(val.second);
            mQ.pop(); 
        }
        LeaveCriticalSection(&mCSQ);
    }
};

bool G_ProgramRunning = true;
MyThreadPool ThreadPool;
MyQueue SendQueue;

unsigned ThreadWorker1(void* args)
{
    int icnt = 0;
    MyThread* thisthread = ThreadPool["A_HANDLE"];
    while (thisthread->mIsRunning)
    {
        thisthread->Sleep(10);
        int* ival = new int();
        *ival = ++icnt;
        SendQueue.Push(2, (void*)ival);
    }
    cout << "ThreadWorker1 ThreadExit!" << endl;
    return 0;
}

unsigned ThreadWorker2(void* args)
{
    MyThread* thisthread = ThreadPool["B_HANDLE"];
    while (thisthread->mIsRunning)
    {
        if(SendQueue.IsEmpty()){ thisthread->Sleep(1); }
        while (!SendQueue.IsEmpty())
        {
            pair<int, void*>* msg = SendQueue.Front();
            int header =  (*msg).first;
            void* vptr = (*msg).second;
            switch (header)
            {
                case 1:
                {
                    char* buf = (char*)vptr;
                    cout << buf << endl;
                    delete(buf);
                    break;
                }
                case 2:
                {
                    int* ival = (int*)vptr;
                    cout << "ival : " << *ival << endl;
                    delete(ival);
                    break;
                }
            }
            SendQueue.Pop();
        }
    }
    cout << "ThreadWorker2 ThreadExit!" << endl;
    return 0;
}

unsigned ThreadWorker3(void* args)
{
    MyThread* thisthread = ThreadPool["C_HANDLE"];
    while (thisthread->mIsRunning)
    {
        char buf[100] = { 0, };
        cin >> buf;
        if (strcmp(buf, "q") == 0)
        {
            G_ProgramRunning = false;
            break;
        }
        char* pbuf = new char[sizeof(buf)];
        memset(pbuf, 0, sizeof(buf));
        memcpy(pbuf, buf, sizeof(buf));
        SendQueue.Push(1,(void*)pbuf);
    }
    cout << "ThreadWorker3 ThreadExit!" << endl;
    return 0;
}

int main(int argc, char* argv[])
{
    ThreadPool.Add("A_HANDLE", ThreadWorker1, nullptr);
    ThreadPool.Add("B_HANDLE", ThreadWorker1, nullptr);
    ThreadPool.Add("C_HANDLE", ThreadWorker1, nullptr);
    ThreadPool.Add("D_HANDLE", ThreadWorker1, nullptr);
    ThreadPool.Add("E_HANDLE", ThreadWorker1, nullptr);
    ThreadPool.Add("F_HANDLE", ThreadWorker1, nullptr);
    ThreadPool.Add("G_HANDLE", ThreadWorker1, nullptr);
    ThreadPool.Add("H_HANDLE", ThreadWorker1, nullptr);
    ThreadPool.Add("I_HANDLE", ThreadWorker1, nullptr);
    ThreadPool.Add("J_HANDLE", ThreadWorker1, nullptr);
    ThreadPool.Add("K_HANDLE", ThreadWorker1, nullptr);
    ThreadPool.Add("L_HANDLE", ThreadWorker1, nullptr);
    ThreadPool.Add("M_HANDLE", ThreadWorker1, nullptr);
    ThreadPool.Add("N_HANDLE", ThreadWorker2, nullptr);
    ThreadPool.Add("O_HANDLE", ThreadWorker3, nullptr);
    ThreadPool.Start();

    while (G_ProgramRunning)
    {
        Sleep(1);
    }
    ThreadPool.Stop();

    return 0;
}
