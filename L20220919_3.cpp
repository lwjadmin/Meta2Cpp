#include <iostream>

using namespace std;

void Swap_CallByVal(int A, int B)
{
    /*-------------------------------------------
    A, B�� ���ÿ� �����ȴ�. 
    ȣ��ܿ��� ���� �Ѱ��ֱ� ������, ���簡 �Ͼ��.
    �Լ� ���ο��� ���� ó���ϰ�, ��ȯ���� �ʱ� ������
    ȣ����� �������� ������ �ʴ´�.
    -------------------------------------------*/
    int Temp = A;
    A = B;
    B = Temp;
}

void Swap_CallByAddress(int* pA, int* pB)
{
    /*-------------------------------------------
    ȣ��ܿ��� �ּҸ� �Ѱ��ֱ� ������, ���簡 �Ͼ�� �ʴ´�.
    �Լ� ���ο��� �ּҿ� ���� ���� ó���Ѵ�.
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


    cout << "main_A �ּ� : " << &A << endl;
    cout << "main_B �ּ� : " << &B << endl;
    cout << "main_A �� : " << A << endl;
    cout << "main_B �� : " << B << endl;
    cout << "main_pA �ּ� : " << &pA << endl;
    cout << "main_pB �ּ� : " << &pB << endl;
    cout << "main_pA �� : " << pA << endl;
    cout << "main_pB �� : " << pB << endl;
    cout << "main_pA �ּҰ� : " << *pA << endl;
    cout << "main_pB �ּҰ� : " << *pB << endl;


    Swap_CallByVal(A, B);
    cout << "A : " << A << endl;
    cout << "B : " << B << endl;

    Swap_CallByAddress(&A, &B);
    cout << "A : " << A << endl;
    cout << "B : " << B << endl;

    return 0;
}