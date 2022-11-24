#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <process.h>

#include <string>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

bool G_ProgramRunning = true;

HANDLE HandleSend = nullptr;
HANDLE HandleRecvQ = nullptr;
HANDLE HandleSendQ = nullptr;

vector<string> MsgList;
CRITICAL_SECTION CS_MsgList;

vector<SOCKET> ClientList;
CRITICAL_SECTION CS_ClientList;

queue<pair<SOCKET, string>> SendQueue;
CRITICAL_SECTION CS_SendQueue;

queue<pair<SOCKET,string>> RecvQueue;
CRITICAL_SECTION CS_RecvQueue;

#define SERVER_IPV4 "127.0.0.1"
#define SERVER_PORT 5001
#define PACKET_SIZE 1024


unsigned OnProcessRecvQ(void* args)
{
    while (G_ProgramRunning)
    {
        if (RecvQueue.size() == 0) { WaitForSingleObject(HandleRecvQ, 1); continue; }
        EnterCriticalSection(&CS_RecvQueue);
        while (!RecvQueue.empty())
        {
            pair<SOCKET, string> QItem = RecvQueue.front();
            RecvQueue.pop();
            if (QItem.second == "#CLIENT_GETALL_LIST")
            {
                EnterCriticalSection(&CS_SendQueue);
                SendQueue.push(QItem);
                LeaveCriticalSection(&CS_SendQueue);
            }
            else
            {
                EnterCriticalSection(&CS_SendQueue);
                cout << "[Server] : " << QItem.second << endl;
                SendQueue.push(make_pair(NULL, QItem.second));
                LeaveCriticalSection(&CS_SendQueue);
            }
        }
        LeaveCriticalSection(&CS_RecvQueue);
    }
    return 0;
}

unsigned OnRecvMessage(void* args)
{
    SOCKET *SocketClient = (SOCKET*)args;
    char Buffer[PACKET_SIZE] = { 0, };
    int RecvBytes = 0;
    while (true)
    {
        memset(Buffer, 0, sizeof(Buffer));
        //In Order to Make Buffer Null Terminated String, Minus 1
        RecvBytes = recv(*SocketClient, Buffer, sizeof(Buffer) - 1, 0);
        if (RecvBytes <= 0)
        {
            EnterCriticalSection(&CS_ClientList);
            ClientList.erase(find(ClientList.begin(), ClientList.end(), *SocketClient));
            LeaveCriticalSection(&CS_ClientList);
            break;
        }
        //1.
        EnterCriticalSection(&CS_ClientList);
        RecvQueue.push(make_pair(*SocketClient, Buffer));
        LeaveCriticalSection(&CS_ClientList);
        //2.
        EnterCriticalSection(&CS_MsgList);
        MsgList.push_back(Buffer);
        LeaveCriticalSection(&CS_MsgList);
    }
    return 0;
}

unsigned OnProcessSendQ(void* args)
{
    char Buffer[PACKET_SIZE] = { 0, };
    int SendBytes = 0;

    while (G_ProgramRunning)
    {
        if (SendQueue.size() == 0) { WaitForSingleObject(HandleSendQ, 1); continue; }
        EnterCriticalSection(&CS_SendQueue);
        while (!SendQueue.empty())
        {
            pair<SOCKET, string> QItem = SendQueue.front();
            SendQueue.pop();

            if (QItem.second == "#CLIENT_GETALL_LIST")
            {
                EnterCriticalSection(&CS_MsgList);
                for (int i = 0; i < MsgList.size(); i++)
                {
                    if (MsgList[i] == "#CLIENT_GETALL_LIST") { continue; }
                    memset(Buffer, 0, sizeof(Buffer));
                    memcpy(Buffer, MsgList[i].c_str(), strlen(MsgList[i].c_str()));
                    
                    SendBytes = send(QItem.first, Buffer, strlen(MsgList[i].c_str()) + 1, 0);
                    cout << "Msg : " << MsgList[i] <<", sendbytes :" << SendBytes << endl;

                }
                LeaveCriticalSection(&CS_MsgList);
            }
            else
            {
                EnterCriticalSection(&CS_ClientList);
                memset(Buffer, 0, sizeof(Buffer));
                int msglen = strlen(QItem.second.c_str());
                memcpy(Buffer, QItem.second.c_str(), msglen);
                for (int i = (int)ClientList.size() - 1; i >= 0; --i)
                {
                    int SendBytes = send(ClientList[i], Buffer, msglen + 1, 0);
                    if (SendBytes <= 0)
                    {
                        closesocket(ClientList[i]);
                        ClientList.erase(ClientList.begin() + i);
                    }
                }
                LeaveCriticalSection(&CS_ClientList);
            }
        }
        LeaveCriticalSection(&CS_SendQueue);
    }
    return 0;
}


