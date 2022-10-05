#pragma once
#include <iostream>
#include <string>

using namespace std;

class Character
{
public:
    int ID;
    string Name;
    int Str;
    int Dex;
    Character();
    Character(int InID, string InName, int InStr, int InDex);
    void ShowStatus();
};

