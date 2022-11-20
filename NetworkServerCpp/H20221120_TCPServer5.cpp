/*----------------------------------------------------------------
    Server 1 : Client 1 Chatting - Àü¿ªº¯¼ö ¶±Ä¥

----------------------------------------------------------------*/
/*
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <process.h>
#include <Windows.h>  
#include <timeapi.h>

#include <iostream>   
#include <queue>
#include <string>

using namespace std;

HANDLE h1;
HANDLE h2;
HANDLE h3;
HANDLE h4;

CRITICAL_SECTION CS_RCV;
CRITICAL_SECTION CS_SND;

SOCKET socketsvr = NULL;
SOCKET socketcli = NULL;

SOCKADDR_IN cliaddr = { 0, };
int szcliaddr = sizeof(cliaddr);
SOCKADDR_IN svraddr = { 0, };
WSAData wsadata = { 0, };

bool NetworkRunning = false;
bool ProgramRunning = false;

queue<string> SendQueue;
queue<string> RecvQueue;

unsigned OnRecvQueue(void* args) //h1
{
    while (ProgramRunning)
    {
        if (!NetworkRunning)
        {
            if (ProgramRunning) { WaitForSingleObject(h1, 100); }
            continue;
        }
        EnterCriticalSection(&CS_RCV);
        while (!RecvQueue.empty())
        {
            string msg = RecvQueue.front();
            cout << "[Server Recv]" << msg << endl;
            SendQueue.push(msg);
            RecvQueue.pop();
        }
        LeaveCriticalSection(&CS_RCV);
    }
    while (!RecvQueue.empty()) { RecvQueue.pop(); }
    return 0;
}

unsigned OnSendQueue(void* args) //h2
{
    while (ProgramRunning)
    {
        if (!NetworkRunning)
        {
            if (ProgramRunning) { WaitForSingleObject(h2, 100); }
            continue;
        }
        EnterCriticalSection(&CS_SND);
        while (!SendQueue.empty())
        {
            string msg = SendQueue.front();
            int szmsg = (int)strlen(msg.c_str());
            cout << "[Server Send]" << msg << endl;
            char Buffer[1024] = { 0, };
            memcpy(Buffer, msg.c_str(), szmsg);
            int SendBytes = send(socketcli, Buffer, szmsg + 1, 0);
            NetworkRunning = SendBytes <= 0 ? false : true;
            SendQueue.pop();
        }
        LeaveCriticalSection(&CS_SND);
    }
    while (!SendQueue.empty()) { SendQueue.pop(); }
    return 0;
}

unsigned OnRecv(void* args) //h3
{
    while (NetworkRunning)
    {
        char Buffer[1024] = { 0, };
        int RecvBytes = recv(socketcli, Buffer, sizeof(Buffer) - 1, 0);
        if (RecvBytes <= 0)
        {
            NetworkRunning = false;
            break;
        }
        else
        {
            EnterCriticalSection(&CS_RCV);
            RecvQueue.push(Buffer);
            LeaveCriticalSection(&CS_RCV);
        }
    }
    return 0;
}

unsigned OnSend(void* args) //h4
{
    cout << "[TIP] Wanna SendToAll? Send Any Message" << endl;
    while (ProgramRunning)
    {
        if (!NetworkRunning)
        {
            if (ProgramRunning) { WaitForSingleObject(h4, 100); }
            continue;
        }
        string msg = "";
        getline(cin, msg);
        if (strcmp(msg.c_str(), "exit") == 0)
        {
            ProgramRunning = false;
            break;
        }
        EnterCriticalSection(&CS_SND);
        SendQueue.push(msg);
        LeaveCriticalSection(&CS_SND);
    }
    closesocket(socketcli);
    return 0;
}

int H20221120_TCPServer5_main(int argc, char* argv[])
{
    InitializeCriticalSection(&CS_RCV);
    InitializeCriticalSection(&CS_SND);
    WSAStartup(MAKEWORD(2, 2), &wsadata);
    socketsvr = socket(AF_INET, SOCK_STREAM, 0);
    svraddr.sin_family = AF_INET;
    svraddr.sin_addr.S_un.S_addr = INADDR_ANY; 
    svraddr.sin_port = htons(4949);
    bind(socketsvr, (sockaddr*)&svraddr, sizeof(svraddr));
    listen(socketsvr, SOMAXCONN);
    ProgramRunning = true;

    h1 = (HANDLE)_beginthreadex(nullptr, 0, OnRecvQueue, nullptr, 0, nullptr);
    h2 = (HANDLE)_beginthreadex(nullptr, 0, OnSendQueue, nullptr, 0, nullptr);
    h4 = (HANDLE)_beginthreadex(nullptr, 0, OnSend, nullptr, 0, nullptr);
    Sleep(10);
    while (ProgramRunning)
    {
        if (!NetworkRunning)
        {
            cout << "Connecting...";
            socketcli = accept(socketsvr, (sockaddr*)&cliaddr, &szcliaddr);
            cout << "Connected!" << endl;
            cout << "[NETWORK START]" << endl;
            NetworkRunning = true;
            h3 = (HANDLE)_beginthreadex(nullptr, 0, OnRecv, nullptr, 0, nullptr);
        }
        if (h3) { WaitForSingleObject(h3, INFINITE); }
        cout << "[NETWORK FINISH]" << endl;
    }
    WSACleanup();
    if (h1) { CloseHandle(h1); }
    if (h2) { CloseHandle(h2); }
    if (h3) { CloseHandle(h3); }
    if (h4) { CloseHandle(h4); }
    DeleteCriticalSection(&CS_RCV);
    DeleteCriticalSection(&CS_SND);
    return 0;
}
*/