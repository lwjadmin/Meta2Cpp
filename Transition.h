#pragma once
#include <string>

using namespace std;

class Transition
{
public:
    int CurrentState;
    string Condition;
    int NextState;
    Transition();
    Transition(int InCurrentState, string InCondition, int InNextState);
};

