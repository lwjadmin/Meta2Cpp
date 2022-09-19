#include <iostream>

using namespace std;

void Swap_CallByVal(int A, int B)
{
    /*-------------------------------------------
    A, B는 스택에 생성된다. 
    호출단에서 값을 넘겨주기 때문에, 복사가 일어난다.
    함수 내부에서 값을 처리하고, 반환하지 않기 때문에
    호출단의 원본값은 변하지 않는다.
    -------------------------------------------*/
    int Temp = A;
    A = B;
    B = Temp;
}

void Swap_CallByAddress(int* pA, int* pB)
{
    /*-------------------------------------------
    호출단에서 주소를 넘겨주기 때문에, 복사가 일어나지 않는다.
    함수 내부에서 주소에 의한 값을 처리한다.
    -------------------------------------------*/
    int Temp = *pA;
    *pA = *pB;
    *pB = Temp;
}

void Swap_CallByReference(int &A, int &B)
{
    int Temp = A;
    A = B;
    B = Temp;
}


int t20220919_1636_main()
{

    int Count = 3;
    int* pDynamic = new int[Count];

    *pDynamic = 1;
    *(pDynamic + 1) = 2;
    *(pDynamic + 2) = 3;

    pDynamic[0] = 1;
    pDynamic[1] = 2;
    pDynamic[2] = 3;

    delete[] pDynamic;

    int arrays[3] = { 1,2,3 };
    cout << arrays << endl;


    int A = 10;
    int B = 20;
    int* pA = &A;
    int* pB = &B;


    cout << "main_A 주소 : " << &A << endl;
    cout << "main_B 주소 : " << &B << endl;
    cout << "main_A 값 : " << A << endl;
    cout << "main_B 값 : " << B << endl;
    cout << "main_pA 주소 : " << &pA << endl;
    cout << "main_pB 주소 : " << &pB << endl;
    cout << "main_pA 값 : " << pA << endl;
    cout << "main_pB 값 : " << pB << endl;
    cout << "main_pA 주소값 : " << *pA << endl;
    cout << "main_pB 주소값 : " << *pB << endl;


    Swap_CallByVal(A, B);
    cout << "A : " << A << endl;
    cout << "B : " << B << endl;

    Swap_CallByAddress(&A, &B);
    cout << "A : " << A << endl;
    cout << "B : " << B << endl;

    return 0;
}