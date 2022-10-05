#pragma once
#include <string>

using namespace std;

class State
{
public:
    int ID;
    string StateName;
    State();
    State(int InID, string InStateName);
};

