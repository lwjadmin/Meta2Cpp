#pragma once

#include <iostream>

using namespace std;

class CustomStack
{
public:
    int* Data;
    int Size;
    int Capacity;
    CustomStack()
    {
        Capacity = 1;
        Size = 0;
        Data = new int[Capacity];
        memset(Data, 0, sizeof(int) * Capacity);
    }
    CustomStack(int InCapacity)
    {
        Capacity = InCapacity;
        Size = 0;
        Data = new int[Capacity];
        memset(Data, 0, sizeof(int) * Capacity);
    }
    bool IsFull()
    {
        return Size == Capacity -1 ? true : false;
    }
    bool IsEmpty()
    {
        return Size == 0 ? true : false;
    }
    void Push(int value)
    {
        if (Size < Capacity)
        {
            Data[Size] = value;
            Size++;
        }
        else
        {
            int newCapacity = Capacity * 2;
            int* newData = new int[newCapacity];
            memset(newData, 0, sizeof(int) * newCapacity);
            memcpy(newData, Data, sizeof(int) * Capacity);
            cout << "Resized! prevCapacity : " << Capacity << ", newCapacity : " << newCapacity << endl;

            Capacity = newCapacity;
            delete[] Data;
            Data = newData;
            Data[Size] = value;
            Size++;
        }
    }

    void Resize()
    {
        int newCapacity = Capacity / 2;
        if (Size < newCapacity)
        {
            int* newData = new int[newCapacity];
            memset(newData, 0, sizeof(int) * newCapacity);
            memcpy(newData, Data, sizeof(int) * newCapacity);
            cout << "Resized! prevCapacity : " << Capacity << ", newCapacity : " << newCapacity << endl;

            Capacity = newCapacity;
            delete[] Data;
            Data = newData;
        }
    }

    void Pop()
    {
        if (!IsEmpty())
        {
            Resize();
            Size--;
        }
    }
    int Top()
    {
        return Data[Size-1];
    }
    void ShowAll()
    {
        for (int i = 0; i < Size; i++)
        {
            cout << "CustomStack[" << i <<"] : " << Data[i] << endl;
        }
    }

    ~CustomStack()
    {
        delete[] Data;
    }
};