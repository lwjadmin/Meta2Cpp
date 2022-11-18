/*--------------------------------------------------------------
Mutex : �ٸ� ���μ����� ���ؽ��� ã�ƿ� �� �ִ�!

���α׷��� 2�� ����� ��, ���μ����� 2���� ����ȴ�.

���ؽ��� ���μ����� ������ �� �ֱ� ������, �ߺ����� ���� ���� ������ ©�� ����.

���ؽ��� Ŀ�� ������Ʈ�̾ �ٸ� ���μ������� ���ٰ����ϴ�. (�ڵ��ȯ)

ũ��Ƽ�� ������ ������忡�� �����Ǵ� ��ü�̱� ������ �ٸ� ���μ������� ������ �� ����. 

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
        cout << "�̹� �������Դϴ�!" << endl;
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