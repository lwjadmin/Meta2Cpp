#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "WS2_32.lib") //WinSock2.DLL Load

#define SERVER_IPV4 "127.0.0.1" 
#define SERVER_PORT 1234
#define PACKET_SIZE 1024

#include <string>
#include <iostream>
#include <WinSock2.h>

using namespace std;

//int main(int argc, char* argv[])
int UDPFileTransferServer_main(int argc, char* argv[])
{
    WSADATA WSAData = { 0, };
    SOCKET UDPSocket = NULL;
    SOCKADDR_IN ServerAddress = { 0, };
    int Retval = 0;

    Retval = WSAStartup(MAKEWORD(2, 2), &WSAData);
    if (Retval != 0)
    {
        cout << "[ERR]Winsock 2.2 Load Failed. ErrorCode : " << GetLastError() << endl;
        exit(-1);
    }

    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_addr.S_un.S_addr = inet_addr(SERVER_IPV4);
    ServerAddress.sin_port = htons(SERVER_PORT);

    while (true)
    {
        if (UDPSocket) { closesocket(UDPSocket); }
        UDPSocket = socket(AF_INET, SOCK_DGRAM, 0/*IPPROTO_UDP*/);
        if (UDPSocket == INVALID_SOCKET)
        {
            cout << "[ERR]UDPSocket Creation Failed. ErrorCode : " << GetLastError() << endl;
            continue;
        }
        Retval = bind(UDPSocket, (SOCKADDR*)&ServerAddress, sizeof(ServerAddress));
        if (Retval == SOCKET_ERROR)
        {
            cout << "[ERR]UDPSocket Bind Error Occured. ErrorCode : " << GetLastError() << endl;
            continue;
        }
        int SendBytes = 0;
        int RecvBytes = 0;
        SOCKADDR_IN ClientSocketAddress = { 0, };
        int szClientSocketAddress = sizeof(ClientSocketAddress);
        char Buffer[PACKET_SIZE] = { 0, };
        const char* FileName = "download.jpg";
        cout << "[SYS]UDPSocket RECV Waiting...";
        RecvBytes = recvfrom(UDPSocket, Buffer, sizeof(Buffer), 0, (sockaddr*)&ClientSocketAddress, &szClientSocketAddress);
        if (RecvBytes <= 0)
        {
            cout << "Failed.[SYS]UDPClient Connection Closed." << endl;
            continue;
        }
        cout << "OK" << endl;
        if (strcmp(Buffer, "FILE_REQ") == 0)
        {
            cout << "[SYS]Recv Message : " << Buffer << endl;
            memset(Buffer, 0, sizeof(Buffer));
            strcpy(Buffer, FileName);
            SendBytes = sendto(UDPSocket, Buffer, (int)strlen(Buffer), 0, (sockaddr*)&ClientSocketAddress, sizeof(ClientSocketAddress));

            cout << "[SYS]Send Message FileName : " << Buffer << endl;
            memset(Buffer, 0, sizeof(Buffer));
            RecvBytes = recvfrom(UDPSocket, Buffer, sizeof(Buffer), 0, (sockaddr*)&ClientSocketAddress, &szClientSocketAddress);

            if (strcmp(Buffer, "FILE_NOT_EXIST") == 0)
            {
                cout << "[SYS]Recv Message : " << Buffer << endl;
                FILE* fp = fopen(FileName, "rb");
                int FReadBytes = 0;
                while (!feof(fp))
                {
                    //Send Message Body : File
                    FReadBytes = fread(Buffer, sizeof(char), sizeof(Buffer), fp);
                    SendBytes = sendto(UDPSocket, Buffer, FReadBytes, 0, (sockaddr*)&ClientSocketAddress, sizeof(ClientSocketAddress));
                }
                char EndOfFile[4] = { 'E','O','F','\0' };
                SendBytes = sendto(UDPSocket, EndOfFile, 4, 0, (sockaddr*)&ClientSocketAddress, sizeof(ClientSocketAddress));
                fclose(fp);
                cout << "[SYS] File Transfer Completed!" << endl;
                break;
            }
            else if(strcmp(Buffer, "FILE_EXIST") == 0)
            {
                cout << "[SYS]Recv Message : " << Buffer << endl;
                break;
            }
        }
    }//eowhile
    cout << "[SYS]UDPServer Closed." << endl;
    if (UDPSocket != NULL) { closesocket(UDPSocket); UDPSocket = NULL; }
    WSACleanup();
    return 0;
}
