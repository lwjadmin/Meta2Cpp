#include <iostream>  

using namespace std;

void GetScoreV1(int Score)
{
    if (Score >= 90)
    {
        cout << "A" << endl;
    }
    else if (Score >= 80)
    {
        cout << "B" << endl;
    }
    else if (Score >= 70)
    {
        cout << "C" << endl;
    }
    else if (Score >= 60)
    {
        cout << "D" << endl;
    }
    else if (Score >= 0)
    {
        cout << "F" << endl;
    }
    else
    {
        cout << "Invalid" << endl;
    }
}

void GetScoreV2(int Score)
{
    if (Score >= 90 && Score <= 100)
    {
        cout << "A" << endl;
    }
    else if (Score >= 80 && Score < 90)
    {
        cout << "B" << endl;
    }
    else if (Score >= 70 && Score < 80)
    {
        cout << "C" << endl;
    }
    else if (Score >= 60 && Score < 70)
    {
        cout << "D" << endl;
    }
    else if (Score >= 0 && Score < 60)
    {
        cout << "F" << endl;
    }
    else
    {
        cout << "Invalid" << endl;
    }
}

void GetScoreV3(int Score)
{
    Score = Score / 10;
    switch (Score)
    {
        case 10:
        case 9:
        { cout << "A" << endl;  break; }
        case 8:
        { cout << "B" << endl;  break; }
        case 7:
        { cout << "C" << endl;  break; }
        case 6:
        { cout << "D" << endl;  break; }
        default:
        { cout << "F" << endl; }
    }//eoswitch
}//eofunc

void IsOddEven(int Number)
{
    //else if를 사용하지 않은 OddEven 체크
    if (Number == 0)
    {
        cout << "0" << endl;
    }
    else
    {
        if (Number % 2 == 1)
        {
            cout << "Odd" << endl;
        }
        else
        {
            cout << "Even" << endl;
        }
    }
}

//Entry Point
int old_main()
{
    int ivalA = 4;
    int ivalB = 3;
    float fval = 4.5f;
    char ca = 'a'; //97
    char cA = 'A'; //65
    char cval = 12;
    bool bTrue = true;
    bool bFalse = false;
    bTrue = 1;
    bFalse = 0;

    //CStyle
    ivalA = (int)fval;
    //CppStyle
    ivalA = static_cast<int>(fval);

    cout << "A + B = " << ivalA + ivalB << endl;
    cout << "A - B = " << ivalA - ivalB << endl;
    cout << "A * B = " << ivalA * ivalB << endl;
    cout << "A / B = " << (float)ivalA / (float)ivalB << endl; //mok
    cout << "A % B = " << ivalA % ivalB << endl; //nmg

    int korean = 100;
    int english = 100;
    int mathmatics = 100;
    int tot = korean + english + mathmatics;
    float avg = static_cast<float>(korean + english + mathmatics) / 3.0f;
    avg = (float)tot / 3.0f;
    avg = ((float)korean + (float)english + (float)mathmatics) / 3.0f;

    int koreanArray[10] = { 0, };
    int idx = 0;
    for (idx = 0; idx < 10; idx = idx + 1)
    {
        //Set Array & ForLoop
        cin >> koreanArray[idx];
    }
    for (idx = 0; idx < 10; idx = idx + 1)
    {
        //Print Array & ForLoop
        cout << koreanArray[idx] << endl;
    }
    for (int ktemp : koreanArray)
    {
        //Print Array & ForeachLoop(C++11)
        cout << ktemp << endl;
    }

    int sumAll = 0;
    int sum3 = 0;
    int sumOdd = 0;
    int sumEven = 0;

    for (int i = 1; i <= 100; i++)
    {
        sumAll += i;
    }
    for (int i = 1; i <= 100; i += 2)
    {
        sumOdd += i;
    }
    for (int i = 2; i <= 100; i += 2)
    {
        sumEven += i;
    }
    for (int i = 3; i <= 100; i += 3)
    {
        sum3 += i;
    }
    cout << sumAll << endl; //5050
    cout << sum3 << endl; //1683
    cout << sumEven << endl; //2550
    cout << sumOdd << endl; //2500

    //별찍기 Increase
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            cout << "*";
        }
        cout << endl;
    }

    //별찍기 Decrease
    for (int i = 4; i >= 0; i--)
    {
        for (int j = 0; j < i + 1; j++)
        {
            cout << "*";
        }
        cout << endl;
    }
    return 0;
}