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

//객체, 클래스 - 부모클래스
class Fruit
{
    //접근 제한자
public:
    //멤버변수, 속성(Properties)
    int Color;
    int Shape;
    int Brix;
    int Size;
    //생성자(Default생성자)
    Fruit()
    {
        cout << "기본 과일 생성자" << endl;
        Color = 0;
        Shape = 0;
        Brix = 0;
        Size = 0;
    }
    //멤버함수, 메소드(Method)
    void Eaten()
    {
        cout << "과일이 먹혔습니다!" << endl;
    }
    void ShowAll()
    {
        cout << "Color : " << Color << endl;
        cout << "Shape : " << Shape << endl;
        cout << "Brix : " << Brix << endl;
        cout << "Size : " << Size << endl;
    }
};

//객체, 클래스 - 자식클래스, 부모클래스(Fruit) 상속
class Apple : public Fruit
{
    //접근 제한자
public:
    //생성자(Default생성자)
    Apple()
    {
        cout << "기본 사과 생성자" << endl;
        Color = 0;
        Shape = 0;
        Brix = 10;
        Size = 10;
    }
    //생성자(생성자 오버로딩)
    Apple(int NewBrix, int NewSize)
    {
        cout << "사과 생성자 오버로딩(재정의)됨" << endl;
        Color = 0;
        Shape = 0;
        Brix = NewBrix;
        Size = NewSize;
    }
    //멤버함수
    void Eaten()
    {
        cout << "사과가 먹힘" << endl;
    }
};

//객체, 클래스 - 자식클래스, 부모클래스(Fruit) 상속
class Orange : public Fruit
{
    //접근 제한자
public:
    //생성자(Default생성자)
    Orange()
    {
        cout << "기본 오렌지 생성자" << endl;
        this->Color = 0;
        this->Shape = 0;
        this->Brix = 10;
        this->Size = 10;
    }
    //생성자(생성자 오버로딩)
    Orange(int NewBrix, int NewSize)
    {
        cout << "오렌지 생성자 오버로딩됨" << endl;
        Color = 0;
        Shape = 0;
        Brix = NewBrix;
        Size = NewSize;
    }
    //멤버함수
    void Eaten()
    {
        cout << "오렌지가 먹힘" << endl;
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
    int NextState = FSM.GetNextState(1, "적발견");
    cout << FSM.GetStateName(NextState) << endl;
}

void RunTest4_Character()
{
    vector<Character> CharacterList;
    CharacterList.push_back(Character(1, "캐릭1", 38, 34));
    CharacterList.push_back(Character(2, "캐릭2", 14, 50));
    CharacterList.push_back(Character(3, "캐릭3", 11, 35));

    map<string, Character> CharacterMap;
    CharacterMap.insert(make_pair<string,Character>("캐릭1", Character(1, "캐릭1", 38, 34)));
    CharacterMap.insert(make_pair<string,Character>("캐릭2", Character(2, "캐릭2", 14, 50)));
    CharacterMap.insert(make_pair<string,Character>("캐릭3", Character(3, "캐릭3", 11, 35)));
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