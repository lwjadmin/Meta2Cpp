/*----------------------------------------------------------------
    Server 1 : Client N Chatting - 전역변수 떡칠
    새로운 클라가 붙으면 OnRecv Thread가 1개가 만들어진다!
    접속자에 따라 OnRecv Thread가 무한히 늘어날 수 있기 때문에 성능상 안좋다..
    [TODO_1] Socket Select를 사용하여 처리!
    [TODO_2] MessageHeader/MessageID를 사용하여 메시지별 데이터를 다르게 처리!
    [TODO_3] 클라에서 최초접속 시 ReqAllMsgList & OnRecvQueue : ResAllMsgList 처리
    [TODO_4] 클래스로 만들어보기!!
----------------------------------------------------------------*/
/*
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <process.h>
#include <Windows.h>  
#include <timeapi.h>

#include <iostream>   
#include <queue>
#include <vector>
#include <string>

using namespace std;

//스레드 핸들
HANDLE H_OnRecvQueue = nullptr;
HANDLE H_OnSendQueue = nullptr;
HANDLE H_OnSend = nullptr;

//크리티컬 섹션 
CRITICAL_SECTION CS_RCV = { 0, };
CRITICAL_SECTION CS_SND = { 0, };
CRITICAL_SECTION CS_SOC = { 0, };
CRITICAL_SECTION CS_LOG = { 0, };

//TCP서버
WSAData wsadata = { 0, };
SOCKET socketsvr = NULL;
SOCKADDR_IN svraddr = { 0, };

//프로그램 while용 bool값
bool ProgramRunning = false;

//공용 STL 저장소
vector<string> vMsgList;
queue<pair<SOCKET, string>> SendQueue;
queue<pair<SOCKET, string>> RecvQueue;
vector<SOCKET> vClientList;

#define SERVER_IPV4 "127.0.0.1"
#define SERVER_PORT 4949
#define PACKET_SIZE 1024

unsigned OnRecvQueue(void* args)  
{
    while (ProgramRunning)
    {
        if (ProgramRunning) { WaitForSingleObject(H_OnSendQueue, 100); }
        EnterCriticalSection(&CS_RCV);
        while (!RecvQueue.empty())
        {
            auto qItem = RecvQueue.front();
            cout << "[Server Recv]" << qItem.second << endl;
            SendQueue.push(qItem);
            RecvQueue.pop();
        }
        LeaveCriticalSection(&CS_RCV);
    }
    while (!RecvQueue.empty()) { RecvQueue.pop(); }
    return 0;
}

unsigned OnSendQueue(void* args)  
{
    while (ProgramRunning)
    {
        if (ProgramRunning) { WaitForSingleObject(H_OnSendQueue, 100); }
        EnterCriticalSection(&CS_SND);
        while (!SendQueue.empty())
        {
            auto qItem = SendQueue.front();
            string msg = qItem.second;
            int szmsg = (int)strlen(msg.c_str());
            char Buffer[PACKET_SIZE] = { 0, };
            memcpy(Buffer, msg.c_str(), szmsg);
            SendQueue.pop();
            EnterCriticalSection(&CS_SOC);
            for (int i = (int)vClientList.size() - 1; i >= 0; --i)
            {
                if (qItem.first != NULL && qItem.first == vClientList[i]) { continue; }
                cout << "[Server Send]" << msg << endl;
                int SendBytes = send(vClientList[i], Buffer, szmsg + 1, 0);
                if (SendBytes <= 0)
                {
                    closesocket(vClientList[i]);
                    vClientList.erase(vClientList.begin() + i);
                }
            }
            LeaveCriticalSection(&CS_SOC);
        }
        LeaveCriticalSection(&CS_SND);
    }
    while (!SendQueue.empty()) { SendQueue.pop(); }
    return 0;
}

unsigned OnRecv(void* args)
{
    SOCKET socketcli = *(SOCKET*)args;
    bool InitOnce = false;
    if (ProgramRunning)
    {
        cout << "Client Connected, ClientCount :" << vClientList.size() << endl;
    }

    if (InitOnce)
    {
        //TODO : MessageHeader / MessageBody의 구분이 필요하다!!
        //EnterCriticalSection(&CS_LOG);
        //for (int i = 0; i < vMsgList.size(); ++i)
        //{
        //    EnterCriticalSection(&CS_SND);
        //    //SendQueue.push(make_pair(socketcli, vMsgList[i]));
        //    LeaveCriticalSection(&CS_SND);
        //}
        //LeaveCriticalSection(&CS_LOG);
    }
    while (true)
    {
        char Buffer[PACKET_SIZE] = { 0, };
        int RecvBytes = recv(socketcli, Buffer, sizeof(Buffer) - 1, 0);
        if (RecvBytes <= 0)
        {
            break;
        }
        else
        {
            EnterCriticalSection(&CS_RCV);
            RecvQueue.push(make_pair(socketcli,Buffer));
            LeaveCriticalSection(&CS_RCV);
            EnterCriticalSection(&CS_LOG);
            vMsgList.push_back(Buffer);
            LeaveCriticalSection(&CS_LOG);
        }
    }
    EnterCriticalSection(&CS_SOC);
    vClientList.erase(find(vClientList.begin(), vClientList.end(), socketcli));
    LeaveCriticalSection(&CS_SOC);
    if (ProgramRunning)
    {
        cout << "Client Disconnected, ClientCount :" << vClientList.size() << endl;
    }
    return 0;
}

unsigned OnSend(void* args)  
{
    cout << "[TIP] Wanna SendToAll? Send Any Message" << endl;
    while (ProgramRunning)
    {
        if (ProgramRunning) { WaitForSingleObject(H_OnSend, 100); }
        string msg = "";
        getline(cin, msg);
        if (strcmp(msg.c_str(), "exit") == 0)
        {
            ProgramRunning = false;
            EnterCriticalSection(&CS_SOC);
            for (auto socketcli : vClientList) { closesocket(socketcli); }
            LeaveCriticalSection(&CS_SOC);
            break;
        }
        EnterCriticalSection(&CS_SND);
        SendQueue.push(make_pair(NULL, msg));
        LeaveCriticalSection(&CS_SND);
    }
    return 0;
}

int H20221120_TCPServer6_main(int argc, char* argv[])
{
    InitializeCriticalSection(&CS_RCV);
    InitializeCriticalSection(&CS_SND);
    InitializeCriticalSection(&CS_SOC);
    InitializeCriticalSection(&CS_LOG);

    WSAStartup(MAKEWORD(2, 2), &wsadata);
    socketsvr = socket(AF_INET, SOCK_STREAM, 0);
    svraddr.sin_family = AF_INET;
    svraddr.sin_addr.S_un.S_addr = INADDR_ANY;
    svraddr.sin_port = htons(4949);
    bind(socketsvr, (sockaddr*)&svraddr, sizeof(svraddr));
    listen(socketsvr, SOMAXCONN);
    ProgramRunning = true;

    H_OnRecvQueue = (HANDLE)_beginthreadex(nullptr, 0, OnRecvQueue, nullptr, 0, nullptr);
    H_OnSendQueue = (HANDLE)_beginthreadex(nullptr, 0, OnSendQueue, nullptr, 0, nullptr);
    H_OnSend = (HANDLE)_beginthreadex(nullptr, 0, OnSend, nullptr, 0, nullptr);
    
    while (ProgramRunning)
    {
        Sleep(1);
        SOCKADDR_IN cliaddr = { 0, };
        int szcliaddr = sizeof(cliaddr);
        SOCKET socketcli = accept(socketsvr, (sockaddr*)&cliaddr, &szcliaddr);
        EnterCriticalSection(&CS_SOC);
        vClientList.push_back(socketcli);
        LeaveCriticalSection(&CS_SOC);
        _beginthreadex(nullptr, 0, OnRecv, (void*)&socketcli, 0, nullptr);
    }
    if (H_OnRecvQueue) { CloseHandle(H_OnRecvQueue); }
    if (H_OnSendQueue) { CloseHandle(H_OnSendQueue); }
    if (H_OnSend) { CloseHandle(H_OnSend); }

    closesocket(socketsvr);
    DeleteCriticalSection(&CS_RCV);
    DeleteCriticalSection(&CS_SND);
    DeleteCriticalSection(&CS_SOC);
    DeleteCriticalSection(&CS_LOG);
    WSACleanup();
    return 0;
}
*/