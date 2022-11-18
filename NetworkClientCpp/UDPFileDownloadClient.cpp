#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "WS2_32.lib") //WinSock2.DLL Load

#define SERVER_IPV4 "127.0.0.1"
#define SERVER_PORT 1234
#define PACKET_SIZE 1024

#include <string>
#include <iostream>
#include <WinSock2.h>
#include <thread>
#include <io.h>
#include <stdio.h>

using namespace std;

int UDPFileDownloadClient_main(int argc, char* argv[])
{
    WSADATA WSAData;
    SOCKET UDPSocket = NULL;
    SOCKADDR_IN ServerAddress;
    SOCKADDR_IN RemoteAddress;
    int szRemoteAddress = (int)sizeof(RemoteAddress);
    int Retval = 0;
    

    memset(&WSAData, 0, sizeof(WSAData));
    memset(&ServerAddress, 0, sizeof(ServerAddress));

    Retval = WSAStartup(MAKEWORD(2, 2), &WSAData);
    if (Retval != 0)
    {
        cout << "[ERR]Winsock 2.2 Load Failed. ErrorCode : " << GetLastError() << endl;
        exit(-1);
    }

    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_port = htons(SERVER_PORT);
    ServerAddress.sin_addr.S_un.S_addr = inet_addr(SERVER_IPV4);

    bool bCalledOnce = false;
    while (true)
    {
        int RecvBytes = 0;
        int SendBytes = 0;
        char Buffer[PACKET_SIZE] = { 0, };

        if (UDPSocket != NULL) { closesocket(UDPSocket); UDPSocket = NULL; }
        UDPSocket = socket(AF_INET, SOCK_DGRAM, 0/*IPPROTO_UDP*/);
        if (UDPSocket == INVALID_SOCKET)
        {
            cout << "[ERR]UDPSocket Creation Failed. ErrorCode : " << GetLastError() << endl;
            continue;
        }
        strcpy(Buffer, "FILE_REQ");
        SendBytes = sendto(UDPSocket, Buffer, strlen(Buffer), 0, (sockaddr*)&ServerAddress, sizeof(ServerAddress));

        memset(Buffer, 0, sizeof(Buffer));
        RecvBytes = recvfrom(UDPSocket, Buffer, sizeof(Buffer), 0, (sockaddr*)&RemoteAddress, &szRemoteAddress);

        if (!bCalledOnce)
        {
            cout << "[SYS]FileName Requesting...";
            bCalledOnce = true;
        }

        if (RecvBytes > 0)
        {
            cout << "OK." << endl;
            char fileName[PACKET_SIZE] = { 0, };
            strcpy(fileName, Buffer);

            cout << "[SYS]Download FileName : " << Buffer << endl;
            memset(Buffer, 0, sizeof(Buffer));
            if (_access(fileName, 0/*F_OK*/) == 0)
            {
                //File Exists 
                strcpy(Buffer, "FILE_EXIST");
                SendBytes = sendto(UDPSocket, Buffer, strlen(Buffer), 0, (sockaddr*)&ServerAddress, sizeof(ServerAddress));
                cout << "[SYS]File Already Exists." << endl;
                break;
            }
            else
            {
                //File Not Exists
                strcpy(Buffer, "FILE_NOT_EXIST");
                SendBytes = sendto(UDPSocket, Buffer, strlen(Buffer), 0, (sockaddr*)&ServerAddress, sizeof(ServerAddress));

                FILE* fp = fopen(fileName, "wb");
                int FileSize = 0;
                int totalSize = 0;
                while(true)
                {
                    memset(Buffer, 0, sizeof(Buffer));

                    //RecvFrom은 ServerSocket이 Closed되도 return 0 또는 SOCKET_ERROR를 반환하지 않는다!!!
                    //SendTo에서 Size : 0만큼 보내서 끝낼수도 있는데, 
                    RecvBytes = recvfrom(UDPSocket, Buffer, sizeof(Buffer), 0, (sockaddr*)&RemoteAddress, &szRemoteAddress);

                    if (strcmp(Buffer, "EOF") == 0)
                    {
                        break;
                    }
                    FileSize = fwrite(Buffer, 1, RecvBytes, fp);
                    totalSize += FileSize;
                } 
                fclose(fp);
                cout << "[SYS] FileDownload Complete." << endl;
                break;
            }
        }
    }
    if (UDPSocket != NULL) { closesocket(UDPSocket); UDPSocket = NULL; }
    WSACleanup();
    return 0;
}
