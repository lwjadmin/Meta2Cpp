#include <iostream>
#include <conio.h>
#include <random>
#include <windows.h>
#include <iomanip>

using namespace std;

namespace LectureLWJ
{

#define __USE_MERSEN_TWISTER_RANDOM__

#ifdef __USE_MERSEN_TWISTER_RANDOM__
    std::random_device rd;
    std::mt19937 mersen_twister_random(rd());
#else
    bool bRandInitOnce = false;
#endif

    int GetRandNumber(int BeginRange = 1, int EndRange = 10)
    {
#ifdef __USE_MERSEN_TWISTER_RANDOM__
        std::uniform_int_distribution<int> GetRandomInt32(BeginRange, EndRange);
        return GetRandomInt32(mersen_twister_random);
#else
        if (!bRandInitOnce)
        {
            srand(static_cast<unsigned int>(time(nullptr)));
            bRandInitOnce = true;
        }
        return (rand() % EndRange) + BeginRange;
#endif
    }


    enum class ConsoleColor
    {
        BLACK,
        BLUE,
        GREEN,
        CYAN,
        RED,
        MAGENTA,
        BROWN,
        LIGHTGRAY,
        DARKGRAY,
        LIGHTBLUE,
        LIGHTGREEN,
        LIGHTCYAN,
        LIGHTRED,
        LIGHTMAGENTA,
        YELLOW,
        WHITE
    };

    void SetConsoleFontColor(ConsoleColor color)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)color);
    }

    void PrintConsoleSystemInfo()
    {
        SetConsoleFontColor(ConsoleColor::GREEN);
        cout << "[SYS]";
        SetConsoleFontColor(ConsoleColor::LIGHTGRAY);
    }

    int* GenerateMonster()
    {
        int* Monster = new int[3];
        //몬스터타입(0:고블린,1:멧돼지,2:슬라임)
        Monster[0] = GetRandNumber(0, 2);
        //랜덤생성
        Monster[1] = GetRandNumber(10, 50);
        //90(동),180(남),270(서),360/0(북)
        Monster[2] = GetRandNumber(0, 3) * 90;
        return Monster;
    }

    void KillMonster(int* Monster)
    {
        if (Monster != nullptr)
        {
            delete[] Monster;
        }
    }

    void ShowMonsterStatus(int* Monster)
    {
        if (Monster == nullptr) { return; }
        string StrMonsterType = "";
        string MonsterDirection = "";
        int MonsterHP = Monster[1];

        switch (Monster[0])
        {
            case 0: { StrMonsterType = "고블린"; break; }
            case 1: { StrMonsterType = "멧돼지"; break; }
            case 2: { StrMonsterType = "슬라임"; break; }
        }

        switch (Monster[2])
        {
            case 0:
            case 360:
            { MonsterDirection = "북쪽"; break; }
            case 90: { MonsterDirection = "동쪽"; break; }
            case 180: { MonsterDirection = "남쪽"; break; }
            case 270: { MonsterDirection = "서쪽"; break; }
        }

        cout << StrMonsterType << "hp는 " << MonsterHP << "이고 "
            << MonsterDirection << "으로 이동합니다." << endl;
    }

    void GenerateMonsterPool_UseDoublePointer(int MonsterCount)
    {
        int** MonsterPool = new int* [MonsterCount];
        PrintConsoleSystemInfo();
        cout << "Monster Pool Count : " << MonsterCount << endl;
        cout << "-------------------------------------------------------------" << endl;

        for (int i = 0; i < MonsterCount; i++)
        {
            MonsterPool[i] = GenerateMonster();
            cout << "[" << std::setw(3) << i + 1 << "] ";
            ShowMonsterStatus(MonsterPool[i]);
            KillMonster(MonsterPool[i]);
        }
        delete[] MonsterPool;
        cout << "-------------------------------------------------------------" << endl;
    }

    void GenerateMonsterPool_UseSinglePointer(int MonsterCount)
    {
        PrintConsoleSystemInfo();
        cout << "Monster Pool Count : " << MonsterCount << endl;
        cout << "-------------------------------------------------------------" << endl;

        for (int i = 0; i < MonsterCount; i++)
        {
            int* Monster = GenerateMonster();
            cout << "[" << std::setw(3) << i + 1 << "] ";
            ShowMonsterStatus(Monster);
            KillMonster(Monster);
        }
        cout << "-------------------------------------------------------------" << endl;
    }

    int PressAnyKeyToContinue()
    {
        int retval = 0;
        PrintConsoleSystemInfo();
        cout << "계속하려면 아무 키나 누르세요/[ESC]키를 누르면 종료합니다." << endl;
        retval = _getch();
        return retval;
    }

    int L20220920_1_main()
    {
        const int ExitKeyCode = 27; //27 : [ESC] Key
        int MonsterCount = 10;
        int Turn = 0;
        bool ExitCalledYN = false;

        while (!ExitCalledYN)
        {
            PrintConsoleSystemInfo();
            cout << "Turn : " << ++Turn << endl;
            GenerateMonsterPool_UseSinglePointer(MonsterCount);
            if (PressAnyKeyToContinue() == ExitKeyCode)
            {
                ExitCalledYN = true;
            }
        }
        return 0;
    }
}
namespace LectureKHU
{
#define L_SAFE_DELETE(x) if(x == nullptr){delete[] x;}
#define L_MAX2(x,y) ((x) > (y) ? (x) : (y))
#define L_MAX3(x,y,z) (MAX(x,y) > z ? MAX(x,y) : z)

#define L_MIN2(x,y) ((x) < (y) ? (x) : (y))
#define L_MIN3(x,y,z) (MIN(x,y) < z ? MIN(x,y) : z)

