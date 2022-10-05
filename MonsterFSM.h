#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "Transition.h"
#include "State.h"

using namespace std;

class MonsterFSM
{
public:
    MonsterFSM();
    int GetNextState(int CurrentState, string Condition);
    string GetStateName(int StateIndex);
    vector<State> StateList;
    vector<Transition> TransitionList;
};

