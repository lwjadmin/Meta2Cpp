#include <iostream>
#include <iomanip>

using namespace std;

/*-----------------------------------------------
부족한 부분 :
-------------------------------------------------
- Memory : Heap / Stack / BSS / Code / Data 구조

- 매크로보다 const 키워드로 상수선언하자.

- 정수형 / 실수형 / 문자형 메모리구조 확인

- bool 0 : false, 0이 아닌 값 : true

- 반올림/버림/올림 꼼수

- 비트연산자

- 2차원 배열과 포인터

-----------------------------------------------*/

void CheckIntSingleArray()
{
    /*-----------------------------------------------------
    1. 정적 1차원 배열은 Stack에 저장된다.
    2. 정적 1차원 배열 초기화는 다음 방법이 있다. 
       [CASE 1] 
       int arr[50] = { 0, }; //이렇게 선언하면 0으로 초기화
       int arr[50] = { 1, }; //이렇게 선언하면 맨 앞요소만 1로 초기화, 뒤는 0으로 초기화
       [CASE 2]
       memset(arr,5,sizeof(arr)); //배열을 특정값으로 초기화할 때는 memset을 써주자.
   3. 정적 1차원 배열의 개수는 배열포인터 / 배열자료형으로 나눠 구할 수 있다.
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
    1. 정적 2차원 배열은 Stack에 저장된다.
    2. 2차원 배열의 포인터를 지정해서 Rows/Cols값을 초기화할 수 있다. 
    3. Cols(열)를 먼저 구해야 Rows(행)을 구할 수 있다. 
    4. 자릿수를 구해서 숫자를 쉽게 표기할 수 있다.
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
    cout << "[stack] int 변수 number의 크기 : " << sizeof(number) << endl;
    cout << "[stack] int 변수 number의 값 : " << number << endl;
    cout << "[stack] int 변수 number의 주소 : 0x" << &number << endl;

    cout << "-----------------------------------------------------------------" << endl;
    int* pnumber = &number;
    cout << "[stack]int 포인터 변수 pnumber의 크기 : " << sizeof(pnumber) << endl;
    cout << "[stack]int 포인터 변수 pnumber의 값 :  0x" << pnumber << endl;
    cout << "[stack]int 포인터 변수 pnumber의 주소 : 0x" << &pnumber << endl;
    cout << "[stack]int 포인터 변수 pnumber의 참조값 : " << *pnumber << endl;

    cout << "-----------------------------------------------------------------" << endl;
    int* darr = new int[5];
    for (int i = 0; i < 5; i++)
    {
        *(darr + i) = i + 1;
        //darr[i] = i + 1;
    }
    cout << "[heap] int 동적배열 포인터 darr의 크기 : " << sizeof(darr) << endl;
    cout << "[heap] int 동적배열 포인터 darr의 값 : 0x" << darr << endl;
    cout << "[heap] int 동적배열 포인터 darr의 주소 : 0x" << &darr << endl;
    cout << "[heap] int 동적배열 포인터 darr의 참조값 : " << *darr << endl;
    cout << "-----------------------------------------------------------------" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "darr[" << i << "] 값 = " << *(darr + i) << endl;
        cout << "darr[" << i << "] 주소 = 0x" << (darr + i) << endl;
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

    cout << "[heap] char 동적배열 포인터 carr의 크기 : " << sizeof(carr) << endl;
    cout << "[heap] char 동적배열 포인터 carr의 값 : " << carr << endl;
    cout << "[heap] char 동적배열 포인터 carr의 주소 : 0x" << &carr << endl;
    cout << "[heap] char 동적배열 포인터 carr의 참조값 : " << *carr << endl;
    cout << "-----------------------------------------------------------------" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "carr[" << i << "] 값 = " << *(carr + i) << endl;
        cout << "carr[" << i << "] 주소 = 0x" << (&carr + i) << endl;
    }

    return 0;
}