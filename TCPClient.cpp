#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#include <string>

using namespace std;

#pragma comment(lib, "WS2_32.lib") //DLL Load

#define SERVER_IPV4 "127.0.0.1"
#define SERVER_PORT 19934
#define PACKET_SIZE 1024

int TCPClient_main(int argc, char* argv[])
{
    bool bExitCalled = false;
    bool bConnectionSuccess = false;
    WSADATA WSAData = { 0, };
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
    //--Set ServerAddress  Init------------------------------------------------------
    ServerAddress.sin_family = PF_INET;
    ServerAddress.sin_addr.S_un.S_addr = inet_addr(SERVER_IPV4);
    ServerAddress.sin_port = htons(SERVER_PORT);

    while (true)
    {
        //--Wait for Server Connection-----------------------------------------------
        if (!bConnectionSuccess)
        {
            cout << "[SYS]Connecting...";
            if (ClientSocket) { closesocket(ClientSocket); ClientSocket = NULL; }
            ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (ClientSocket == INVALID_SOCKET)
            {
                cout << "ClientSocket Creation Error : " << GetLastError() << endl;
                continue;
            }
            Result = connect(ClientSocket, (SOCKADDR*)&ServerAddress, sizeof(ServerAddress));
            if (Result == SOCKET_ERROR)
            {
                cout << "ClientSocket Connection Failed : " << GetLastError() << endl;
                continue;
            }
            else
            {
                cout << "ClientSocket Connection Success!" << endl;
                bConnectionSuccess = true;
            }
        }
#pragma region --EXAM_01---------------------------------------------------------------
        /*
        //--SEND---------------------------------------------------------------------
        memset(Buffer, 0, PACKET_SIZE);
        cout << "[SYS]Insert Message : ";
        getline(cin, Message);
        memcpy(Buffer, Message.c_str(), Message.size());
        int SendBytes = send(ClientSocket, Buffer, PACKET_SIZE, 0);
        if (SendBytes <= 0)
        {
            cout << "[ERR]ClientSocket Send Error : " << GetLastError() << endl;
            bConnectionSuccess = false;
            continue;
        }
        else
        {
            cout << "[SYS]Client Send Message : " << Message << endl;
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
        cout << "OK\n[SYS]Client Received Message : " << Buffer << endl;
        if (Buffer[0] == 'E' && Buffer[1] == 'X' && Buffer[2] == 'I' && Buffer[3] == 'T')
        {
            break;
        }
        */
#pragma  endregion
#pragma  region --EXAM_02---------------------------------------------------
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
        cout << "OK\n[SYS]Client Received Message : " << Buffer << endl;
        if (Buffer[0] == 'E' && Buffer[1] == 'X' && Buffer[2] == 'I' && Buffer[3] == 'T')
        {
            break;
        }
#pragma  endregion
    }
    if (ClientSocket) { closesocket(ClientSocket); ClientSocket = NULL; }
    WSACleanup();
    return 0;
}