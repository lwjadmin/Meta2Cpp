#include "MonsterFSM.h"

MonsterFSM::MonsterFSM()
{
    StateList.push_back(State(1, "��ȸ"));
    StateList.push_back(State(2, "�߰�"));
    StateList.push_back(State(3, "����"));
    StateList.push_back(State(4, "����"));
    TransitionList.push_back(Transition(1, "���߰�", 2));
    TransitionList.push_back(Transition(2, "����ħ", 1));
    TransitionList.push_back(Transition(2, "�����Ÿ� ����", 3));
    TransitionList.push_back(Transition(3, "�����Ÿ� ��Ż", 2));
    TransitionList.push_back(Transition(3, "HP ����", 4));
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
