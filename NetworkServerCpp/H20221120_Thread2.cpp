/*---------------------------------------------------------------
    CRT(C Runtime Library) Simple Thread Example
    -- MainThread�� ����(1)/����(2)�� ���� �����尡 ����/����ȴ�!
    -- 1���� �����带 ���� �۷ι��� ������ �����ؾ� �ϴ� �������� �ִ�.
    -- �����带 Ŭ������ ������!
---------------------------------------------------------------*/
//CHeader
#include <Windows.h> //for HANDLE
#include <process.h> //for CRT-Thread
#include <conio.h>   //for getch
//CppHeader
#include <iostream>  //for cin/cout
//CustomHeader

using namespace std;

HANDLE GThreadHandle = nullptr;
bool GThreadRunning = false;

unsigned WINAPI RunThreadV2(void* args)
{
    //Call By Reference
    int RepCnt = 0;
    cout << "[RunThreadV2] start!" << endl;
    while (GThreadRunning)
    {
        cout << "RepCnt : " << RepCnt++ << endl;
        if (GThreadRunning) { WaitForSingleObject(GThreadHandle, 1000); }
    }
    cout << "[RunThreadV2] finish!" << endl;
    return RepCnt;
}

void StartThread()
{
    if (!GThreadHandle)
    {
        cout << "[RunThreadV2] Start Called!" << endl;
        GThreadHandle = (HANDLE)_beginthreadex(nullptr, 0, RunThreadV2, nullptr, CREATE_SUSPENDED/*0*/, nullptr);
        if (GThreadHandle)
        {
            GThreadRunning = true;
            ResumeThread(GThreadHandle); 
        }
        cout << "[RunThreadV2] Start Complete!" << endl;
    }
}

void StopThread()
{
    cout << "[RunThreadV2] Stop Called!" << endl;
    if (GThreadHandle) { 
        GThreadRunning = false;
        WaitForSingleObject(GThreadHandle, INFINITE);
        CloseHandle(GThreadHandle); 
        GThreadHandle = nullptr;
    }
    cout << "[RunThreadV2] Stop Complete!" << endl;
}

void PrintMenu()
{
    system("cls");
    cout << "[main] 1. StartThread" << endl;
    cout << "[main] 2. StopThread" << endl;
    cout << "[main] 3. Exit" << endl;
    cout << "[main] Press Buttons : ";
}

int H20221120_Thread2_main(int argc, char* argv[])
{
    int command = 0;
    bool bExitCalled = false;
    bool bProgramRunning = false;
    while (!bExitCalled)
    {
        if (!bProgramRunning)
        {
            PrintMenu();
        }
        cin >> command;
        switch (command)
        {
            case 1:
            {
                StartThread();
                bProgramRunning = true;
                break;
            }
            case 2:
            {
                StopThread();
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
    return 0;
}