unsigned OnSendMessage(void* args)
{
    cout << "[TIP] Wanna SendToAll? Send Any Message" << endl;
    while (G_ProgramRunning)
    {
        string msg = "";
        getline(cin, msg);
        if (strcmp(msg.c_str(), "EXIT") == 0)
        {
            G_ProgramRunning = false;
            EnterCriticalSection(&CS_ClientList);
            for (auto socketcli : ClientList) { closesocket(socketcli); }
            LeaveCriticalSection(&CS_ClientList);
            break;
        }
        EnterCriticalSection(&CS_SendQueue);
        SendQueue.push(make_pair(NULL, msg));
        LeaveCriticalSection(&CS_SendQueue);
    }
    return 0;
}


int main(int argc, char* argv[])
{
    InitializeCriticalSection(&CS_MsgList);
    InitializeCriticalSection(&CS_ClientList);
    InitializeCriticalSection(&CS_SendQueue);
    InitializeCriticalSection(&CS_RecvQueue);
    WSADATA WSAData = { 0, };
    SOCKET SocketServer = NULL;
    SOCKADDR_IN ServerAddress = { 0, };

    WSAStartup(MAKEWORD(2, 2), &WSAData);
    SocketServer = socket(AF_INET, SOCK_STREAM, 0);
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_addr.S_un.S_addr = inet_addr(SERVER_IPV4);
    ServerAddress.sin_port = htons(SERVER_PORT);

    bind(SocketServer, (sockaddr*)&ServerAddress, sizeof(ServerAddress));
    listen(SocketServer, SOMAXCONN);
    
    //HandleSend = (HANDLE)_beginthreadex(nullptr, 0, OnSendMessage, nullptr, 0, nullptr);
    HandleSendQ = (HANDLE)_beginthreadex(nullptr, 0, OnProcessSendQ, nullptr, 0, nullptr);
    HandleRecvQ = (HANDLE)_beginthreadex(nullptr, 0, OnProcessRecvQ, nullptr, 0, nullptr);

    while (G_ProgramRunning)
    {
        Sleep(1);
        SOCKADDR_IN ClientAddress = { 0, };
        int szClientAddress = sizeof(ClientAddress);
        SOCKET SocketClient = accept(SocketServer, (sockaddr*)&ClientAddress, &szClientAddress);
        EnterCriticalSection(&CS_ClientList);
        ClientList.push_back(SocketClient);
        LeaveCriticalSection(&CS_ClientList);
        _beginthreadex(nullptr, 0, OnRecvMessage, (void*)&SocketClient, 0, nullptr);
    }
    if (SocketServer) { closesocket(SocketServer); }

    if (HandleSend) { CloseHandle(HandleSend); }
    if (HandleRecvQ) { CloseHandle(HandleRecvQ); }
    if (HandleSendQ) { CloseHandle(HandleSendQ); }

    DeleteCriticalSection(&CS_MsgList);
    DeleteCriticalSection(&CS_ClientList);
    DeleteCriticalSection(&CS_SendQueue);
    DeleteCriticalSection(&CS_RecvQueue);
    WSACleanup();
    return 0;
}