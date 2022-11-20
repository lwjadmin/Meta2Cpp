/*----------------------------------------------------------------
    Singleton Pattern : MyProgram ����
    -- Global �������� Ŭ���� ���� ������ �� �ֵ��� �ֻ��� Ŭ������ �������. 
    -- MyProgram�� ��ӹ޾� ��Ƽ������� �����ϴ� ���α׷��� ����� �ִ�.
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