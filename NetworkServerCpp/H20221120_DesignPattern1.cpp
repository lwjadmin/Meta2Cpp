/*----------------------------------------------------------------
    Singleton Pattern : MyProgram 적용
    -- Global 변수들을 클래스 내에 저장할 수 있도록 최상위 클래스를 만들었다. 
    -- MyProgram을 상속받아 멀티스레드로 동작하는 프로그램을 만들수 있다.
----------------------------------------------------------------*/

//CHeader
#include <Windows.h> //for HANDLE
//CppHeader
#include <iostream>  //for cin/cout
//CustomHeader
#include "MyThread.h"
#include "MyProgram.h"

using namespace std;

void PrintMenu_DP1()
{
    system("cls");
    cout << "[main] 1. Program Start" << endl;
    cout << "[main] 2. Program Stop" << endl;
    cout << "[main] 3. Exit" << endl;
    cout << "[main] Press Buttons : ";
}

//int main(int argc, char* argv[])
int H20221120_DesignPattern1_main(int argc, char* argv[])
{
    int command = 0;
    bool bExitCalled = false;
    bool bProgramRunning = false;

    GMyProgram.Init();

    while (!bExitCalled)
    {
        if (!bProgramRunning)
        {
            PrintMenu_DP1();
        }
        cin >> command;
        switch (command)
        {
            case 1:
            {
                GMyProgram.Start();
                bProgramRunning = true;
                break;
            }
            case 2:
            {
                GMyProgram.Finish();
                bProgramRunning = false;
                cout << "GMyProgram.number : " << GMyProgram.number << endl;
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