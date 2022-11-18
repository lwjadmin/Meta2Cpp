#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#include <string>

using namespace std;

#pragma comment(lib, "WS2_32.lib") //DLL Load

#define SERVER_IPV4 "0.0.0.0"
#define SERVER_PORT 19934
#define PACKET_SIZE 1024

int TCPServer_main(int argc, char* argv[])
{
    bool bExitCalled = false;
    bool bConnectionSuccess = false;

    WSADATA WSAData = { 0, };
    SOCKET ServerSocket = NULL;
    SOCKET ClientSocket = NULL;
    SOCKADDR_IN ServerAddress = { 0, };
    SOCKADDR_IN ClientAddress = { 0, };

    char Buffer[PACKET_SIZE] = { 0, };
    string Message = "";
    int Result = 0;

    //--Init WinSock 2.2------------------------------------------------------
    Result = WSAStartup(MAKEWORD(2, 2), &WSAData);
    if (Result != 0)
    {
        cout << "[ERR]Winsock Init Error : " << GetLastError() << endl;
        exit(-1);
    }
    //--Set ServerAddress-----------------------------------------------------
    ServerAddress.sin_family = PF_INET;
    ServerAddress.sin_addr.S_un.S_addr = inet_addr(SERVER_IPV4)/*htonl(INADDR_ANY)*/;
    ServerAddress.sin_port = htons(SERVER_PORT);
    //--Set ServerSocket-------------------------------------------------------
    ServerSocket = socket(AF_INET, SOCK_STREAM /*SOCK_DGRAM*/, 0);
    if (ServerSocket == INVALID_SOCKET)
    {
        cout << "[ERR]ServerSocket Creation Error : " << GetLastError() << endl;
        exit(-1);
    }
    //--Bind ServerSocket & Address---------------------------------------------
    Result = bind(ServerSocket, (SOCKADDR*)&ServerAddress, sizeof(ServerAddress));
    if (Result == SOCKET_ERROR)
    {
        cout << "[ERR]ServerSocket Bind Error : " << GetLastError() << endl;
        exit(-1);
    }
    //--ServerSocket Listen------------------------------------------------------
    Result = listen(ServerSocket, 0);
    if (Result == SOCKET_ERROR)
    {
        cout << "[ERR]ServerSocket Listen Error : " << GetLastError() << endl;
        exit(-1);
    }

    while (true)
    {
        //--Wait for Client Connection-----------------------------------------------
        if (!bConnectionSuccess)
        {
            cout << "[SYS]Waiting For Any TCP Connections(Blocking)...";
            int szClientAddress = sizeof(ClientAddress);
            if (ClientSocket) { closesocket(ClientSocket); ClientSocket = NULL; }
            ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientAddress, &szClientAddress);
            if (ClientSocket == INVALID_SOCKET)
            {
                cout << "\n[ERR]ClientSocket Accept Error : " << GetLastError() << endl;
                continue;
            }
            else
            {
                cout << "OK\n[SYS]ClientSocket Connection Success!" << endl;
                bConnectionSuccess = true;
            }
        }
        //--RECV---------------------------------------------------------------------
        cout << "[SYS]Waiting For Message...";
        memset(Buffer, 0, PACKET_SIZE);
        int RecvBytes = recv(ClientSocket, Buffer, sizeof(Buffer), 0);
        if (RecvBytes <= 0)
        {
            cout << "\n[ERR]ClientSocket Recv Error : " << GetLastError() << endl;
            bConnectionSuccess = false;
            continue;
        }
        cout << "OK\n[SYS]Server Received Message : " << Buffer << endl;
        if (Buffer[0] == 'E' && Buffer[1] == 'X' && Buffer[2] == 'I' && Buffer[3] == 'T')
        {
            break;
        }
        //--SEND---------------------------------------------------------------------
        memset(Buffer, 0, PACKET_SIZE);
        cout << "[SYS]Insert Message : ";
        getline(cin, Message);
        memcpy(Buffer, Message.c_str(), Message.length());
        int SendBytes = send(ClientSocket, Buffer, PACKET_SIZE, 0);
        if (SendBytes <= 0)
        {
            cout << "[ERR]ClientSocket Send Error : " << GetLastError() << endl;
            continue;
        }
        else
        {
            cout << "[SYS]Server Send Message : " << Message << endl;
        }
    }
    if (ClientSocket) { closesocket(ClientSocket); ClientSocket = NULL; }
    if (ServerSocket) { closesocket(ServerSocket); ServerSocket = NULL; }
    WSACleanup();
    return 0;
}