    enum MoveDirection
    {
        North = 1,
        South = 2,
        East = 3,
        West = 4
    };

    void SetDirection()
    {
        const char* directionList[] = { "북쪽","남쪽","동쪽","서쪽" };
        int idx = rand() % 4;
        if (idx >= 0 && idx < 4)
        {
            cout << directionList[idx];
        }
    }

    void PrintMonster(const char* Name, const int* data, const int count)
    {
        if (data != nullptr)
        {
            for (int i = 0; i < count; ++i)
            {
                cout << Name << " HP는 " << setw(3) << setfill('0') << data[i] << "이고, ";
                SetDirection();
                cout << "으로 이동합니다.\n";
            }
        }
    }

    int* GenerateMonsterPointer(int count)
    {
        int* ptr = nullptr;
        if (count > 0)
        {
            ptr = new int[count];
            for (int i = 0; i < count; i++)
            {
                ptr[i] = rand() % 100 + 1;
            }
        }
        return ptr;
    }

    int L20220920_1_main()
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        int goblincount = rand() % 5 + 1;
        int slimecount = rand() % 5 + 1;
        int boarcount = rand() % 5 + 1;

        //cin >> goblincount;
        //cin >> slimecount;
        //cin >> boarcount;

        int* goblinHp = GenerateMonsterPointer(goblincount);
        int* slimeHp = GenerateMonsterPointer(slimecount);
        int* boarHp = GenerateMonsterPointer(boarcount);

        int inputKey = -1;
        while (!(inputKey == 'Q' || inputKey == 'q'))
        {
            PrintMonster("고블린", goblinHp, goblincount);
            PrintMonster("슬라임", slimeHp, slimecount);
            PrintMonster("멧돼지", boarHp, boarcount);
            cout << "아무 키나 누르면 다음턴" << endl;
            inputKey = _getch();
        }

        L_SAFE_DELETE(goblinHp);
        L_SAFE_DELETE(slimeHp);
        L_SAFE_DELETE(boarHp);

        return 0;
    }
}

