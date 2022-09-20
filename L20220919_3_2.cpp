#include <iostream>

using namespace std;

int* InitDynamicArray(int size)
{
    int* pArr = new int[size];
    memset(pArr, 0, sizeof(int)* size);
    return pArr;
}

void RemoveDynamicArray(int* pArr)
{
    if (pArr != nullptr)
    {
        delete[] pArr;
    }
}

void PrintDynamicArray(int* pArr, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << pArr[i] << (i != size - 1 ? "," : "\n");
    }
}

int* ResizeDynamicArray(int* pArr, int prevsize, int newsize)
{
    int* pArr2 = InitDynamicArray(newsize);
    for (int i = 0; i < prevsize; i++)
    {
        pArr2[i] = pArr[i];
    }
    delete[] pArr;
    return pArr2;
}

int L20220919_3_2_main()
{
    int* pArr = nullptr;
    int size = 10;
    pArr = InitDynamicArray(size);
    for (int i = 0; i < 10; i++)
    {
        pArr[i] = i + 1;
    }
    PrintDynamicArray(pArr, size);
    pArr = ResizeDynamicArray(pArr, size, size + 10);
    for (int i = 10; i < 20; i++)
    {
        pArr[i] = i + 1;
    }
    size = size + 10;
    PrintDynamicArray(pArr, size);
    RemoveDynamicArray(pArr);
    return 0;
}