#include "MonsterFSM.h"

MonsterFSM::MonsterFSM()
{
    StateList.push_back(State(1, "배회"));
    StateList.push_back(State(2, "추격"));
    StateList.push_back(State(3, "공격"));
    StateList.push_back(State(4, "죽음"));
    TransitionList.push_back(Transition(1, "적발견", 2));
    TransitionList.push_back(Transition(2, "적놓침", 1));
    TransitionList.push_back(Transition(2, "사정거리 접근", 3));
    TransitionList.push_back(Transition(3, "사정거리 이탈", 2));
    TransitionList.push_back(Transition(3, "HP 없음", 4));
}

int MonsterFSM::GetNextState(int CurrentState, string Condition)
{
    int NextState = 0;
    for (size_t i = 0; i < TransitionList.size(); i++)
    {
        if (TransitionList[i].CurrentState == CurrentState &&
            TransitionList[i].Condition == Condition)
        {
            NextState = TransitionList[i].NextState;
            break;
        }
    }
    return NextState;
}

string MonsterFSM::GetStateName(int StateIndex)
{
    string strout = "";
    for (size_t i = 0; i < StateList.size(); i++)
    {
        if (StateList[i].ID == StateIndex)
        {
            strout =  StateList[i].StateName;
            break;
        }
    }
    return strout;
}
