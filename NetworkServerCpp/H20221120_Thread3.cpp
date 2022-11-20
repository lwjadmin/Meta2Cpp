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
#include "MyThread.h"

using namespace std;

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

//int main(int argc, char* argv[])
int H20221120_Thread3_main(int argc, char* argv[])
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
