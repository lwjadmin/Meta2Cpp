#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <process.h>
#include <Windows.h>
#include <timeapi.h>

#include <iostream>
#include <vector>

#pragma comment(lib,"WS2_32.lib")

#define SERVER_IPV4 "127.0.0.1"
#define SERVER_PORT 4949
#define PACKET_SIZE 1024

using namespace std;

vector<SOCKET> vSocketList;
vector<HANDLE> vHandleList;

CRITICAL_SECTION CSThread;

unsigned WINAPI WorkThread(void* args)
{
    SOCKET TCPClientSocket = *(SOCKET*)args;

    while (true)
    {
        char Buffer[PACKET_SIZE] = { 0, };
        int RecvBytes = recv(TCPClientSocket, Buffer, sizeof(Buffer), 0);
        if (RecvBytes < 0)
        {
            break;
        }
        cout << "[Server] RECV Message : " << Buffer << endl;

        for (int i = 0; i < vSocketList.size(); i++)
        {
            if (vSocketList[i] == TCPClientSocket) { continue; }
            int SendBytes = send(vSocketList[i], Buffer, strlen(Buffer), 0);
            if (SendBytes < 0)
            {
                break;
            }
        }
    }
    if (TCPClientSocket) { closesocket(TCPClientSocket); }
    cout << "[SYS]TCPClient Disconnected." << endl;
    /*-------------------------------------------------------------------------
    MultiThread ȯ�濡�� WorkThread �Լ� ���۽� Heap�� ����Ǵ� vSocketList�� 
    Thread-safe���� �ʱ� ������ �浹�� ���α׷��� �������� �ִ�. 
    ����, vSocketList �����Ͽ� 1Element �����ϴ� ������ Critical Section���� ���Ѵ�.
    -------------------------------------------------------------------------*/
    EnterCriticalSection(&CSThread);
    for (int i = 0; i < vSocketList.size(); i++)
    {
        if (vSocketList[i] == TCPClientSocket)
        {
            vSocketList.erase(vSocketList.begin() + i);
            break;
        }
    }
    LeaveCriticalSection(&CSThread);
    return 0;
}

int L20221118_TCPMultiplexingServer_main2(int argc, char* argv[])
//int main(int argc, char* argv[])
{
    InitializeCriticalSection(&CSThread);
    WSAData wsadata = { 0, };
    SOCKET TCPServerSocket = NULL;
    SOCKADDR_IN TCPServerAddress = { 0, };
    int Retval = 0;
    //1.Load Winsock2.2
    Retval = WSAStartup(MAKEWORD(2, 2), &wsadata);
    if (Retval != 0)
    {
        cout << "[ERR]Winsock 2.2 Load Failed. ErrorCode : " << GetLastError() << endl;
        exit(-1);
    }
    cout << "[SYS]Winsock 2.2 Load Complete!" << endl;
    TCPServerAddress.sin_family = AF_INET;
    TCPServerAddress.sin_addr.S_un.S_addr = inet_addr(SERVER_IPV4);
    TCPServerAddress.sin_port = htons(SERVER_PORT);
    //2.Create TCPServerSocket
    TCPServerSocket = socket(AF_INET, SOCK_STREAM, 0/*IPPROTO_TCP*/);
    if (TCPServerSocket == INVALID_SOCKET)
    {
        cout << "[ERR]TCPSocket Creation Failed! ErrorCode : " << GetLastError() << endl;
        exit(-2);
    }
    cout << "[SYS]TCPSocket Creation Complete!" << endl;
    //3.Bind TCPServerSocket to Address 
    Retval = bind(TCPServerSocket, (sockaddr*)&TCPServerAddress, sizeof(TCPServerAddress));
    if (Retval != 0)
    {
        cout << "[ERR]TCPSocket Address Bind Failed! ErrorCode : " << GetLastError() << endl;
        exit(-3);
    }
    cout << "[SYS]TCPSocket Address Bind Complete!" << endl;
    //4.Set TCPServerSocket Listening...
    Retval = listen(TCPServerSocket, SOMAXCONN);
    if (Retval != 0)
    {
        cout << "[ERR]TCPSocket Listen Failed! ErrorCode : " << GetLastError() << endl;
        exit(-4);
    }
    cout << "[SYS]TCPSocket Listening..." << endl;

    /*------------------------------------------------------------------
    �� ������ �����ڰ� �����Ҽ��� ������ �����尡 �����ϱ� ������ �����ϴ�. 
    �����ڰ� �α׾ƿ��� �� ��� �����带 ���̴� ������ �߰��ؾ� �ϰ�, 
    �����尡 ���ѵǾ� ���ɼ� �ֵ��� ���ѵ� ������ ������ �����, �� �����忡��
    Socket Select�� �Ҽ� �ֵ��� �����ϴ� ���� ���� �������̴�!

    �����Ͱ� ������ ť�� �ִ� �����带 �ϳ� �����,
    ť�� �ϳ� ���� �����͸� ó���ϴ� �����带 �ϳ� ����� ���� ����. 
    ------------------------------------------------------------------*/
    while (true)
    {
        SOCKADDR_IN TCPClientAddress = { 0, };
        int szTCPClientAddress = sizeof(TCPClientAddress);
        SOCKET TCPClientSocket = accept(TCPServerSocket, (sockaddr*)&TCPClientAddress, &szTCPClientAddress);
        vSocketList.push_back(TCPClientSocket);
        HANDLE WorkHandle = (HANDLE)_beginthreadex(nullptr, 0, WorkThread, (void*)&TCPClientSocket, 0, nullptr);
        EnterCriticalSection(&CSThread);
        vHandleList.push_back(WorkHandle);
        LeaveCriticalSection(&CSThread);
        cout << "[SYS]New TCPClient Connected." << endl;
    }//eowhile

    for (int i = 0; i < vHandleList.size(); i++)
    {
        TerminateThread(vHandleList[i], -1);
        CloseHandle(vHandleList[i]);
    }
    vHandleList.clear();
    DeleteCriticalSection(&CSThread);

    if (TCPServerSocket) { closesocket(TCPServerSocket); }
    WSACleanup();
    return 0;
}

