#include "L20220926.h"


int L20220926_2_main(int argc, char* argv[])
{
    /*----------------------------------------------
    - vector : �̸� �޸𸮸� �Ҵ��س��´�, Ư�� ������ ���� ������ �� �ִ�. 
    - list : �ϳ��� �߰��� ������ �޸𸮸� �Ҵ��Ѵ�, �Է¼ӵ��� ������.
    - set : ���ڸ��� ������������ �ڵ����ĵȴ�. 
    ----------------------------------------------*/
    vector<int> VectorList;
    list<int> LinkedList;
    set<int> OrderedSet;

    cout << "--Random Number Init-------------" << endl;
    int RandCount = EventInputNumber(1, 100);
    for (int i = 0; i < RandCount; i++)
    {
        int RandNumber = GetRandomNumber(1, 100);
        VectorList.push_back(RandNumber);
        LinkedList.push_back(RandNumber);
        OrderedSet.insert(RandNumber);
    }

    cout << "--Vector Forward For Loop-------------" << endl;
    for (int i = 0; i < (int)VectorList.size(); i++)
    {
        cout << VectorList[i] << (i != ((int)VectorList.size() - 1) ? "," : "\n");
    }

    cout << "--Vector Reverse For Loop-------------" << endl;
    for (int i = (int)VectorList.size() - 1; i >= 0; --i)
    {
        cout << VectorList[i] << (i != 0 ? "," : "\n");
    }

    cout << "--Vector Forward For Loop Using Iterator-------------" << endl;
    for (auto/*vector<int>::iterator*/ itr = VectorList.begin(); itr != VectorList.end(); itr++)
    {
        cout << *itr << (itr != VectorList.end() - 1 ? "," : "\n");
    }

    cout << "--Vector Reverse For Loop Using Iterator-------------" << endl;
    for (auto/*vector<int>::reverse_iterator*/ ritr = VectorList.rbegin(); ritr != VectorList.rend(); ritr++)
    {
        cout << *ritr << (ritr != VectorList.rend() - 1 ? "," : "\n");
    }

    cout << "--Vector For Loop (Foreach Type)-------------" << endl;
    for (auto val : VectorList)
    {
        cout << val << endl;
    }

    cout << "--LinkedList For Loop (Foreach Type)-------------" << endl;
    for (auto val : LinkedList)
    {
        cout << val << endl;
    }

    cout << "--OrderedSet For Loop (Foreach Type)-------------" << endl;
    for (auto val : OrderedSet)
    {
        cout << val << endl;
    }
    
    cout << "--LinkedList Forward For Loop Using Iterator-------------" << endl;
    for (auto/*list<int>::iterator*/ itr = LinkedList.begin(); itr != LinkedList.end(); itr++)
    {
        //�������� ����
        //cout << *itr << (itr != (LinkedList.end() - 1) ? "," : "\n");
        cout << *itr << endl;
    }

    cout << "--LinkedList Reverse For Loop Using Iterator-------------" << endl;
    for (auto/*list<int>::reverse_iterator*/ ritr = LinkedList.rbegin(); ritr != LinkedList.rend(); ritr++)
    {
        //�������� ����
        //cout << *ritr << (ritr != LinkedList.rend() - 1 ? "," : "\n");
        cout << *ritr << endl;
    }

    
    cout << "--OrderedSet Forward For Loop Using Iterator-------------" << endl;
    for (auto/*set<int>::iterator*/ itr = OrderedSet.begin(); itr != OrderedSet.end(); itr++)
    {
        //�������� ����
        //cout << *itr << (itr != (OrderedSet.end() - 1) ? "," : "\n");
        cout << *itr << endl;
    }

    //�������� ����
    cout << "--OrderedSet Reverse For Loop Using Iterator-------------" << endl;
    for (auto/*set<int>::reverse_iterator*/ ritr = OrderedSet.rbegin(); ritr != OrderedSet.rend(); ritr++)
    {
        //cout << *ritr << (ritr != OrderedSet.rend() - 1 ? "," : "\n");
        cout << *ritr << endl;
    }

    return 0;
}