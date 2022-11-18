/*--------------------------------------------------------------
Mutex : 다른 프로세스의 뮤텍스를 찾아올 수 있다!

프로그램이 2개 실행될 때, 프로세스가 2개가 실행된다.

뮤텍스는 프로세스간 공유될 수 있기 때문에, 중복실행 방지 등의 로직을 짤때 쓴다.

뮤텍스는 커널 오브젝트이어서 다른 프로세스에서 접근가능하다. (핸들반환)

크리티컬 섹션은 유저모드에서 생성되는 객체이기 때문에 다른 프로세스에서 접근할 수 없다. 

--------------------------------------------------------------*/

#include <iostream>
#include <process.h>
#include <Windows.h>
#include <conio.h>

#pragma  comment(lib, "winmm.lib")

using namespace std;

HANDLE Global_MutexHandle;

CRITICAL_SECTION Global_CS;

int Global_Gold = 0;

unsigned WINAPI WorkerThread_MTX(void* Args)
{
    //HANDLE handle = *(HANDLE*)Args;
    for (int i = 0; i < 10000; i++)
    {
        WaitForSingleObject(Global_MutexHandle, INFINITE);
        Global_Gold++;
        ReleaseMutex(Global_MutexHandle);
    }
    //WaitForSingleObject(handle, 100);
    cout << Global_Gold << endl;
    return 0;
}

unsigned WINAPI WorkerThread_CS(void* Args)
{
    for (int i = 0; i < 10000; i++)
    {
        EnterCriticalSection(&Global_CS);
        Global_Gold++;
        LeaveCriticalSection(&Global_CS);
    }
    cout << Global_Gold << endl;
    return 0;
}

//int L20221118_Thread_main(int argc, char* argv[])
int main(int argc, char* argv[])
{
    HANDLE ThreadHandles[2];
    InitializeCriticalSection(&Global_CS);
    Global_MutexHandle = CreateMutex(nullptr, false, L"myprogram");

    if (Global_MutexHandle == nullptr || GetLastError() == ERROR_ALREADY_EXISTS)
    {
        cout << "이미 실행중입니다!" << endl;
        exit(-1);
    }
    
    int StartTime = timeGetTime();
    ThreadHandles[0] = (HANDLE)_beginthreadex(nullptr, 0, WorkerThread_MTX,0/*(void*)&ThreadHandles[0]*/, 0, nullptr);
    ThreadHandles[1] = (HANDLE)_beginthreadex(nullptr, 0, WorkerThread_MTX,0/*(void*)&ThreadHandles[1]*/, 0, nullptr);
    WaitForMultipleObjects(2, ThreadHandles, true, INFINITE);
    cout << "Elapsed : " << timeGetTime() - StartTime << "ms" << endl;

    StartTime = timeGetTime();
    ThreadHandles[0] = (HANDLE)_beginthreadex(nullptr, 0, WorkerThread_CS, 0/*(void*)&ThreadHandles[0]*/, 0, nullptr);
    ThreadHandles[1] = (HANDLE)_beginthreadex(nullptr, 0, WorkerThread_CS, 0/*(void*)&ThreadHandles[1]*/, 0, nullptr);
    WaitForMultipleObjects(2, ThreadHandles, true, INFINITE);
    cout << "Elapsed : " << timeGetTime() - StartTime << "ms" << endl;

    _getch();
    DeleteCriticalSection(&Global_CS);
    CloseHandle(Global_MutexHandle);
    
    return 0;
}