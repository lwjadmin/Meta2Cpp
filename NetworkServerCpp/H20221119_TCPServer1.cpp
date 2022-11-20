/*---------------------------------------------------------------
    TCP Echo Server
    -- TCP클라이언트가 NTS(Null Terminated String)를 보내면, 서버에서 받아서 그대로 되돌려준다.
---------------------------------------------------------------*/

#define _WINSOCK_DEPRECATED_NO_WARNINGS

//CHeader
#include <WinSock2.h>
//CppHeader
#include <iostream>
//CustomHeader

//Library
#pragma comment(lib, "WS2_32.lib")

//define
#define SERVER_IPV4 "127.0.0.1"
#define SERVER_PORT 4949
#define PACKET_SIZE 1024

using namespace std;

int H20221119_TCPServer1_main(int argc, char* argv[])
{
    WSAData wsadata = { 0, };
    SOCKET TCPServerSocket = NULL;
    SOCKADDR_IN TCPServerAddress = { 0, };
    int Retval = 0;

    //1. Load Winsock2.2
    Retval = WSAStartup(MAKEWORD(2, 2), &wsadata);
    if (Retval != 0)
    {
        cout << "[ERR]Winsock2.2 Load Failed. ErrorCode : " << GetLastError() << endl;
        exit(-1);
    }
    cout << "[SYS]Winsock2.2 Load Success!" << endl;

    //2. Create TCPServerSocket
    TCPServerAddress.sin_family = AF_INET;
    //inet_addr : add define _WINSOCK_DEPRECATED_NO_WARNINGS
    TCPServerAddress.sin_addr.S_un.S_addr = inet_addr(SERVER_IPV4); 
    TCPServerAddress.sin_port = htons(SERVER_PORT);

    TCPServerSocket = socket(AF_INET, SOCK_STREAM, 0/*IPPROTO_TCP*/);
    if (TCPServerSocket == INVALID_SOCKET)
    {
        cout << "[ERR]TCPSocket Creation Failed! ErrorCode : " << GetLastError() << endl;
        exit(-2);
    }
    cout << "[SYS]TCPSocket Creation Complete!" << endl;

    //3. Bind TCPServerSocket to Address
    Retval = bind(TCPServerSocket, (sockaddr*)&TCPServerAddress, sizeof(TCPServerAddress));
    if (Retval != 0)
    {
        cout << "[ERR]TCPSocket Address Bind Failed! ErrorCode : " << GetLastError() << endl;
        exit(-3);
    }
    cout << "[SYS]TCPSocket Address Bind Complete!" << endl;

    //4. Set TCPServerSocket Listen State
    Retval = listen(TCPServerSocket, SOMAXCONN);
    if (Retval != 0)
    {
        cout << "[ERR]TCPSocket Listen Failed! ErrorCode : " << GetLastError() << endl;
        exit(-4);
    }
    cout << "[SYS]TCPSocket Listening..." << endl;
    //Blocking Accept Socket
    SOCKADDR_IN TCPClientAddress = { 0, };
    int szTCPClientAddress = sizeof(TCPClientAddress);
    SOCKET TCPClientSocket = accept(TCPServerSocket, (sockaddr*)&TCPClientAddress, &szTCPClientAddress);
    if (TCPClientSocket == INVALID_SOCKET)
    {
        cout << "[ERR]TCPClientSocket Creation Failed! ErrorCode : " << GetLastError() << endl;
        exit(-5);
    }
    cout << "[Network Start]" << endl;

    while (true)
    {
        int SendBytes = 0;
        int RecvBytes = 0;
        char Buffer[PACKET_SIZE] = { 0, };
        RecvBytes = recv(TCPClientSocket, Buffer, sizeof(Buffer), 0);
        if (RecvBytes == 0)
        {
            cout << "[ERR]TCPClientSocket Connection Closed" << endl;
            break;
        }
        else if (RecvBytes < 0)
        {
            cout << "[ERR]TCPClientSocket Error Occured! ErrorCode : " << GetLastError() << endl;
            break;
        }
        cout << "[SYS]RECV Message : " << Buffer << endl;
        //In Order to Make NTS(Null Terminated String), Add + 1 ('\0')
        SendBytes = send(TCPClientSocket, Buffer, (int)strlen(Buffer) + 1, 0);
        if (SendBytes == 0)
        {
            cout << "[ERR]TCPClientSocket Connection Closed" << endl;
            break;
        }
        else if (SendBytes < 0)
        {
            cout << "[ERR]TCPClientSocket Error Occured! ErrorCode : " << GetLastError() << endl;
            break;
        }
    }
    cout << "[Network Finish]" << endl;
    if(TCPClientSocket != NULL){ closesocket(TCPClientSocket); }
    if (TCPServerSocket != NULL) { closesocket(TCPServerSocket); }
    return 0;
}
