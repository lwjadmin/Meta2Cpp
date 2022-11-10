#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "WS2_32.lib") //WinSock2.DLL Load

#define SERVER_IPV4 "0.0.0.0" /*"127.0.0.1"*/
#define SERVER_PORT 1234
#define PACKET_SIZE 1024

#include <string>
#include <iostream>
#include <WinSock2.h>

using namespace std;

int L20221108_UDPServer_main(int argc, char* argv[])
//int main(int argc, char* argv[])
{
    bool bExitCalled = false;
    WSADATA WSAData = { 0, };
    SOCKET ServerSocket = NULL;
    SOCKADDR_IN ServerSocketAddress = { 0, };
    int Result = 0;

    //--Init WinSock 2.2------------------------------------------------------
    //扩家南 2.2 檬扁拳
    Result = WSAStartup(MAKEWORD(2, 2), &WSAData);
    if (Result != 0)
    {
        cout << "[ERR]WinSock2.2 Init Error! ErrorCode : " << GetLastError() << endl;
        exit(-1);
    }
    //--Set ServerAddress & ServerSocket---------------------------------------
    //家南 积己
    ServerSocketAddress.sin_family = PF_INET/*AF_INET*/;
    ServerSocketAddress.sin_addr.S_un.S_addr = inet_addr(SERVER_IPV4);
    ServerSocketAddress.sin_port = htons(SERVER_PORT);
    ServerSocket = socket(AF_INET, SOCK_DGRAM, 0/*IPPROTO_UDP*/);
    if (ServerSocket == INVALID_SOCKET)
    {
        cout << "[ERR]ServerSocket Creation Error! ErrorCode : " << GetLastError() << endl;
        exit(-2);
    }
    //--Bind ServerSocket & Address---------------------------------------------
    //家南俊 IP林家, 器飘 官牢爹
    Result = bind(ServerSocket, (SOCKADDR*)&ServerSocketAddress, sizeof(ServerSocketAddress));
    if (Result == SOCKET_ERROR)
    {
        cout << "[ERR]ServerSocket Bind Error! ErrorCode : " << GetLastError() << endl;
        exit(-3);
    }
    do
    {
        cout << "[ERR]UDPClient Listening...";
        int SendBytes = 0;
        int RecvBytes = 0;
        SOCKADDR_IN ClientSocketAddress = { 0, };
        int szClientSocketAddress = sizeof(ClientSocketAddress);
        char buffer[PACKET_SIZE] = { 0, };
        //--RECV----------------------------------------------------------------------------------
        RecvBytes = recvfrom(ServerSocket, buffer, sizeof(buffer), 0, (sockaddr*)&ClientSocketAddress, &szClientSocketAddress);
        if (RecvBytes == 0)
        {
            std::cout << "UDPClient Connection Closed." << std::endl;
        }
        else if (RecvBytes == SOCKET_ERROR)
        {
            std::cout << "UDPServer Socket Error! ErrorCode : " << GetLastError() << endl;
        }
        else
        {
            cout << "OK.\n[SYS]UDPServer RECV Message : " << buffer << endl;
            //--SEND----------------------------------------------------------------------------------
            SendBytes = sendto(ServerSocket, buffer, RecvBytes, 0, (sockaddr*)&ClientSocketAddress, szClientSocketAddress);
            if (SendBytes == 0)
            {
                std::cout << "UDPClient Connection Closed." << std::endl;
            }
            else if (SendBytes == SOCKET_ERROR)
            {
                std::cout << "UDPServer Socket Error! ErrorCode : " << GetLastError() << endl;
            }
            else
            {
                cout << "[SYS]UDPServer SEND Message : " << buffer << endl;
            }
        }
    } while (!bExitCalled);
    if (ServerSocket) { closesocket(ServerSocket); ServerSocket = NULL; }
    WSACleanup();
    return 0;
}
