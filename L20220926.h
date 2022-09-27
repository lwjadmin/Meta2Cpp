#pragma once
#include <iostream>
#include <random>

#include "L20220926_FWorld.h"
#include "L20220926_FPlayer.h"
#include "L20220926_FGoal.h"
#include "L20220926_FWall.h"
#include "L20220926_FFloor.h"

//STL(Standard Template Library) Container & Algorithm
#include <iostream>
#include <list> //연결형리스트
#include <vector> //벡터
#include <stack> //스택
#include <queue> //큐
#include <map> //Key/Value 값을 자동정렬해준다.
#include <set> //값을 중복되지 않게 처리해준다.
#include <string>
#include <algorithm> //자료구조를 뒤집고 섞고 하는 것들을 지원해준다. (정렬, 탐색 등...)

//Boost
//https://www.boost.org/

using namespace std;

#define DefineUseMersenTwister

#ifndef DefineUseMersenTwister
bool IsRandInitOnce = false;
#endif

enum class EnumHighLowState
{
    Unknown = INT_MIN,
    Equal = 0,
    High = 1,
    Low = 2,
};

int GetRandomNumber(int MinValue, int MaxValue);
int EventInputNumber(int MinValue, int MaxValue);
EnumHighLowState CheckNumberIsHighLow(int NumberOrigin, int NumberCompare);
void FillArrayWithRandomNumbers(int* List, int ListCount, int MinValue, int MaxValue);
void TaskInputNumberIsHighLow();
bool CheckBullsNCowsResult(int* ListOrigin, int ListOriginCount, int* ListCompare, int ListCompareCount);
void PrintIntArray(int* Array, int size);
void FillArrayWithPlayerNumbers(int* List, int ListCount, int MinValue, int MaxValue);
void TaskBullsNCows();


int UnrealStyleInitialize();
int UnrealStyleInput();
int UnrealStyleProcess(int RandomNumber, int UserNumber);
void UnrealStyleDraw(int NumberResult);
void TaskUnrealStyleRun(int RandomNumber);



//template<typename CustomType>
//class Store
//{
//public:
//    CustomType Number;
//};
//
//template<typename T>
//T AddNumber(T a, T b)
//{
//    return a + b;
//}
//
//template<typename t1, typename t2>
//t1 AddNumber(t1 A, t2 B)
//{
//    return A + B;
//}
//
//int AddNumber(int A, int B)
//{
//    return A + B;
//}
//
//float AddNumber(float A, float B)
//{
//    return A + B;
//}
//
//char AddNumber(char A, char B)
//{
//    return A + B;
//}

