#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

void Prob10430_PrintAll()
{
    int A = 0;
    int B = 0;
    int C = 0;

    cin >> A >> B >> C;
    cout << (A + B) % C << endl;
    cout << ((A % C) + (B % C)) % C << endl;
    cout << (A * B) % C << endl;
    cout << ((A % C) * (B % C)) % C << endl;
}

void Prob2588_Adder()
{
    int number1 = 0;
    int number2 = 0;

    cin >> number1;
    cin >> number2;

    int num1 = number2 % 10;
    int num10 = (number2 % 100) / 10;
    int num100 = (number2 % 1000) / 100;

    int total = 0;

    cout << number1 * num1 << endl;
    cout << number1 * num10 << endl;
    cout << number1 * num100 << endl;
    cout << (number1 * num1) + (number1 * num10 * 10) + (number1 * num100 * 100) << endl;
}

void Prob2588_PrintCat()
{
    cout << "\\    /\\" << endl;
    cout << " )  ( ')" << endl;
    cout << "(  /  )" << endl;
    cout << " \\(__)|" << endl;
}

void Prob10172_PrintDog()
{
    cout << "|\\_/|" << endl;
    cout << "|q p|   /}" << endl;
    cout << "( 0 )\"\"\"\\" << endl;
    cout << "|\"^\"`    |" << endl;
    cout << "||_/=\\\\__|" << endl;
}

void Prob25083_PrintLeaf()
{
    cout << "         ,r'\"7" << endl;
    cout << "r`-_   ,'  ,/" << endl;
    cout << " \\. \". L_r'" << endl;
    cout << "   `~\\/" << endl;
    cout << "      |" << endl;
    cout << "      |" << endl;
}

void Prob1330_Compare()
{
    int a = 0;
    int b = 0;
    cin >> a >> b;
    if (a == b)
    {
        cout << "==";
    }
    else if (a > b)
    {
        cout << ">";
    }
    else if (a < b)
    {
        cout << "<";
    }
}

void Proj9498_GetScore()
{
    int scores = 0;
    cin >> scores;
    if (scores >= 90 && scores <= 100)
    {
        cout << "A";
    }
    else if (scores >= 80)
    {
        cout << "B";
    }
    else if (scores >= 70)
    {
        cout << "C";
    }
    else if (scores >= 60)
    {
        cout << "D";
    }
    else
    {
        cout << "F";
    }
}

void Prob2753_PrintLeapYear()
{
    int year = 0;
    cin >> year;
    bool condition1 = (year % 4 == 0) ? true : false;
    bool condition2 = (year % 100 != 0) ? true : false;
    bool condition3 = (year % 400 == 0) ? true : false;

    if ((condition1 && condition2) || condition3)
    {
        cout << "1";
    }
    else
    {
        cout << "0";
    }
}

void Prob2753_CheckQuadrant()
{
    int x;
    int y;
    cin >> x;
    cin >> y;

    if (x > 0 && y > 0)
    {
        cout << 1;
    }
    else if (x > 0 && y < 0)
    {
        cout << 4;
    }
    else if (x < 0 && y > 0)
    {
        cout << 2;
    }
    else if (x < 0 && y < 0)
    {
        cout << 3;
    }

}


void Prob2884_EarlyAlarm()
{
    int hours = 0;
    int minutes = 0;
    int totalMinutes = 0;
    cin >> hours >> minutes;
    totalMinutes = (hours * 60) + minutes;

    if ((totalMinutes - 45) >= 0)
    {
        totalMinutes -= 45;
    }
    else
    {
        totalMinutes -= 45;
        totalMinutes += (60 * 24);
    }

    hours = totalMinutes / 60;
    minutes = totalMinutes % 60;
    cout << hours << " " << minutes;

}

void Prob2525_OvenWatch()
{
    int hours = 0;
    int minutes = 0;
    int setminutes = 0;
    int totalMinutes = 0;
    cin >> hours >> minutes;
    cin >> setminutes;

    totalMinutes = (hours * 60) + minutes + setminutes;
    if (totalMinutes >= (24 * 60))
    {
        totalMinutes -= (24 * 60);
    }


    cout << totalMinutes / 60 << " " << totalMinutes % 60 << endl;

}


void Prob11654_ASCII()
{
    char ch;
    cin >> ch;
    cout << (int)ch;
}


void Prob11720_NumberAdd()
{
    char charr[105] = { 0, };
    int nCount = 0;
    int sum = 0;
    cin >> nCount;
    cin >> charr;
    for (int i = 0; i < nCount; i++)
    {
        sum += (charr[i] - 48);
    }
    cout << sum << endl;
}


void Prob10809_FindAlphabet()
{
    char alphabet[101] = { 0, };
    cin >> alphabet;
    int len = (int)strlen(alphabet);
    char Alpha[26];
    memset(Alpha, -1, sizeof(char) * 26);

    for (int j = 0; j < len; j++)
    {
        int index = alphabet[j] - 97;
        if (Alpha[index] == -1)
        {
            Alpha[index] = j;
        }
    }


    for (int i = 0; i < 26; i++)
    {
        cout << (int)Alpha[i] << (i < 25 ? " " : "\n");
    }
}

