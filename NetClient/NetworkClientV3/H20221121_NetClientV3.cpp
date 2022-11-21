#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <process.h>

#include <string>
#include <iostream>

using namespace std;

#pragma comment(lib, "WS2_32.lib") 

#define SERVER_IPV4 "127.0.0.1"
#define SERVER_PORT 5001
#define PACKET_SIZE 1024

bool G_NetworkRunning = false;
bool G_ProgramRunning = true;

HANDLE HandleRecv = nullptr;
HANDLE HandleSend = nullptr;

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

unsigned OnSendMessage(void* args)
{
    SOCKET* SocketClient = (SOCKET*)args;
    string Message = "";
    char Buffer[PACKET_SIZE] = { 0, };
    int SendBytes = 0;
    while (G_ProgramRunning)
    {
        if (!G_NetworkRunning) { WaitForSingleObject(HandleRecv, 1); continue; }
        getline(cin, Message);
        memset(Buffer, 0, sizeof(Buffer));
        memcpy(Buffer, Message.c_str(), strlen(Message.c_str()));
        if (strcmp(Buffer, "exitclient") == 0)
        {
            G_ProgramRunning = false;
            break;
        }
        if (G_NetworkRunning)
        {
            //In Order to Send Buffer Null Terminated String, Plus 1
            SendBytes = send(*SocketClient, Buffer, (int)strlen(Buffer) + 1, 0);
            if (SendBytes <= 0)
            {
                cout << "Server Disconnected!" << endl;
                G_NetworkRunning = false;
                continue;
            }
            cout << "[Client] : " << Buffer << endl;
        }
    }
    return 0;
}

int main(int argc, char* argv[])
{
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

    HandleSend = (HANDLE)_beginthreadex(nullptr, 0, OnSendMessage, (void*)&SocketClient, 0, nullptr);
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
            cout << "Server Connected!" << endl;
            G_NetworkRunning = true;
            continue;
        }
        Sleep(1);
    }

    if (SocketClient) { closesocket(SocketClient); }
    if (HandleRecv) { WaitForSingleObject(HandleRecv, INFINITE); CloseHandle(HandleRecv); }
    if (HandleSend) { WaitForSingleObject(HandleSend, INFINITE); CloseHandle(HandleSend); }
    WSACleanup();
    return 0;
}
