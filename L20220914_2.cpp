#include <iostream>

using namespace std;

//값에 의한 전달
void Swap1(int First, int Second)
{
    int temp = First;
    First = Second;
    Second = temp;
}

//참조에 의한 전달
void Swap2(int& First, int& Second)
{
    int temp = First;
    First = Second;
    Second = temp;
}


//주소에 의한 전달
void Swap3(int* First, int* Second)
{
    int temp = *First;
    *First = *Second;
    *Second = temp;
}

int main()
{
    int First = 1;
    int Second = 2;

    Swap1(First, Second);
    Swap2(First, Second);
    Swap3(&First, &Second);

    cout << First << endl;
    cout << Second << endl;

    return 0;
}