void Prob2675_StringRepeat()
{
    int nCount = 0;
    cin >> nCount;


    for (int i = 0; i < nCount; i++)
    {
        int nCount2 = 0;
        char str[21] = { 0, };
        cin >> nCount2 >> str;
        int strcnt = (int)strlen(str);
        int tmpval = 0;
        int repcnt = 0;
        for (int i = 0; i < nCount2 * strcnt; i++)
        {
            cout << str[tmpval];
            repcnt++;
            if (repcnt == nCount2)
            {
                tmpval++;
                repcnt = 0;
            }
        }
        cout << "\n";
    }
}


void Prob1157_WordStudy()
{
    string word;
    cin >> word;
    int alphabets[26] = { 0, };
    int maxcnt = 0;
    int maxrep = 0;
    char maxAlpha;

    for (int i = 0; i < word.size(); i++)
    {
        int iword = (int)word[i];
        if (iword >= 97)
        {
            iword = iword - 32;
        }
        iword = iword - 65;
        if (iword > -1 && iword < 26) { alphabets[iword] += 1; }
    }
    //검증로직
    //for (int j = 0; j < 26; j++)
    //{
    //    cout << (char)(j + 65) << (j != 26 - 1 ? " " : "\n");
    //}
    //for (int k = 0; k < 26; k++)
    //{
    //    cout << alphabets[k] << (k != 26 - 1 ? " " : "\n");
    //}
    //1차 - maxAlpha 찾기
    for (int l = 0; l < 26; l++)
    {
        if (maxcnt < alphabets[l])
        {
            maxcnt = alphabets[l];
            maxAlpha = 65 + l;
        }
    }
    //2차 - maxAlpha가 중복되는지 여부 확인
    for (int l = 0; l < 26; l++)
    {
        if (alphabets[l] == maxcnt && maxAlpha - 65 != l)
        {
            maxAlpha = '?';
            break;
        }
    }
    cout << maxAlpha << endl;
}

void Prob1152_GetWordCount()
{
    string str;
    getline(cin, str);
    int wordcnt = 0;
    bool bWordStart = false;
    for (int i = 0; i < str.size(); i++)
    {
        if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z'))
        {
            bWordStart = true;
            continue;
        }
        else if (str[i] == ' ' && bWordStart == true)
        {
            bWordStart = false;
            wordcnt++;
        }
    }
    if (bWordStart) { wordcnt++; }
    cout << wordcnt << endl;
}


void Prob2908_ReverseNumberCheck_Swap(char& a, char& b)
{
    char tmp = a;
    a = b;
    b = tmp;
}

void Prob2908_ReverseNumberCheck()
{
    string str1;
    string str2;

    cin >> str1 >> str2;
    Prob2908_ReverseNumberCheck_Swap(str1[0], str1[2]);
    Prob2908_ReverseNumberCheck_Swap(str2[0], str2[2]);

    int i1 = stoi(str1);
    int i2 = stoi(str2);
    int max = i1 > i2 ? i1 : i2;
    cout << max << endl;
}


void Prob5622_Dial()
{
    string dial;
    cin >> dial;
    int sum = 0;
    for (int i = 0; i < dial.size(); i++)
    {
        switch (dial[i])
        {
            case 'A':case 'B':case 'C':
            { sum += 3; break; }
            case 'D':case 'E':case 'F':
            { sum += 4; break; }
            case 'G':case 'H':case 'I':
            { sum += 5; break; }
            case 'J':case 'K':case 'L':
            { sum += 6; break; }
            case 'M':case 'N':case 'O':
            { sum += 7; break; }
            case 'P':case 'Q':case 'R':case 'S':
            { sum += 8; break; }
            case 'T':case 'U':case 'V':
            { sum += 9; break; }
            case 'W':case 'X':case 'Y':case 'Z':
            { sum += 10; break; }
        }

    }
    cout << sum << endl;
}

void Prob2941_Croatia()
{
    string words[8] = { "c=", "c-", "dz=", "d-", "lj", "nj", "s=", "z=" };
    string msg = "";
    string comparer = "";
    cin >> msg;

    int nCount = 0;
    for (int i = 0; i < msg.size(); i++)
    {
        switch (msg[i])
        {
            case 'c':
            case 'd':
            case 'l':
            case 'n':
            case 's':
            case 'z':
            {
                bool bFound = false;
                for (int j = 0; j < 8; j++)
                {
                    comparer = msg.substr(i, words[j].size());
                    if (comparer == words[j])
                    {
                        i += words[j].size() - 1;
                        nCount++;
                        bFound = true;
                        break;
                    }
                }
                if (!bFound)
                {
                    nCount++;
                }
                break;
            }
            default:
            {
                nCount++;
            }
        }
    }
    cout << nCount << endl;
}

void Prob1316_GroupWordChecker()
{
    int nCount = 0;
    int groupCount = 0;
    cin >> nCount;

    for (int i = 0; i < nCount; i++)
    {
        int alphabet[26] = { 0, };
        bool bValid = true;
        string str = "";
        cin >> str;
        char prevChar = str[0];
        char newChar;
        for (int j = 0; j < (int)str.size(); j++)
        {
            newChar = str[j];
            if (prevChar == newChar)
            {
                alphabet[newChar - 'a'] += 1;
            }
            else if (prevChar != newChar)
            {
                if (alphabet[newChar - 'a'] > 0)
                {
                    bValid = false;
                    break;
                }
                alphabet[newChar - 'a'] += 1;
                prevChar = newChar;
            }
        }
        if (bValid) { groupCount++; }
    }
    cout << groupCount << endl;
}