int L20221118_TCPMultiplexingServer_main1(int argc, char* argv[])
//int main(int argc, char* argv[])
{
    WSAData wsadata = { 0, };
    SOCKET TCPServerSocket = NULL;
    SOCKADDR_IN TCPServerAddress = { 0, };
    int Retval = 0;
    //1.Load Winsock2.2
    Retval = WSAStartup(MAKEWORD(2, 2), &wsadata);
    if (Retval != 0)
    {
        cout << "[ERR]Winsock 2.2 Load Failed. ErrorCode : " << GetLastError() << endl;
        exit(-1);
    }
    cout << "[SYS]Winsock 2.2 Load Complete!" << endl;
    TCPServerAddress.sin_family = AF_INET;
    TCPServerAddress.sin_addr.S_un.S_addr = inet_addr(SERVER_IPV4);
    TCPServerAddress.sin_port = htons(SERVER_PORT);
    //2.Create TCPServerSocket
    TCPServerSocket = socket(AF_INET, SOCK_STREAM, 0/*IPPROTO_TCP*/);
    if (TCPServerSocket == INVALID_SOCKET)
    {
        cout << "[ERR]TCPSocket Creation Failed! ErrorCode : " << GetLastError() << endl;
        exit(-2);
    }
    cout << "[SYS]TCPSocket Creation Complete!" << endl;
    //3.Bind TCPServerSocket to Address 
    Retval = bind(TCPServerSocket, (sockaddr*)&TCPServerAddress, sizeof(TCPServerAddress));
    if (Retval != 0)
    {
        cout << "[ERR]TCPSocket Address Bind Failed! ErrorCode : " << GetLastError() << endl;
        exit(-3);
    }
    cout << "[SYS]TCPSocket Address Bind Complete!" << endl;
    //4.Set TCPServerSocket Listening...
    Retval = listen(TCPServerSocket, SOMAXCONN);
    if (Retval != 0)
    {
        cout << "[ERR]TCPSocket Listen Failed! ErrorCode : " << GetLastError() << endl;
        exit(-4);
    }
    cout << "[SYS]TCPSocket Listening..." << endl;
    //--------------------------------------------------------------------------------------------
    //Socket ����ü �迭(����) �Ҵ� 
    fd_set reads; FD_ZERO(&reads);
    //Socket ����ü �迭(���纻) �Ҵ�
    fd_set copys; FD_ZERO(&copys);
    //TCPServerSocket�� ���¸� �����Ͽ� OS�� ������ �� �ִ� ����ü�� �Ҵ��Ѵ�.
    FD_SET(TCPServerSocket, &reads);
    //1�ʸ��� �ѹ��� ����
    TIMEVAL Timeout;
    Timeout.tv_sec = 1;
    Timeout.tv_usec = 0;
    
    while (true)
    {
        copys = reads;
        //Timeout���� ���ϻ��°� �ٲ� ���� �ִ��� Ȯ���ϱ�!
        int fd_num = select(0, &copys, 0, 0, &Timeout);
        if (fd_num == SOCKET_ERROR)
        {
            cout << "[ERR]Select Error Occured! ErrorCode : " << GetLastError() << endl;
            exit(-5);
        }
        else if (fd_num == 0)
        {
            //�ٲ� ���� ���ٸ�, Continue;
            continue;
        }
        int SendBytes = 0;
        int RecvBytes = 0;
        char Buffer[PACKET_SIZE] = { 0, };
        

        for (int i = 0; i < (int)reads.fd_count; i++)
        {
            //�ش� ������ �ٲ�� �ִ°�?
            if (FD_ISSET(reads.fd_array[i], &copys)) //�ٲ�� �ִ���?
            {
                //�ٲ�� ������, �ڽ�(��������)�� �ٲ���ٰ� �˸��� ���´�!
                //�������Ͽ��� Ŭ�� ���� Connect�� Accpet�ϰ� reads�� �߰�
                if (reads.fd_array[i] == TCPServerSocket)
                {
                    sockaddr_in TCPClientAddress = { 0, };
                    int szTCPClientAddress = sizeof(TCPClientAddress);
                    SOCKET TCPClientSocket = accept(TCPServerSocket, (sockaddr*)&TCPClientAddress, &szTCPClientAddress);
                    FD_SET(TCPClientSocket, &reads);
                    cout << "[SYS]New TCPClient Connected." << endl;
                }
                else
                {
                    memset(Buffer, 0, sizeof(Buffer));

                    SOCKET TCPClientSocket = reads.fd_array[i];
                    RecvBytes = recv(TCPClientSocket, Buffer, sizeof(Buffer), 0);
                    //���۸� �ݵ�� NTS(Null Terminated String)�� ������� ������ ���ڿ��� '\0'���� �����Ѵ�.
                    Buffer[sizeof(Buffer) - 1] = '\0';
                    if (RecvBytes <= 0)
                    {
                        //TCPClientSocket�� ��������Ǿ��ų�(0) �����������(SOCKET_ERROR(-1))
                        //fd_set ����ü ����(reads)���� ���� ���� �ݴ´�.
                        FD_CLR(TCPClientSocket, &reads);
                        closesocket(TCPClientSocket);
                        cout << "[SYS]TCPClient Disconnected." << endl;
                    }
                    else
                    {
                        cout << "[SYS]TCPClient Recv Message : " << Buffer << endl;
                        for (int j = 0; j < (int)reads.fd_count; j++)
                        {
                            if (reads.fd_array[j] != TCPServerSocket && reads.fd_array[j] != TCPClientSocket)
                            {
                                //����, reads.fd_array[j]�� TCPClientSocket�� ���, ���� �޽����� Send�Ѵ�!
                                SendBytes = send(reads.fd_array[j], Buffer, sizeof(Buffer), 0);
                                if (SendBytes <= 0)
                                {
                                    //TCPClientSocket�� ��������Ǿ��ų�(0) �����������(SOCKET_ERROR(-1))
                                    //fd_set ����ü ����(reads)���� ���� ���� �ݴ´�.
                                    SOCKET TCPClientSocket = reads.fd_array[j];
                                    FD_CLR(TCPClientSocket, &reads);
                                    closesocket(TCPClientSocket);
                                    continue;
                                }
                                cout << "[SYS]TCPClient Send Message : " << Buffer << endl;
                            }
                        }
                    }
                }
            }//eoif_FD_ISSET
        }//eofor
    }//eowhile
    if (TCPServerSocket) { closesocket(TCPServerSocket); }
    WSACleanup();
    return 0;
}