#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <process.h>

#include <string>
#include <iostream>
#include <queue>

using namespace std;

#pragma comment(lib, "WS2_32.lib") 

#define SERVER_IPV4 "127.0.0.1"
#define SERVER_PORT 5001
#define PACKET_SIZE 1024

bool G_NetworkRunning = false;
bool G_ProgramRunning = true;

HANDLE HandleSend = nullptr;
HANDLE HandleRecv = nullptr;
HANDLE HandleSendQ = nullptr;

queue<string> SendQueue;
CRITICAL_SECTION CS_SendQueue;

unsigned OnRecvMessage(void* args)
{
    SOCKET* SocketClient = (SOCKET*)args;
    char Buffer[PACKET_SIZE] = { 0, };
    int RecvBytes = 0;
    while (G_ProgramRunning)
    {
        if (!G_NetworkRunning) { WaitForSingleObject(HandleRecv, 1); continue; }
        memset(Buffer, 0, sizeof(Buffer));
        //In Order to Make Buffer Null Terminated String, Minus 1
        RecvBytes = recv(*SocketClient, Buffer, sizeof(Buffer) - 1, 0);
        if (RecvBytes <= 0 && G_NetworkRunning)
        {
            cout << "Server Disconnected!" << endl;
            G_NetworkRunning = false;
            continue;
        }
        cout << "[Server] : " << Buffer << endl;
    }

    return 0;
}

unsigned OnCheckSendQ(void* args)
{
    SOCKET* SocketClient = (SOCKET*)args;
    char Buffer[PACKET_SIZE] = { 0, };
    string Msg = "";
    int SendBytes = 0;

    while (G_ProgramRunning)
    {
        if (!G_NetworkRunning || SendQueue.size() == 0) { WaitForSingleObject(HandleSendQ, 1); continue; }
        EnterCriticalSection(&CS_SendQueue);
        while (!SendQueue.empty())
        {
            Msg = SendQueue.front();
            SendQueue.pop();

            memset(Buffer, 0, sizeof(Buffer));
            memcpy(Buffer, Msg.c_str(), strlen(Msg.c_str()));
            SendBytes = send(*SocketClient, Buffer, (int)strlen(Buffer) + 1, 0);
            if (SendBytes <= 0)
            {
                cout << "Server Disconnected!" << endl;
                G_NetworkRunning = false;
                continue;
            }
        }
        LeaveCriticalSection(&CS_SendQueue);
    }
    return 0;
}

unsigned OnSendMessage(void* args)
{
    string Msg = "";
    while (G_ProgramRunning)
    {
        getline(cin, Msg);
        if (strcmp(Msg.c_str(), "#CLIENT_EXIT") == 0)
        {
            G_ProgramRunning = false;
            break;
        }
        EnterCriticalSection(&CS_SendQueue);
        SendQueue.push(Msg);
        LeaveCriticalSection(&CS_SendQueue);
    }
    return 0;
}

int main(int argc, char* argv[])
{
    InitializeCriticalSection(&CS_SendQueue);
    WSADATA WSAData = { 0, };
    SOCKET SocketClient = NULL;
    SOCKADDR_IN ServerAddress = { 0, };

    int Retval = 0;
    char Buffer[PACKET_SIZE] = { 0, };
    int SendBytes = 0;

    Retval = WSAStartup(MAKEWORD(2, 2), &WSAData);
    if (Retval != 0) { exit(-1); }
    ServerAddress.sin_family = PF_INET;
    ServerAddress.sin_addr.S_un.S_addr = inet_addr(SERVER_IPV4);
    ServerAddress.sin_port = htons(SERVER_PORT);


    HandleSendQ = (HANDLE)_beginthreadex(nullptr, 0, OnCheckSendQ, (void*)&SocketClient, 0, nullptr);
    HandleSend = (HANDLE)_beginthreadex(nullptr, 0, OnSendMessage, nullptr, 0, nullptr);
    HandleRecv = (HANDLE)_beginthreadex(nullptr, 0, OnRecvMessage, (void*)&SocketClient, 0, nullptr);

    while (G_ProgramRunning)
    {
        if (!G_NetworkRunning)
        {
            if (SocketClient) { closesocket(SocketClient); SocketClient = NULL; }
            SocketClient = socket(AF_INET, SOCK_STREAM, 0);
            if (SocketClient == INVALID_SOCKET) { continue; }
            Retval = connect(SocketClient, (SOCKADDR*)&ServerAddress, sizeof(ServerAddress));
            if (Retval == SOCKET_ERROR) { continue; }
            system("cls");
            cout << "Server Connected!" << endl;
            WaitForSingleObject(HandleSendQ, 5);
            EnterCriticalSection(&CS_SendQueue);
            while (!SendQueue.empty()) { SendQueue.pop(); };
            SendQueue.push("#CLIENT_GETALL_LIST");
            LeaveCriticalSection(&CS_SendQueue);
            G_NetworkRunning = true;
            continue;
        }
        Sleep(1);
    }

    if (SocketClient) { closesocket(SocketClient); }
    if (HandleSend) { WaitForSingleObject(HandleSend, INFINITE); CloseHandle(HandleSend); }
    if (HandleRecv) { WaitForSingleObject(HandleRecv, INFINITE); CloseHandle(HandleRecv); }
    if (HandleSendQ) { WaitForSingleObject(HandleSendQ, INFINITE); CloseHandle(HandleSendQ); }
    DeleteCriticalSection(&CS_SendQueue);
    WSACleanup();
    return 0;
}
