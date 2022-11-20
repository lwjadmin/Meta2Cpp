#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <process.h>
#include <Windows.h>
#include <timeapi.h>

#include <iostream>
#include <vector>

#pragma comment(lib,"WS2_32.lib")

using namespace std;

vector<SOCKET> GUserList;
CRITICAL_SECTION GServerCS;

unsigned WINAPI WorkerThread(void* Arg)
{
    SOCKET socket = *(SOCKET*)Arg;
    while (true)
    {
        char Buffer[1024] = { 0, };
        int recvBytes = recv(socket, Buffer, sizeof(Buffer), 0);
        if (recvBytes <= 0)
        {
            break;
        }
        else
        {
            cout << "RECV : " << Buffer << endl;
            for (int i = 0; i < GUserList.size(); i++)
            {
                int sendBytes = send(GUserList[i], Buffer, (int)strlen(Buffer), 0);
                if (sendBytes <= 0)
                {
                    break;
                }
            }
        }
    }
    cout << "Client DisConnected!" << endl;
    closesocket(socket);
    EnterCriticalSection(&GServerCS);
    GUserList.erase(find(GUserList.begin(), GUserList.end(), socket));
    LeaveCriticalSection(&GServerCS);
    return 0;
}


int L20221118_TCPMultiThreadServer_main(int argc, char* argv[])
//int main(int argc, char* argv[])
{
    InitializeCriticalSection(&GServerCS);
    WSAData wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);

    SOCKET TCPServerSocket = socket(AF_INET, SOCK_STREAM, 0/*IPPROTO_TCP*/);
    SOCKADDR_IN TCPServerAddress;
    TCPServerAddress.sin_family = AF_INET;
    TCPServerAddress.sin_addr.S_un.S_addr = INADDR_ANY; /*inet_addr("127.0.0.1");*/
    TCPServerAddress.sin_port = htons(4949);
    
    bind(TCPServerSocket, (sockaddr*)&TCPServerAddress, sizeof(TCPServerAddress));
    listen(TCPServerSocket, SOMAXCONN);

    while (true)
    {
        SOCKADDR_IN TCPClientAddress;
        int szTCPClientAddress = sizeof(TCPClientAddress);
        SOCKET TCPClientSocket = accept(TCPServerSocket, (sockaddr*)&TCPClientAddress, &szTCPClientAddress);
        EnterCriticalSection(&GServerCS);
        GUserList.push_back(TCPClientSocket);
        LeaveCriticalSection(&GServerCS);
        HANDLE ThreadHandle = (HANDLE)_beginthreadex(nullptr, 0, WorkerThread, (void*)&TCPClientSocket, 0, nullptr);
        cout << "New Client Connected!" << endl;
    }
    closesocket(TCPServerSocket);
    WSACleanup();
    DeleteCriticalSection(&GServerCS);
    return 0;
}