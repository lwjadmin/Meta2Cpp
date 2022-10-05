#include <iostream>
#include <stack> //Container
#include <string>

#pragma warning(disable : 4996)

using namespace std;

//DFS(깊이우선탐색) : Stack 사용
//BFS(너비우선탐색) : Queue 사용
//TODO : 가변형 길이의 Stack을 만들기! (크기:자동증가, 기본크기 : 256)

template<typename T>
class MyStack
{
public:
    MyStack()
    {

    }
    ~MyStack()
    {
    }
    void Push(T Data)
    {
        Values[Position++] = Data;
    }
    int Top()
    {
        return Values[Position - 1];
    }
    void Pop()
    {
        Position = Position > 0 ? Position - 1 : Position;
    }
    bool isEmpty()
    {
        return Position == 0 ? true : false;
    }
    int Size()
    {
        return Position - 1;
    }
private:
    T Values[10];
    unsigned int Position = 0;
};


void Prob1()
{
    int Number = 0;
    cin >> Number;

    stack<int> Stack;
    while (Number > 0)
    {
        Stack.push(Number % 2);
        Number = Number / 2;
    }
    while (!Stack.empty())
    {
        cout << Stack.top();
        Stack.pop();
    }
}

int Prob1_Lecture()
{
    int Number = 0;
    stack<int> Store;
    cin >> Number;

    while (Number != 0)
    {
        Store.push(Number % 2);
        Number /= 2;
    }
    while (!Store.empty())
    {
        cout << Store.top();
        Store.pop();
    }
    return 0;
}

void Prob2()
{
    int NCount = 0;
    cin >> NCount;
    long long XNumber = 0;
    stack<long long> NPot;
    int XORResult = 0;
    for (int i = 0; i < NCount; i++)
    {
        long long TmpNPot = 1;
        cin >> XNumber;
        while (TmpNPot < XNumber)
        {
            TmpNPot *= 2;
        }
        NPot.push(TmpNPot);
    }
    while (!NPot.empty()){
        XORResult ^= NPot.top();
        NPot.pop();
    }
    cout << XORResult << endl;
}

void Prob2Adv1()
{
    int NCount = 0;
    cin >> NCount;
    long long XNumber = 0;
    int XORResult = 0;
    for (int i = 0; i < NCount; i++)
    {
        int N = 1;
        cin >> XNumber;
        while (XNumber > 0)
        {
            XNumber /= 2;
            N *= 2;

            //TODO : 곱하기와 나누기를 빼자.
        }
        XORResult ^= N;
    }
    cout << XORResult << endl;
}

void Prob2Adv2()
{
    int NCount = 0;
    cin >> NCount;
    unsigned long long XORResult = 0;
    for (int i = 0; i < NCount; i++)
    {
        unsigned long long XNumber = 0;
        unsigned long long N = 1;
        cin >> XNumber;
        while (XNumber > 0)
        {
            XNumber = XNumber >> 1;
            N = N << 1;
        }
        XORResult ^= N;
    }
    cout << XORResult << endl;
}

void Prob2Adv2_Run(int argc, char* argv[])
{
    if (argc > 1)
    {
        FILE* fp = freopen(argv[1], "r", stdin);
        if (fp != nullptr)
        {
            Prob2Adv2();
        }
    }
}

int L20221004_1_main(int argc, char* argv[])
{
    //Prob2Adv2_Run(argc, argv);
    //Prob1_Lecture();
    /*------------------------------------------------------
    비트연산자 : 최적화 시 사용!
    0000 0000 = 2^0 * 0 = 0
    0000 0001 = 2^0 * 1 = 1
    0000 0010 = 2^1 * 1 = 2
    0000 0100 = 2^2 * 1 = 4
    0000 1000 = 2^3 * 1 = 8
    0001 0000 = 2^4 * 1 = 16
    0010 0000 = 2^5 * 1 = 32
    0100 0000 = 2^6 * 1 = 64
    1000 0000 = 2^7 * 1 = 128 

    << => 곱하기 2^N 효과, 자료형 범위 넘어가면 0
    >> => 나누기 2^N 효과, 자료형 범위 넘어가면 0
    &  => 비트 단위로 AND
    |  => 비트 단위로 OR
    ~  => 비트 단위로 NOT
    ^  => 비트 단위로 XOR (같으면 0, 다르면 1)

    **비트마스킹 : bit 연산자를 사용해서 bit flag를 줘서 처리한다!
    ------------------------------------------------------*/
    return 0;
}