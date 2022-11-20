/*---------------------------------------------------------------
    CRT(C Runtime Library) Simple Thread Example
---------------------------------------------------------------*/

//CHeader
#include <Windows.h>
#include <process.h>
#include <conio.h>
//CppHeader
#include <iostream>
//CustomHeader

using namespace std;

unsigned RunThreadV1(void* args)
{
    //Call By Reference
    int* iarg = (int*)args;

    cout << "[ThreadRun]Send Args : " << *iarg << endl;
    for (int i = 0; i < 10; i++)
    {
        *iarg += 1;
        cout << "iarg : " << *iarg << endl;
    }
    return 0;
}

int H20221120_Thread1_main(int argc, char* argv[])
{
    unsigned int threadID = 0;
    int threadarg = 1;
    HANDLE ThreadHandle = (HANDLE)_beginthreadex(nullptr, 0, RunThreadV1, &threadarg, CREATE_SUSPENDED/*0*/, &threadID);
    if(ThreadHandle){ ResumeThread(ThreadHandle); }
    cout << "[Main] Thread : ThreadRun Started." << endl;
    cout << "[Main] threadarg : " << threadarg << endl;

    bool ShowOnce = false;
    while (true)
    {
        if (!ShowOnce)
        {
            cout << "[Main] Press q to Quit" << endl;
            ShowOnce = true;
        }
        if (_getch() == 'q') { break; }
    }
    if (ThreadHandle) { WaitForSingleObject(ThreadHandle, INFINITE); }
    cout << "[Main] Thread : ThreadRun Stopped." << endl;
    cout << "[Main] threadarg : " << threadarg << endl;

    return 0;
}
