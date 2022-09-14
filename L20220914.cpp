#include <iostream> //표준라이브러리
//#include "iostream" //커스텀 라이브러리
#include <conio.h> //_getch가 포함되어있는 헤더

using namespace std;

void PrintMountain()
{
    /*----------------------------------------------------
         *     : S 4,P 1
        ***    : S 3,P 3
       *****   : S 2,P 5
      *******  : S 1,P 7
     ********* : S 0,P 9
      *******  : S 1,P 7
       *****   : S 2,P 5
        ***    : S 3,P 3
         *     : S 4,P 1
     ---------------------------------------------------*/
    int MaxDiaSize = 9;
    bool bExitCalled = false;
    bool bReachedRight = false;
    int staridx = 1;
    int spaceidx = (MaxDiaSize / 2) + 1;
    while (!bExitCalled)
    {
        for (int i = 0; i < spaceidx; i++)
        {
            cout << " ";
        }
        for (int j = 0; j < staridx; j++)
        {
            cout << "*";
        }
        cout << endl;

        if (!bReachedRight)
        {
            staridx += 2;
            spaceidx -= 1;
            if (staridx > MaxDiaSize)
            {
                bReachedRight = true;
            }
        }
        else
        {
            staridx -= 2;
            spaceidx += 1;
            if (staridx < 0)
            {
                bExitCalled = true;
            }
        }
    }
}

void PrintReverseMountain()
{
    for (int i = 5; i >= 1; i--)
    {
        for (int j = 1; j <= 5; j++)
        {
            if (j > i - 1)
            {
                cout << "*";
            }
            else
            {
                cout << " ";
            }
        }
        cout << endl;
    }
}

void AddOddNEven()
{
    int sum = 0;
    //Type1 : For문 2번
    sum = 0;
    for (int i = 1; i <= 100; i += 2)
    {
        sum += i;
    }
    for (int i = 2; i <= 100; i += 2)
    {
        sum -= i;
    }
    cout << sum;

    //Type2 : 홀수일때 +, 짝수일때 -
    sum = 0;
    for (int i = 1; i <= 100; i++)
    {
        //sum += (i % 2 == 1) ? i : -i;
        if (i % 2 == 1)
        {
            sum += i;
        }
        else
        {
            sum -= i;
        }
    }
    cout << sum;

    //Type3 : 2씩증가, 홀수더하기, 짝수빼기
    sum = 0;
    for (int i = 2; i <= 100; i = i + 2)
    {
        //cout << i << "," << i - 1 << "," << -i << endl;
        sum += i - 1;
        sum -= i;
    }
    cout << sum;

    //Type4 : 부호를 계속 곱해서 처리하기
    sum = 0;
    int sign = -1;
    for (int i = 1; i <= 100; i++)
    {
        sign *= -1;
        sum += (sign * i);
    }
    cout << sum;
}

int Map[10][10] =
{
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

bool bIsRunning = true;
int PlayerPosX = 1;
int PlayerPosY = 1;
int PlayerGold = 0;
char InputKeyCode = 0;

void Input()
{
    InputKeyCode = _getch();
}

void Tick()
{
    switch (InputKeyCode)
    {
        case 'W':
        case 'w':
        case 72: //Up Arrow Key
        {
            if (Map[PlayerPosY - 1][PlayerPosX] != 0)
            {
                PlayerPosY--;
            }
            break;
        }
        case 'S':
        case 's':
        case 80: //Down Arrow Key
        {
            if (Map[PlayerPosY + 1][PlayerPosX] != 0)
            {
                PlayerPosY++;
            }
            break;
        }
        case 'D':
        case 'd':
        case 77: //Right Arrow Key
        {
            if (Map[PlayerPosY][PlayerPosX + 1] != 0)
            {
                PlayerPosX++;
            }

            break;
        }
        case 'A':
        case 'a':
        case 75: //Left Arrow Key
        {
            if (Map[PlayerPosY][PlayerPosX - 1] != 0)
            {
                PlayerPosX--;
            }
            break;
        }
        case 27: //End Key
        {
            bIsRunning = false;
            break;
        }
    }
}

void Draw()
{
    system("cls");
    for (int Y = 0; Y < 10; Y++)
    {
        for (int X = 0; X < 10; X++)
        {
            if (PlayerPosY == Y && PlayerPosX == X)
            {
                cout << "★";
            }
            else
            {
                switch (Map[Y][X])
                {
                    case 0: //Wall;
                    {
                        cout << "□";
                        break;
                    }
                    case 1: //Runway;
                    {
                        cout << "  ";
                        break;
                    }
                }
            }
        }
        cout << endl;
    }
}

//entry point
int GameLifeCycle()
{
    while (bIsRunning)
    {
        //1. 입력받는다.
        Input();
        //2. 처리한다.
        Tick();
        //3. 그린다.
        Draw();
    }
    cout << "END!!" << endl;
    return 0;
}