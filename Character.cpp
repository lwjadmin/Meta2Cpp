#include "Character.h"

//#define USE_MEMBER_INITALIZER_LISTS

Character::Character()
{
    this->ID = 0;
    this->Name = "";
    this->Str = 0;
    this->Dex = 0;
}

Character::Character(int InID, string InName, int InStr, int InDex)
#ifdef USE_MEMBER_INITALIZER_LISTS
    : ID(InID), Name(InName), Str(InStr), Dex(InDex)
#endif
{
#ifndef USE_MEMBER_INITALIZER_LISTS
    this->ID = InID;
    this->Name = InName;
    this->Str = InStr;
    this->Dex = InDex;
#endif
}

void Character::ShowStatus()
{
    cout << "ID : " << ID << endl;
    cout << "Name : " << Name << endl;
    cout << "Str : " << Str << endl;
    cout << "Dex : " << Dex << endl;
}
