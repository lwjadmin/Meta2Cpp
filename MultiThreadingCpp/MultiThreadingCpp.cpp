/*-----------------------------------------------------------------------------------------------
※ 프로그램 / 프로세스 / 스레드

-- 파일 : 프로그램 파일과 데이터 파일로 구분된다. 
          프로그램 파일 : 순차적으로 진행되는 실행파일
          데이터 파일 : 순차적인 진행과정이 필요없는 단순한 자료


-- 프로그램 : 저장장치에 저장된 실행파일
-- 프로세스 : 메모리에 로드되어 실행중인 파일


※ 유저 모드와 커널 모드

-- 커널 : 운영체제의 핵심 부분으로, 디바이스 드라이버 입출력처리, CPU 스케줄링, 메모리 관리, 파일시스템&파일 관리를 수행한다.

-- 메모리에 운영체제와 응용프로그램이 로드되어 동작하면, 커널과 관련된 메모리 영역이 별도로 존재할 것이다. 
   메모리


   User Mode : OS 자원 요청(Req)/응답(Res)
   ------------------------------------------------
   Kernel Mode : OS 자원(CPU/메모리/디스크/파일) 접근
   
   HANDLE : UserMode에서 객체 생성 요청을 Kernel에 요청한 다음, 
            Kernel에서 만든 객체의 메모리 위치를 반환하며,
            해당 메모리의 위치를 HANDLE이라고 한다.
   
            커널에서 생성한 객체(커널오브젝트)는 구조체로 관리하는데,
            이때 핸들이라는 구조체 포인터로 접근해서 커널오브젝트를 관리할 수 있다!!!
   
※ cdecl / stdcall 차이 
  함수 생성 후 메모리를 정리할 때, 호출한 함수 스코프에서 메모리를 정리할 건지, 
  부모 함수 스코프에서 메모리를 정리할 건지 선택하는 옵션이다.

  https://learn.microsoft.com/ko-kr/cpp/c-runtime-library/reference/beginthread-beginthreadex?view=msvc-170
-------------------------------------------------------------------------------------------------*/

#include <iostream>
#include <process.h>
#include <Windows.h>
#include <conio.h>
#include <timeapi.h>

using namespace std;

#pragma  comment(lib, "Winmm.lib") //For timeGetTime()

//unsigned WINAPI Thread(void* Arg) //X86 & X64 (WINAPI : __stdcall)
unsigned Thread(void* Arg) //X64 only
{
    for (int i = 1; i <= 100; i++)
    {
        cout << i << endl;
    }
    return 0;
}

int GlobalGold = 100; //전역변수 설정

CRITICAL_SECTION GoldCS; //유저 모드 동기화 객체 - 임계영역(CriticalSection) 설정

unsigned Increase(void* Arg) 
{
    //크리티컬 섹션(임계영역)의 지정은 성능에 많은 영향을 미치므로 신중하게 지정해야 한다.
    for (int i = 1; i < 1000000; i++)
    {
        EnterCriticalSection(&GoldCS);
        GlobalGold++;
        LeaveCriticalSection(&GoldCS);
    }
    
    return 0;
}

unsigned Decrease(void* Arg)
{
    
    for (int i = 1; i < 1000000; i++)
    {
        EnterCriticalSection(&GoldCS);
        GlobalGold--;
        LeaveCriticalSection(&GoldCS);
    }
    
    return 0;
}
/*---------------------------------------------------------
    ※ 유저모드, 커널모드, 커널오브젝트(스레드 객체), 핸들

    윈도우 프로그램은 프로세스 실행 시 메인 스레드를 만들고 실행한다.
    메인함수는 메인스레드에서 동작한다.
    BeginThreadEx : 스레드를 생성해달라고 OS에 요청한다.
    InitFlag : 0 (즉시시작) / CREATE_SUSPENDED (대기)
    StackSize : 0일 경우 스레드의 스택크기를 최대크기로 사용할 수 있다!
                0 권장
    Security : 보안옵션, nullptr 권장

    메인 스레드가 꺼지면 자식 스레드도 꺼진다.

    스레드간 통신시 Context Switching을 한다.
    스레드 생성 권장 갯수는 물리적 CPU의 스레드 개수 내로 만드는게 좋다.
    ex) 4코어 8스레드 : 7개 내로 만들자 (1 : 메인스레드)

    메인스레드가 죽으면 자식스레드가 죽는다.
---------------------------------------------------------*/

int MultiThreadingCpp_main(int argc, char* argv[])
//int main(int argc, char* argv[])
{
    InitializeCriticalSection(&GoldCS);
    unsigned int ThreadID1 = 0;
    unsigned int ThreadID2 = 0;
    char Message[] = "안녕하세요.";
    int number = 5;
    DWORD StartMs = timeGetTime(); //Get MilliSecond Timer
    HANDLE ThreadHandles[2];
    ThreadHandles[0] = (HANDLE)_beginthreadex(nullptr, 0, Increase, nullptr, 0, &ThreadID1);
    ThreadHandles[1] = (HANDLE)_beginthreadex(nullptr, 0, Decrease, nullptr, 0, &ThreadID2);
    WaitForMultipleObjects(2, ThreadHandles, true, INFINITE);
    DWORD FnshMs = timeGetTime();
    cout << "Elapsed Milliseconds : " << (StartMs - FnshMs) << endl;
    cout << GlobalGold << endl;

    ////스레드를 재실행한다.(시작!!)
    //ResumeThread(ThreadHandle);
    //
    //Sleep(10);
    ////스레드를 멈춘다.
    //SuspendThread(ThreadHandle);
    //
    //Sleep(1000);
    ////스레드를 재실행한다.(이전에 멈춘위치로부터 다시시작)
    //ResumeThread(ThreadHandle);
    // 
    ////스레드를 강제종료한다.
    ////TerminateThread(ThreadHandle, -1);
    ////스레드가 끝날 때까지 무한히 기다린다...
    //WaitForSingleObject(ThreadHandle, INFINITE);
    ////Thread가 Signal 상태(꺼짐)가 될때까지 0.3초간 기다린다. 
    ////WaitForSingleObject(ThreadHandle, 300);

    for (int i = 0; i < 2; i++)
    {
        if(ThreadHandles[i]){ CloseHandle(ThreadHandles[i]); }
    }
    DeleteCriticalSection(&GoldCS);
    return 0;
}
