#include <iostream>
#include <vector>
#include <map>
#include <conio.h>

#include "Pixel.h"
#include "Character.h"
#include "MonsterFSM.h"
#include "XLClass.h"
#include "CustomStack.h"

using namespace std;
using namespace lwj;

//��ü, Ŭ���� - �θ�Ŭ����
class Fruit
{
    //���� ������
public:
    //�������, �Ӽ�(Properties)
    int Color;
    int Shape;
    int Brix;
    int Size;
    //������(Default������)
    Fruit()
    {
        cout << "�⺻ ���� ������" << endl;
        Color = 0;
        Shape = 0;
        Brix = 0;
        Size = 0;
    }
    //����Լ�, �޼ҵ�(Method)
    void Eaten()
    {
        cout << "������ �������ϴ�!" << endl;
    }
    void ShowAll()
    {
        cout << "Color : " << Color << endl;
        cout << "Shape : " << Shape << endl;
        cout << "Brix : " << Brix << endl;
        cout << "Size : " << Size << endl;
    }
};

//��ü, Ŭ���� - �ڽ�Ŭ����, �θ�Ŭ����(Fruit) ���
class Apple : public Fruit
{
    //���� ������
public:
    //������(Default������)
    Apple()
    {
        cout << "�⺻ ��� ������" << endl;
        Color = 0;
        Shape = 0;
        Brix = 10;
        Size = 10;
    }
    //������(������ �����ε�)
    Apple(int NewBrix, int NewSize)
    {
        cout << "��� ������ �����ε�(������)��" << endl;
        Color = 0;
        Shape = 0;
        Brix = NewBrix;
        Size = NewSize;
    }
    //����Լ�
    void Eaten()
    {
        cout << "����� ����" << endl;
    }
};

//��ü, Ŭ���� - �ڽ�Ŭ����, �θ�Ŭ����(Fruit) ���
class Orange : public Fruit
{
    //���� ������
public:
    //������(Default������)
    Orange()
    {
        cout << "�⺻ ������ ������" << endl;
        this->Color = 0;
        this->Shape = 0;
        this->Brix = 10;
        this->Size = 10;
    }
    //������(������ �����ε�)
    Orange(int NewBrix, int NewSize)
    {
        cout << "������ ������ �����ε���" << endl;
        Color = 0;
        Shape = 0;
        Brix = NewBrix;
        Size = NewSize;
    }
    //����Լ�
    void Eaten()
    {
        cout << "�������� ����" << endl;
    }
};

void RunTest1_Fruit()
{
    Apple MyApple;
    MyApple.Color = 0;
    MyApple.Shape = 0;
    MyApple.Brix = 10;
    MyApple.Size = 10;
    MyApple.ShowAll();
    Apple MyApple2(5, 5);
    MyApple2.ShowAll();
    
    Orange MyOrange;
    MyOrange.Color = 0;
    MyOrange.Shape = 0;
    MyOrange.Brix = 10;
    MyOrange.Size = 10;
    MyOrange.ShowAll();
    Orange MyOrange2(7, 7);
    MyOrange2.ShowAll();
}

void RunTest2_Image()
{
    const int VerticalResolution = 240;
    const int HorizontalResolution = 320;
    Pixel* Image = new Pixel[HorizontalResolution * VerticalResolution];

    for (int v = 0; v < VerticalResolution; v++)
    {
        for (int h = 0; h < HorizontalResolution; h++)
        {
            Pixel* p = &Image[v * VerticalResolution + h];
            p->X = h;
            p->Y = v;
            p->R = 255;
            p->G = 255;
            p->B = 255;
        }
    }
    delete[] Image;
}

void RunTest3_MonsterFSM()
{
    MonsterFSM FSM;
    int NextState = FSM.GetNextState(1, "���߰�");
    cout << FSM.GetStateName(NextState) << endl;
}

void RunTest4_Character()
{
    vector<Character> CharacterList;
    CharacterList.push_back(Character(1, "ĳ��1", 38, 34));
    CharacterList.push_back(Character(2, "ĳ��2", 14, 50));
    CharacterList.push_back(Character(3, "ĳ��3", 11, 35));

    map<string, Character> CharacterMap;
    CharacterMap.insert(make_pair<string,Character>("ĳ��1", Character(1, "ĳ��1", 38, 34)));
    CharacterMap.insert(make_pair<string,Character>("ĳ��2", Character(2, "ĳ��2", 14, 50)));
    CharacterMap.insert(make_pair<string,Character>("ĳ��3", Character(3, "ĳ��3", 11, 35)));
}

void RunTest5_CustomXLClass()
{
    //XLWorkBook ExcelWorkBook;
    //ExcelWorkBook.CreateXLWorkBook("file1.xlsx");
    //XLSheet ExcelSheet1("sheet1");
    //ExcelSheet1.XLCells.Set(0, 1, 1);
    //ExcelSheet1.XLCells.Set(0, 1, 2);
    //ExcelSheet1.XLCells.Set(0, 1, 3);
    //ExcelWorkBook.XLSheets.push_back(ExcelSheet1);
}


void RunTodo1_CustomStack()
{
    CustomStack stack;
    for (int i = 0; i < 100; i++)
    {
        stack.Push(i);
    }
    stack.ShowAll();
    while (!stack.IsEmpty())
    {
        cout << stack.Top() << endl;
        stack.Pop();
    }
    stack.ShowAll();
}

int L20221004_2_main()
{
    //RunTest1_Fruit();
    //RunTest2_Image();
    //RunTest3_MonsterFSM();
    //RunTest4_Character();
    //RunTest5_CustomXLClass();
    RunTodo1_CustomStack();
    return 0;
}