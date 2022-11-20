#pragma once
#include <windows.h>
#include <map>
#include <string>
#include "MyThread.h"

using namespace std;

//SingletonClass
class MyProgram
{
private:
    MyProgram();
    MyProgram(const MyProgram& ref) = delete;
    MyProgram& operator=(const MyProgram& ref) = delete;
    ~MyProgram();
public:
    int number;
    CRITICAL_SECTION csnumber;
    map<string, MyThread*> mThreadMap;
    static MyProgram& GetInstance()
    {
        static MyProgram s;
        return s;
    }
    virtual void Init();
    virtual void Start();
    virtual void Finish();
};

#define GMyProgram MyProgram::GetInstance()