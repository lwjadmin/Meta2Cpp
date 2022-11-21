#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <string>
#include <iostream>

using namespace std;

#pragma comment(lib, "WS2_32.lib") 

#define SERVER_IPV4 "127.0.0.1"
#define SERVER_PORT 5001
#define PACKET_SIZE 1024

int main(int argc, char* argv[])
{
    WSADATA WSAData = { 0, };
    SOCKET SocketClient = NULL;
    SOCKADDR_IN ServerAddress = { 0, };
    string Message = "";
    int Retval = 0;
    char Buffer[PACKET_SIZE] = { 0, };
    int SendBytes = 0;
    int RecvBytes = 0;
    bool bProgramRunning = true;

    Retval = WSAStartup(MAKEWORD(2, 2), &WSAData);
    if (Retval != 0) { exit(-1); }
    ServerAddress.sin_family = PF_INET;
    ServerAddress.sin_addr.S_un.S_addr = inet_addr(SERVER_IPV4);
    ServerAddress.sin_port = htons(SERVER_PORT);

    while (bProgramRunning)
    {
        cout << "SocketClient Connecting..." << endl;
        if (SocketClient != NULL)
        {
            closesocket(SocketClient);
            SocketClient = NULL;
        }
        SocketClient = socket(AF_INET, SOCK_STREAM, 0);
        if (SocketClient == INVALID_SOCKET)
        {
            continue;
        }
        Retval = connect(SocketClient, (SOCKADDR*)&ServerAddress, sizeof(ServerAddress));
        if (Retval == SOCKET_ERROR)
        {
            continue;
        }
        cout << "SocketClient Connected!" << endl;
        while (true)
        {
            cout << "Client->Server INSERT Message : ";
            getline(cin, Message);
            memset(Buffer, 0, sizeof(Buffer));
            memcpy(Buffer, Message.c_str(), strlen(Message.c_str()));
            if (strcmp(Buffer, "exitclient") ==0)
            {
                bProgramRunning = false;
                break;
            }
            //In Order to Send Buffer Null Terminated String, Plus 1
            SendBytes = send(SocketClient, Buffer, (int)strlen(Buffer) + 1, 0);
            if (SendBytes <= 0) { break; }
            cout << "Client->Server SEND Message : " << Buffer << endl;
            memset(Buffer, 0, sizeof(Buffer));
            //In Order to Make Buffer Null Terminated String, Minus 1
            RecvBytes = recv(SocketClient, Buffer, sizeof(Buffer)-1, 0); 
            if (RecvBytes <= 0) { break; }
            cout << "Server->Client RECV Message : " << Buffer << endl;
        }
    }
    if (SocketClient) { closesocket(SocketClient); }
    WSACleanup();
    return 0;
}
