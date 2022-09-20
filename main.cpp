#include <iostream>
#include <iomanip>

using namespace std;

/*-----------------------------------------------
������ �κ� :
-------------------------------------------------
- Memory : Heap / Stack / BSS / Code / Data ����

- ��ũ�κ��� const Ű����� �����������.

- ������ / �Ǽ��� / ������ �޸𸮱��� Ȯ��

- bool 0 : false, 0�� �ƴ� �� : true

- �ݿø�/����/�ø� �ļ�

- ��Ʈ������

- 2���� �迭�� ������

-----------------------------------------------*/

void CheckIntSingleArray()
{
    /*-----------------------------------------------------
    1. ���� 1���� �迭�� Stack�� ����ȴ�.
    2. ���� 1���� �迭 �ʱ�ȭ�� ���� ����� �ִ�. 
       [CASE 1] 
       int arr[50] = { 0, }; //�̷��� �����ϸ� 0���� �ʱ�ȭ
       int arr[50] = { 1, }; //�̷��� �����ϸ� �� �տ�Ҹ� 1�� �ʱ�ȭ, �ڴ� 0���� �ʱ�ȭ
       [CASE 2]
       memset(arr,5,sizeof(arr)); //�迭�� Ư�������� �ʱ�ȭ�� ���� memset�� ������.
   3. ���� 1���� �迭�� ������ �迭������ / �迭�ڷ������� ���� ���� �� �ִ�.
       int arrsize = sizeof(arr) / sizeof(int);
   -----------------------------------------------------*/

    int arr[50];
    memset(arr, -1, sizeof(arr));
    int arrsize = sizeof(arr) / sizeof(int);
    for (int i = 0; i < arrsize; i++)
    {
        arr[i] = i + 1;
    }
    for (int i = 0; i < arrsize; i++)
    {
        cout << arr[i] << (i != arrsize - 1 ? "," : "\n");
    }
    //for (const int i : arr)
    //{
    //    cout << i << endl;
    //}
}

int GetUnsignedIntegerDigit(int number)
{
    int retval = 0;
    while (number > 0)
    {
        number /= 10;
        retval++;
    }
    return retval;
}

void CheckIntDoubleArray()
{
    /*-------------------------------------------------
    1. ���� 2���� �迭�� Stack�� ����ȴ�.
    2. 2���� �迭�� �����͸� �����ؼ� Rows/Cols���� �ʱ�ȭ�� �� �ִ�. 
    3. Cols(��)�� ���� ���ؾ� Rows(��)�� ���� �� �ִ�. 
    4. �ڸ����� ���ؼ� ���ڸ� ���� ǥ���� �� �ִ�.
    -------------------------------------------------*/
    int arr2[3][5] =
    {
        {1,2,3,4,5},
        {6,7,8,9,10},
        {11,12,13,14,15},
    };
    //int arr2[5][14] = { 0, }; 
    
    int* parr2 = &arr2[0][0];
    int cols = sizeof(arr2[0]) / sizeof(int);
    int rows = (sizeof(arr2) / cols) / sizeof(arr2[0][0]);
    int len = rows * cols;
    memset(arr2, 0, sizeof(int) * len);
    int repcnt = GetUnsignedIntegerDigit(len);

    for (int i = 0; i < len; i++)
    {
        parr2[i] = i + 1;
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout <<  (j == 0 ? "{":"") << setw(repcnt) << setfill('0') << arr2[i][j] << (j != cols - 1 ? "," : "}\n");
        }
    }
}

int main(int argc, char* argv[])
{
    
    int number = 5;
    cout << "[stack] int ���� number�� ũ�� : " << sizeof(number) << endl;
    cout << "[stack] int ���� number�� �� : " << number << endl;
    cout << "[stack] int ���� number�� �ּ� : 0x" << &number << endl;

    cout << "-----------------------------------------------------------------" << endl;
    int* pnumber = &number;
    cout << "[stack]int ������ ���� pnumber�� ũ�� : " << sizeof(pnumber) << endl;
    cout << "[stack]int ������ ���� pnumber�� �� :  0x" << pnumber << endl;
    cout << "[stack]int ������ ���� pnumber�� �ּ� : 0x" << &pnumber << endl;
    cout << "[stack]int ������ ���� pnumber�� ������ : " << *pnumber << endl;

    cout << "-----------------------------------------------------------------" << endl;
    int* darr = new int[5];
    for (int i = 0; i < 5; i++)
    {
        *(darr + i) = i + 1;
        //darr[i] = i + 1;
    }
    cout << "[heap] int �����迭 ������ darr�� ũ�� : " << sizeof(darr) << endl;
    cout << "[heap] int �����迭 ������ darr�� �� : 0x" << darr << endl;
    cout << "[heap] int �����迭 ������ darr�� �ּ� : 0x" << &darr << endl;
    cout << "[heap] int �����迭 ������ darr�� ������ : " << *darr << endl;
    cout << "-----------------------------------------------------------------" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "darr[" << i << "] �� = " << *(darr + i) << endl;
        cout << "darr[" << i << "] �ּ� = 0x" << (darr + i) << endl;
    }

    char* carr = new char[6];
    for (int i = 0; i < 5; i++)
    {
        carr[i] = 'A' + i;
        carr[i] = 65 + i;
        carr[i] = 0x41 + i;
    }
    carr[5] = 0;
    carr[5] = '\0';
    carr[5] = NULL;

    cout << "[heap] char �����迭 ������ carr�� ũ�� : " << sizeof(carr) << endl;
    cout << "[heap] char �����迭 ������ carr�� �� : " << carr << endl;
    cout << "[heap] char �����迭 ������ carr�� �ּ� : 0x" << &carr << endl;
    cout << "[heap] char �����迭 ������ carr�� ������ : " << *carr << endl;
    cout << "-----------------------------------------------------------------" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "carr[" << i << "] �� = " << *(carr + i) << endl;
        cout << "carr[" << i << "] �ּ� = 0x" << (&carr + i) << endl;
    }

    return 0;
}